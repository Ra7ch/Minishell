/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raitmous <raitmous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 01:29:55 by raitmous          #+#    #+#             */
/*   Updated: 2023/06/25 02:34:16 by raitmous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

int		ft_check_builtins(t_data *data);
char	*ft_getpwd(t_env *env);
void	ft_builtins_sub(char **str, t_env **env, t_data *data, int x);
int		ft_builtins(t_data *data, t_env **env, int x);
void	ft_cd_sub_sub(int *n, char **str, char *arg, t_env **env);
void	ft_cd_sub1(int *n, char **str, char *arg, t_env **env);
void	ft_cd_sub2(char **str, t_env **env);
void	ft_cd(t_data *data, t_env **env);
int		ft_check_n(char *str);
void	ft_echo(char **str);
int		is_var(char *str, int *equal, int *add);
int		ft_strcmp2(const char *s1, const char *s2);
int		ft_underscore(t_env *env, char *value);
void	ft_search_insert_sub(t_env **env, char ***str, int equal, int add);
int		ft_search_inset(t_env *env, char **str, int equal, int add);
char	*ft_search_env(t_env *env, char *str);
void	ft_export_error(char **str, int i, int is_export);
void	ft_export(t_env **env, char **str);
void	ft_unset_sub(t_env **env);
void	ft_unset(t_env **env, char **str, t_env *node, t_env *temp);
int		ft_is_number(char *str);
void	ft_exit(char **arg);
void	ft_env(t_env *env, int is_export);

#endif