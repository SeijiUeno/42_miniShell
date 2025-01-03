/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:24:44 by sueno-te          #+#    #+#             */
/*   Updated: 2025/01/03 18:18:15 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	exec_wait_for_children(t_ms *minishell, pid_t *pids, int count)
{
	struct sigaction	sa_ignore;
	struct sigaction	sa_restore;
	int					status;
	int					i;

	status = 0;
	(void)minishell;
	sa_ignore.sa_handler = SIG_IGN;
	sa_ignore.sa_flags = 0;
	sigemptyset(&sa_ignore.sa_mask);
	sigaction(SIGINT, &sa_ignore, &sa_restore);
	sigaction(SIGQUIT, &sa_ignore, NULL);
	status = 0;
	status_control(0);
	i = 0;
	while (i < count)
	{
		waitpid(pids[i], &status, 0);
		status_control(status_filter(status));
		i++;
	}
	sigaction(SIGINT, &sa_restore, NULL);
	sigaction(SIGQUIT, &sa_restore, NULL);
}

void	setup_child_fds(t_ms *m, t_command *cmd, int *pipes, int ctx[2])
{
	int	cur_index;
	int	cmd_count;

	cmd_count = ctx[1];
	cur_index = ctx[0];
	if (cur_index > 0 && dup2(pipes[(cur_index - 1) * 2], STDIN_FILENO) < 0)
		util_free_child(m);
	if ((cur_index < cmd_count - 1)
		&& (dup2(pipes[cur_index * 2 + 1], STDOUT_FILENO) < 0))
		util_free_child(m);
	pipe_close_all(pipes, (cmd_count - 1) * 2);
	if (cmd->redir && redir_setup(cmd->redir, m) != 0)
		util_free_child(m);
}

void	exec_run_child_command(t_ms *m, t_command *cmd, int *pipes, int ctx[2])
{
	char	*cmd_path;

	setup_child_fds(m, cmd, pipes, ctx);
	if (!cmd->argv || !cmd->argv[0])
		util_free_child(m);
	m->status = builtin_check(cmd->argv, m);
	if (m->status >= 0)
		util_free_child(m);
	cmd_path = define_full_path(cmd->argv[0], m->path);
	if (!cmd_path)
	{
		error(cmd->argv[0], " Command not found", 127);
		util_free_child(m);
	}
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	execve(cmd_path, cmd->argv, m->envp);
	perror("execve");
	util_free_child(m);
}
