/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raitmous <raitmous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:32:37 by mben-zeh          #+#    #+#             */
/*   Updated: 2024/02/21 18:47:22 by raitmous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
t_global *g_v = NULL;
const char *ApiKey = "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";

void	minishell(char *str, t_env **env, t_list *list, t_data *data)
{
	t_data	*root;

	root = NULL;
	g_v->heredoc = 0;
	ft_putstr("\x1b[0;0m", 1);
	if (str)
	{
		if (*str)
		{
			add_history(str);
			if (ft_spl(str, &list, *env))
				syntax_error(list);
			else
			{
				data = ft_full_data(list, *env);
				root = buildtree(NULL, NULL, data);
				ft_exection(root, env);
				ft_free(list, data, root, NULL);
			}
		}
		free(str);
	}
	else
		(printf("exit\n"), exit(g_v->exit_status));
}

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		g_v->exit_status = 1;
	}
}

char	*ft_prompt(void)
{
	char	*str;
	char	*prompt;
	char	**p;
	char	*tmp;
	int		i;

	str = getcwd(NULL, 0);
	if (str == NULL)
		str = ft_strdup(" ");
	p = ft_split(str, '/');
	free(str);
	i = 0;
	while (p[i])
		i++;
	if (g_v->exit_status == 0)
		tmp = ft_strdup("\xF0\x9F\x98\x8A \x1b[1;36m");
	else
		tmp = ft_strdup("\xF0\x9F\x98\xA1 \x1b[1;36m");
	prompt = ft_strjoin(tmp, p[i - 1]);
	prompt = ft_strjoin(prompt, ">\x1b[1;0m \x1b[1;38m");
	i = 0;
	while (p[i])
		free(p[i++]);
	return (free(p), prompt);
}

char	*ft_readline(void)
{
	char			*str;
	char			*prompt;
	struct termios	term;
	struct termios	original;

	prompt = NULL;
	tcgetattr(STDERR_FILENO, &term);
	tcgetattr(STDERR_FILENO, &original);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDERR_FILENO, TCSANOW, &term);
	if (g_v->heredoc == 1)
		g_v->exit_status = 1;
	prompt = ft_prompt();
	signal(SIGINT, &handle_sigint);
	str = readline(prompt);
	free(prompt);
	signal(SIGINT, SIG_IGN);
	tcsetattr(STDERR_FILENO, TCSANOW, &original);
	return (str);
}


struct string {
    char *ptr;
    size_t len;
};

void init_string(struct string *s) {
    s->len = 0;
    s->ptr = malloc(1);
    if (s->ptr) s->ptr[0] = '\0';
}

size_t writefunc(void *ptr, size_t size, size_t nmemb, struct string *s) {
    size_t new_len = s->len + size * nmemb;
    s->ptr = realloc(s->ptr, new_len + 1);
    if (s->ptr) {
        memcpy(s->ptr + s->len, ptr, size * nmemb);
        s->ptr[new_len] = '\0';
        s->len = new_len;
    }
    return size * nmemb;
}

char *clean_command(const char *response) {
    // Remove code block markers and trim whitespace
    const char *start = response;
    while (*start && (isspace((unsigned char)*start) || *start == '`')) start++;
    const char *end = start + strlen(start);
    while (end > start && (isspace((unsigned char)*(end-1)) || *(end-1) == '`')) end--;
    size_t len = end - start;
    char *cmd = malloc(len + 1);
    if (cmd) {
        memcpy(cmd, start, len);
        cmd[len] = '\0';
    }
    return cmd;
}

int is_empty(const char *s) {
    if (!s) return 1;
    while (*s) {
        if (!isspace((unsigned char)*s))
            return 0;
        s++;
    }
    return 1;
}

char *ai_prompt(char *str) {
	if (is_empty(str)) {
        return strdup("");
    }
    CURL *curl;
    CURLcode res;
    struct curl_slist *headers = NULL;
    struct string response;
    char *api_key = getenv("GROQ_API_KEY");
    char *command = NULL;

    if (!api_key) {
        fprintf(stderr, "GROQ_API_KEY not set\n");
        return str;
    }

    // Prepare the prompt
    char prompt[1024];
    snprintf(prompt, sizeof(prompt),
		"You are a Unix shell assistant. Given the following user request, respond ONLY with the exact shell command to run, and nothing else. "
		"If the user refers to 'this folder', 'here', or similar, use '.' to refer to the current directory. "
		"Do NOT use placeholders like '/path/to/folder'. "
		"Do NOT include explanations, markdown, or code blocks. "
		"If the request is ambiguous or not a command, respond with an empty string. "
		"User request: %s", str);
    // Prepare JSON body
    struct json_object *body = json_object_new_object();
    json_object_object_add(body, "model", json_object_new_string("meta-llama/llama-4-scout-17b-16e-instruct")); // the Groq model here
    struct json_object *messages = json_object_new_array();
    struct json_object *msg = json_object_new_object();
    json_object_object_add(msg, "role", json_object_new_string("user"));
    json_object_object_add(msg, "content", json_object_new_string(prompt));
    json_object_array_add(messages, msg);
    json_object_object_add(body, "messages", messages);

    const char *body_str = json_object_to_json_string(body);

    // Init curl
    curl = curl_easy_init();
	printf("curl: %p\n", curl);
    if (curl) {
        init_string(&response);
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.groq.com/openai/v1/chat/completions");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body_str);

        headers = curl_slist_append(headers, "Content-Type: application/json");
        char auth_header[256];
        snprintf(auth_header, sizeof(auth_header), "Authorization: Bearer %s", api_key);
        headers = curl_slist_append(headers, auth_header);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        res = curl_easy_perform(curl);

        if (res == CURLE_OK) {
            // Parse JSON response
            struct json_object *parsed = json_tokener_parse(response.ptr);
            struct json_object *choices, *first, *msg_obj, *content_obj;
            if (json_object_object_get_ex(parsed, "choices", &choices) &&
                json_object_array_length(choices) > 0) {
                first = json_object_array_get_idx(choices, 0);
                if (json_object_object_get_ex(first, "message", &msg_obj) &&
                    json_object_object_get_ex(msg_obj, "content", &content_obj)) {
                    const char *cmd = json_object_get_string(content_obj);
                    if (cmd && strlen(cmd) > 0) {
                        command = strdup(cmd);
                    }
                }
            }
            json_object_put(parsed);
        }
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
        free(response.ptr);
    }
    json_object_put(body);

	printf("command: %s\n", command);

    if (command) {
        char *cleaned = clean_command(command);
        free(command);
        return cleaned;
    }
    return strdup("");
}

int confirm_command(const char *cmd) {
    char answer[16];
    printf("AI suggests: %s\n", cmd);
    printf("Do you want to run this command? [y/N]: ");
    if (fgets(answer, sizeof(answer), stdin) == NULL)
        return 0;
    // Accept 'y' or 'Y' as yes, everything else is no
    return (answer[0] == 'y' || answer[0] == 'Y');
}

int main (int ac, char **av, char **envp)
{
	char	*str;
	t_env	*env;

	g_v = malloc(sizeof(t_global));
	env = NULL;
	ac = 0;
	av = NULL;
	(void)ac;
	(void)av;
	ft_full_env(&env, envp, NULL);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		str = ft_readline();

		// here i ll pass the command to the ai prompt to generate a command
		str = ai_prompt(str);
		// and then i ll ask if the user want to execute the command
		if (str && strlen(str) > 0) {
			if (confirm_command(str)) {
				// Proceed to execute the command
				minishell(str, &env, NULL, NULL);
			} else {
				printf("Command not executed.\n");
				free(str);
			}
		}
		// minishell(str, &env, NULL, NULL);
	}
	return (g_v->exit_status);
}
