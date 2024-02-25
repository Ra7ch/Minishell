/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_6.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raitmous <raitmous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 00:34:14 by raitmous          #+#    #+#             */
/*   Updated: 2024/02/21 19:51:21 by raitmous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_execution_sub1_child(t_data **data, t_env **env, int *par)
{
	(*par)++;
	if ((*data)->fdin > 2)
		dup2((*data)->fdin, STDIN_FILENO);
	if ((*data)->fdout > 2)
		dup2((*data)->fdout, STDOUT_FILENO);
	ft_exection((*data)->left, env);
	exit(g_v->exit_status);
}

int	ft_execution_sub1(t_data **data, t_env **env, int *par, int *pfd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (0);
	if (pid == 0)
		ft_execution_sub1_child(data, env, par);
	else
	{
		if ((*data)->fdin > 2)
			(dup2(pfd[0], STDIN_FILENO),
				close((*data)->fdin));
		if ((*data)->fdout > 2)
			(dup2(pfd[1], STDOUT_FILENO),
				close((*data)->fdout));
		waitpid(pid, &g_v->exit_status, 0);
		g_v->exit_status = WEXITSTATUS(g_v->exit_status);
	}
	return (1);
}

int	ft_execution_sub2_sub1(t_data **data, t_env **env, int *pid, int **fd)
{
	*pid = fork();
	if (*pid == -1)
		return (0);
	if (*pid == 0)
	{
		g_v->exit_inpipe = 1;
		close((*fd)[0]);
		dup2((*fd)[1], STDOUT_FILENO);
		ft_exection((*data)->left, env);
		exit(g_v->exit_status);
	}
	g_v->exit_status = 0;
	return (1);
}

int	ft_execution_sub2_sub2(t_data **data, t_env **env, int *pid, int **fd)
{
	*pid = fork();
	if (*pid == -1)
		return (0);
	if (*pid == 0)
	{
		g_v->exit_inpipe = 1;
		close((*fd)[1]);
		dup2((*fd)[0], STDIN_FILENO);
		ft_exection((*data)->right, env);
		exit(g_v->exit_status);
	}
	return (1);
}

int	ft_execution_sub2(t_data **data, t_env **env, int *par, int *pid)
{
	int	*fd;

	if (*par >= 2)
		exit(1);
	*par = 0;
	fd = malloc(2 * sizeof(int));
	if (pipe(fd) == -1)
		return (0);
	if (ft_execution_sub2_sub1(data, env, &(pid[0]), &fd) == 0)
		return (0);
	if (ft_execution_sub2_sub2(data, env, &(pid[1]), &fd) == 0)
		return (0);
	close(fd[1]);
	close(fd[0]);
	waitpid(pid[0], &g_v->exit_status, 0);
	waitpid(pid[1], &g_v->exit_status, 0);
	g_v->exit_status = WEXITSTATUS(g_v->exit_status);
	free(fd);
	return (1);
}
