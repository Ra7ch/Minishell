/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raitmous <raitmous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 01:40:38 by raitmous          #+#    #+#             */
/*   Updated: 2023/06/25 02:34:12 by raitmous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

int		ft_strncmp(char *s1, char *s2, size_t n);
size_t	ft_strlen(const char *str);
void	ft_putstr(char *s, int fd);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		is_token(char c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_nbrlen(long n);
char	*ft_itoa(int n);
int		ft_atoi(char *str);
char	*ft_check(char *s1, char *s2);
char	*ft_strjoin(char *s1, char *s2);
void	ft_token_redirect(t_list *node, char *content);
t_list	*ft_lstnew(char *content);
void	ft_token_file(t_list *node, t_list *new, t_env *env);
void	ft_lstadd_back(t_list **lst, t_list *new, t_env *env);
void	ft_lstadd_front(t_file **lst, t_file *new);
t_file	*ft_filenew(t_list *list, t_env *env);
void	ft_fileadd_back(t_file **lst, t_file *new);
t_data	*ft_dtnew(t_data *left, t_data *right);
t_data	*ft_datanew(char **arg, t_file *files, t_TokenType token);
void	ft_dtadd_back(t_data **lst, t_data *new);
t_env	*ft_envnew(char *var, char *value);
void	ft_envadd_back(t_env **lst, t_env *new);
t_fork	*ft_forknew(pid_t pid, int fdin, int fdout);
void	ft_forkadd_back(t_fork **lst, t_fork *new);
t_pipe	*ft_fdnew(int *fd);
void	ft_fdadd_front(t_pipe **lst, t_pipe *new);
void	ft_fdadd_back(t_pipe **lst, t_pipe *new);
char	**ft_split(char const *s, char c);
void	ft_freedata(t_data *lst, int all);
void	ft_free(t_list *list, t_data *data, t_data *root, t_file *file);
void	ft_free_word(t_word *word);
void	ft_freelist(t_list *lst);
void	ft_freeroot(t_data *root);
void	ft_freefile(t_file *file);
void	ft_free_arg(char **arg);
void	syntax_error(t_list *list);

#endif