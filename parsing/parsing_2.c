/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raitmous <raitmous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 00:46:01 by raitmous          #+#    #+#             */
/*   Updated: 2023/06/25 03:24:45 by raitmous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_heredoc_sigint(int sig)
{
	g_v->exit_status = -1;
	(void)sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	ft_putstr("\n", 1);
	exit(1);
}

void	heredoc_init(char **str, int **fd, char **h_doc)
{
	*str = NULL;
	*h_doc = NULL;
	close((*fd)[0]);
	signal(SIGINT, &handle_heredoc_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	heredoc_child(int *fd, int quote, char *lim, t_env *env)
{
	char	*h_doc;
	char	*str;

	heredoc_init(&str, &fd, &h_doc);
	while (g_v->exit_status != -1)
	{
		h_doc = readline(">");
		if (!h_doc || !ft_strcmp(h_doc, lim))
		{
			free(h_doc);
			break ;
		}
		if (!quote)
		{
			str = ft_expand(h_doc, env, 0);
			free(h_doc);
			h_doc = str;
		}
		h_doc = ft_strjoin(h_doc, "\n");
		(ft_putstr(h_doc, fd[1]), free(h_doc));
	}
	if (g_v->exit_status == -1)
		exit(1);
	exit(0);
}

int	ft_full_heredoc(char *lim, t_env *env, int quote)
{
	int	fd[2];
	int	pid;

	if (pipe(fd))
		return (g_v->exit_status = 1, -1);
	pid = fork();
	if (pid == -1)
		return (g_v->exit_status = 1, -1);
	if (pid == 0)
		heredoc_child(fd, quote, lim, env);
	else
	{
		waitpid(pid, &g_v->exit_status, 0);
		close(fd[1]);
		if (WEXITSTATUS(g_v->exit_status) == 1)
		{
			close(fd[0]);
			g_v->heredoc = 1;
		}
		g_v->exit_status = WEXITSTATUS(g_v->exit_status);
	}
	return (fd[0]);
}
