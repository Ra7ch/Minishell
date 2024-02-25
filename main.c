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
		minishell(str, &env, NULL, NULL);
	}
	return (g_v->exit_status);
}
