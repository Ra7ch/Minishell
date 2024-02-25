/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raitmous <raitmous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 02:13:02 by raitmous          #+#    #+#             */
/*   Updated: 2024/02/21 18:41:11 by raitmous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <termios.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# define ERROR_SYNTAX "\x1b[1;31mminishell: syntax error\n"
# define PROMPT "\x1b[1;36mMinish$>\x1b[1;0m \x1b[1;38m"

typedef struct s_global
{
	int				exit_status;
	int				heredoc;
	int				seg_quit;
	int				q;
	int				exit_inpipe;
}					t_global;

extern t_global			*g_v ;

typedef enum TokenType
{
	TOKEN_PIPE = 0,
	TOKEN_AND = 1,
	TOKEN_OR = 2,
	TOKEN_APPEND = 3,
	TOKEN_HEREDOC = 4,
	TOKEN_INPUT = 5,
	TOKEN_OUTPUT = 6,
	TOKEN_WORD = 7,
	FILE_IN = 8,
	FILE_OUT = 9,
	FILE_APP = 10,
	WORD_LIM = 11,
	TOKEN_PAR = 12,
}					t_TokenType;

typedef struct s_file
{
	int				fd;
	char			*name;
	t_TokenType		token;
	struct s_file	*next;
}					t_file;

typedef struct s_data
{
	t_TokenType		token;
	t_file			*files;
	char			**arg;
	struct s_data	*left;
	struct s_data	*right;
	pid_t			pid;
	int				fdin;
	char			**path;
	int				fdout;
	int				in_par;

}					t_data;

typedef struct s_list
{
	char			*content;
	t_TokenType		token;
	int				quote;
	struct s_list	*next;
	struct s_list	*prev;
}					t_list;

typedef struct s_env
{
	char			*var;
	char			*value;
	struct s_env	*next;
}					t_env;
typedef struct s_fork
{
	pid_t			pid;
	int				fdin;
	int				fdout;
	struct s_fork	*next;
}					t_fork;

typedef struct s_pipe
{
	int				*fd;
	int				fdin;
	int				fdout;
	struct s_pipe	*prev;
	struct s_pipe	*next;
}					t_pipe;

enum
{
	STATE_NORMAL,
	STATE_SINGLE_QUOTE,
	STATE_DOUBLE_QUOTE,
};

typedef struct s_word
{
	char			c;
	int				type;
	struct s_word	*next;
}					t_word;

int					ft_check_builtins(t_data *data);
char				*ft_getpwd(t_env *env);
void				ft_builtins_sub(char **str, t_env **env, t_data *data,
						int x);
int					ft_builtins(t_data *data, t_env **env, int x);
void				ft_cd_sub_sub(int *n, char **str, char *arg, t_env **env);
void				ft_cd_sub1(int *n, char **str, char *arg, t_env **env);
void				ft_cd_sub2(char **str, t_env **env);
void				ft_cd(t_data *data, t_env **env);
int					ft_check_n(char *str);
void				ft_echo(char **str);
int					is_var(char *str, int *equal, int *add);
int					ft_strcmp2(const char *s1, const char *s2);
int					ft_underscore(t_env *env, char *value);
void				ft_search_insert_sub(t_env **env, char ***str, int equal,
						int add);
int					ft_search_inset(t_env *env, char **str, int equal, int add);
char				*ft_search_env(t_env *env, char *str);
void				ft_export_error(char **str, int i, int is_export);
void				ft_export(t_env **env, char **str);
void				ft_unset_sub(t_env **env);
void				ft_unset(t_env **env, char **str, t_env *node, t_env *temp);
int					ft_is_number(char *str);
void				ft_exit(char **arg);
void				ft_env(t_env *env, int is_export);
char				*ft_split_join(char *ptr, t_env *env);
void				ft_print_ambiguous(t_data *root);
int					ft_openfile_sub1(t_data **root, t_env *env, char ***arg,
						char *ptr);
void				ft_openfile_sub2(t_data **root, char **arg);
void				ft_openfile(t_data *root, t_env *env);
void				ft_args_sub3(char **temp, char **ptr);
void				ft_args_sub2(t_env *env, char **temp, char **ptr);
void				ft_args_sub1(char **arg, t_env *env, char **str);
void				ft_arg_while(char **args);
char				**ft_args(char **arg, t_env *env);
void				ft_putstr_fd(char *s, int fd);
void				ft_msg_cmd_error(char *cmd);
int					size_env(t_env *env);
char				**ft_env_tab(t_env *env);
char				*ft_envchr(char **envp, char *str);
char				*ft_getenv(t_env *env, const char *find);
char				**ft_path_envp(t_env *envp);
int					ft_charexist(char *s, int c);
void				ft_isdir(char **str, char **envp);
void				ft_exec_cmd(t_data *data, t_env *env);
int					ft_exec_sub1(t_data **data, t_env **env);
void				ft_exec_child(t_data *data, t_env **env, int builtins);
void				ft_exec_parent(t_data **data, int pid);
int					ft_exec_check_builtins(int *builtins, t_env **env,
						t_data **data);
int					ft_exec(t_data *data, t_env **env);
void				ft_execution_sub1_child(t_data **data, t_env **env,
						int *par);
int					ft_execution_sub1(t_data **data, t_env **env, int *par,
						int *pfd);
int					ft_execution_sub2_sub1(t_data **data, t_env **env, int *pid,
						int **fd);
int					ft_execution_sub2_sub2(t_data **data, t_env **env, int *pid,
						int **fd);
int					ft_execution_sub2(t_data **data, t_env **env, int *par,
						int *pid);
void				ft_execution_sub3(t_data *data, t_env **env, int *par);
int					ft_execution_sub0(t_data *data, int par);
void				ft_exection(t_data *data, t_env **env);
char				*ft_add_list(char *str, t_list **list, int **all,
						t_env *env);
int					ft_spl_sub1(char **str, int *par, int (*qte)[3], int i);
int					ft_spl(char *str, t_list **list, t_env *env);
void				ft_add_env(t_env **data, char **env);
void				ft_full_env(t_env **data, char **envp, char **env);
void				handle_heredoc_sigint(int sig);
void				heredoc_init(char **str, int **fd, char **h_doc);
void				heredoc_child(int *fd, int quote, char *lim, t_env *env);
int					ft_full_heredoc(char *lim, t_env *env, int quote);
void				ft_insetdata(t_data *data, t_data *new);
void				buildtree_sub1(t_data **data, int *par, t_data **node);
void				buildtree_sub2(t_data **data, t_data **current,
						t_data **root, t_data **node);
void				buildtree_sub3(t_data **data, t_data **current,
						t_data **root);
t_data				*buildtree(t_data *root, t_data *current, t_data *data);
void				ft_full_data_sub1(t_list **list, char **str, t_file **files,
						t_data **data);
void				ft_full_data_sub2(t_list **list, char **str, t_file **files,
						t_env *env);
t_data				*ft_full_data(t_list *list, t_env *env);
void				look_for_quote(char *s, int *i, char c);
int					check_wildcard(char *arg);
void				creat_word(char c, t_word **p, int type, int i);
int					token_word_sub(int *type, int *i, char *str);
t_word				*token_words(char *str);
int					check_pattern(t_word *p, const char *line);
void				expand_wildcard_sub_sub(int j, char **ptr,
						struct dirent *entry);
void				expand_wildcard_sub(int j, t_word *p, char **ptr,
						char *str);
char				*expand_wildcard(char *str);
char				*ft_quote(char *str);
int					check_pattern(t_word *p, const char *line);
void				expand_wildcard_sub_sub(int j, char **ptr,
						struct dirent *entry);
void				expand_wildcard_sub(int j, t_word *p, char **ptr,
						char *str);
char				*expand_wildcard(char *str);
int					ft_check_error_sub1(t_list *list);
int					ft_check_error_sub2(t_list *list);
int					ft_check_error_sub3(t_list *list, t_list *next,
						t_list *prev);
int					ft_check_error(t_list *list);
int					ft_check_redir(t_list *list);
int					ft_strncmp(char *s1, char *s2, size_t n);
size_t				ft_strlen(const char *str);
void				ft_putstr(char *s, int fd);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strdup(const char *s1);
char				*ft_substr(char const *s, unsigned int start, size_t len);
int					is_token(char c);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_nbrlen(long n);
char				*ft_itoa(int n);
int					ft_atoi(char *str);
char				*ft_check(char *s1, char *s2);
char				*ft_strjoin(char *s1, char *s2);
void				ft_token_redirect(t_list *node, char *content);
t_list				*ft_lstnew(char *content);
void				ft_token_file(t_list *node, t_list *new, t_env *env);
void				ft_lstadd_back(t_list **lst, t_list *new, t_env *env);
void				ft_lstadd_front(t_file **lst, t_file *new);
t_file				*ft_filenew(t_list *list, t_env *env);
void				ft_fileadd_back(t_file **lst, t_file *new);
t_data				*ft_dtnew(t_data *left, t_data *right);
t_data				*ft_datanew(char **arg, t_file *files, t_TokenType token);
void				ft_dtadd_back(t_data **lst, t_data *new);
t_env				*ft_envnew(char *var, char *value);
void				ft_envadd_back(t_env **lst, t_env *new);
t_fork				*ft_forknew(pid_t pid, int fdin, int fdout);
void				ft_forkadd_back(t_fork **lst, t_fork *new);
t_pipe				*ft_fdnew(int *fd);
void				ft_fdadd_front(t_pipe **lst, t_pipe *new);
void				ft_fdadd_back(t_pipe **lst, t_pipe *new);
char				**ft_split(char const *s, char c);
void				ft_freedata(t_data *lst, int all);
void				ft_free(t_list *list, t_data *data, t_data *root,
						t_file *file);
void				ft_free_word(t_word *word);
void				ft_freelist(t_list *lst);
void				ft_freeroot(t_data *root);
void				ft_freefile(t_file *file);
void				ft_free_arg(char **arg);
void				syntax_error(t_list *list);
int					check_expand(char *str, int use);
char				*ft_expand(char *str, t_env *env, int use);
int					check_quote(char *str);
void				rl_replace_line(const char *str, int i);

#endif