/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raitmous <raitmous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 00:37:13 by raitmous          #+#    #+#             */
/*   Updated: 2023/06/25 02:34:01 by raitmous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

char	*ft_split_join(char *ptr, t_env *env);
void	ft_print_ambiguous(t_data *root);
void	ft_openfile_sub1(t_data **root, t_env *env, char ***arg, char *ptr);
void	ft_openfile_sub2(t_data **root, char **arg);
void	ft_openfile(t_data *root, t_env *env);
void	ft_args_sub3(char **temp, char **ptr);
void	ft_args_sub2(t_env *env, char **temp, char **ptr);
void	ft_args_sub1(char **arg, t_env *env, char **str);
void	ft_arg_while(char **args);
char	**ft_args(char **arg, t_env *env);
void	ft_putstr_fd(char *s, int fd);
void	ft_msg_cmd_error(char *cmd);
int		size_env(t_env *env);
char	**ft_env_tab(t_env *env);
char	*ft_envchr(char **envp, char *str);
char	*ft_getenv(t_env *env, const char *find);
char	**ft_path_envp(t_env *envp);
int		ft_charexist(char *s, int c);
void	ft_isdir(char **str, char **envp);
void	ft_exec_cmd(t_data *data, t_env *env);
int		ft_exec_sub1(t_data **data, t_env **env);
void	ft_exec_child(t_data *data, t_env **env, int builtins);
void	ft_exec_parent(t_data **data, int pid);
int		ft_exec_check_builtins(int *builtins, t_env **env, t_data **data);
int		ft_exec(t_data *data, t_env **env);
void	ft_execution_sub1_child(t_data **data, t_env **env, int *par);
int		ft_execution_sub1(t_data **data, t_env **env, int *par, int *pfd);
int		ft_execution_sub2_sub1(t_data **data, t_env **env, int *pid, int **fd);
int		ft_execution_sub2_sub2(t_data **data, t_env **env, int *pid, int **fd);
int		ft_execution_sub2(t_data **data, t_env **env, int *par, int *pid);
void	ft_execution_sub3(t_data *data, t_env **env, int *par);
int		ft_execution_sub0(t_data *data, int par);
void	ft_exection(t_data *data, t_env **env);

#endif
