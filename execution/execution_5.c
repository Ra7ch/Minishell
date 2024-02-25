/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-zeh <mben-zeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 00:32:54 by raitmous          #+#    #+#             */
/*   Updated: 2023/06/25 03:42:54 by mben-zeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exec_child(t_data *data, t_env **env, int builtins)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (data->fdin == -1 || data->fdout == -1)
		exit(1);
	if (data->fdin > 2)
		dup2(data->fdin, STDIN_FILENO);
	if (data->fdout > 2)
		dup2(data->fdout, STDOUT_FILENO);
	if (builtins)
		(ft_builtins(data, env, builtins), exit(g_v->exit_status));
	ft_exec_cmd(data, *env);
	exit(g_v->exit_status);
}

void	ft_exec_parent(t_data **data, int pid)
{
	waitpid(pid, &g_v->exit_status, 0);
	ft_free_arg((*data)->arg);
	if (WIFEXITED(g_v->exit_status))
		g_v->exit_status = WEXITSTATUS(g_v->exit_status);
	else if (WIFSIGNALED(g_v->exit_status))
	{
		g_v->exit_status = 128 + WTERMSIG(g_v->exit_status);
		if (WTERMSIG(g_v->exit_status) == SIGQUIT)
			write(1, "Quit: 3", 8);
		write(1, "\n", 1);
	}
}

int	ft_exec_check_builtins(int *builtins, t_env **env, t_data **data)
{
	*builtins = ft_check_builtins(*data);
	if (*builtins > 4 || (*builtins == 4 && (*data)->arg && (*data)->arg[1]))
	{
		if (*builtins != 7)
			g_v->exit_status = 0;
		ft_builtins((*data), env, *builtins);
		ft_free_arg((*data)->arg);
		return (0);
	}
	return (1);
}

int	ft_exec(t_data *data, t_env **env)
{
	pid_t	pid;
	int		builtins;

	pid = 0;
	ft_exec_sub1(&data, env);
	if (ft_exec_check_builtins(&builtins, env, &data) == 0)
		return (0);
	pid = fork();
	if (pid == -1)
		return (g_v->exit_status = 1, (1));
	if (pid == 0)
		ft_exec_child(data, env, builtins);
	else
		ft_exec_parent(&data, pid);
	return (0);
}
