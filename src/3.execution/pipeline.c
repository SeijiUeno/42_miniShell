/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:25:42 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/14 16:01:30 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	run_single_command(t_minishell *m, t_command *c)
{
	if (c->redir && redir_setup(c->redir) != 0)
		return (EXIT_FAILURE);
	if (!c->argv)
		return (0);
	if (builtin_check(c->argv, m) >= 0)
		return (m->status);
	return (exec_run_command(c->argv, 0, m));
}

void	fork_children(t_minishell *m, t_command **cmds, int cmd_count,
		int *pipes)
{
	pid_t	*pids;
	int		i;
	int		ctx[2];

	i = 0;
	pids = ft_calloc(sizeof(pid_t), cmd_count);
	while (i < cmd_count)
	{
		pids[i] = fork();
		if (fork() == 0)
		{
			ctx[0] = i;
			ctx[1] = cmd_count;
			exec_run_child_command(m, cmds[i], pipes, ctx);
		}
		i++;
	}
	pipe_close_all(pipes, (cmd_count - 1) * 2);
	exec_wait_for_children(m, pids, cmd_count);
	free(pids);
}

void	pipe_run_pipeline(t_minishell *m, t_command **cmds, int cmd_count)
{
	int	*pipes;

	if (cmd_count == 1)
	{
		g_in_subprocess = 1;
		m->status = run_single_command(m, cmds[0]);
		g_in_subprocess = 0;
		return ;
	}
	pipes = ft_calloc(sizeof(int), (cmd_count - 1) * 2);
	if (!pipes)
		return ;
	if (pipe_create(pipes, cmd_count) != EXIT_SUCCESS)
	{
		free(pipes);
		return ;
	}
	g_in_subprocess = 1;
	fork_children(m, cmds, cmd_count, pipes);
	g_in_subprocess = 0;
	free(pipes);
}
