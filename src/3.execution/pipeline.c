/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:25:42 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/15 19:24:11 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	run_single_command(t_ms *m, t_command *c)
{
	int	status;

	status = 0;
	if (c->redir && redir_setup(c->redir, m) != EXIT_SUCCESS)
	{
		ft_putstr_fd("Error: Redirection setup failed\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (!c->argv)
		return (0);
	status = builtin_check(c->argv, m);
	if (status >= 0)
		return (status);
	status = exec_run_command(c->argv, 0, m);
	return (status);
}

void	fork_children(t_ms *m, t_command **cmds, int cmd_count, int *pipes)
{
	pid_t	*pids;
	int		i;
	int		ctx[2];

	ctx[1] = cmd_count;
	pids = ft_calloc(sizeof(pid_t), cmd_count);
	if (!pids)
		return ;
	i = 0;
	while (i < cmd_count)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			ctx[0] = i;
			exec_run_child_command(m, cmds[i], pipes, ctx);
		}
		i++;
	}
	pipe_close_all(pipes, (cmd_count - 1) * 2);
	exec_wait_for_children(m, pids, cmd_count);
	gc_deallocate(pids);
}

void	pipe_run_pipeline(t_ms *m, t_command **cmds, int cmd_count)
{
	int	*pipes;

	if (cmd_count == 1)
	{
		g_in_subprocess = 1;
		if (cmds[0]->redir && redir_setup(cmds[0]->redir, m) != EXIT_SUCCESS)
			m->status = 1;
		else
			m->status = run_single_command(m, cmds[0]);
		g_in_subprocess = 0;
		return ;
	}
	pipes = ft_calloc(sizeof(int), (cmd_count - 1) * 2);
	if (!pipes)
		return ;
	if (pipe_create(pipes, cmd_count) != EXIT_SUCCESS)
	{
		gc_deallocate(pipes);
		return ;
	}
	g_in_subprocess = 1;
	fork_children(m, cmds, cmd_count, pipes);
	g_in_subprocess = 0;
	gc_deallocate(pipes);
}
