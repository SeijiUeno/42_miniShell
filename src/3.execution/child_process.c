/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:24:44 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/14 15:58:11 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void exec_wait_for_children(t_minishell *minishell, pid_t *pids, int count) {
    struct sigaction sa_ignore, sa_restore;
    sa_ignore.sa_handler = SIG_IGN;
    sa_ignore.sa_flags = 0;
    sigemptyset(&sa_ignore.sa_mask);
    sigaction(SIGINT, &sa_ignore, &sa_restore); // Ignore Ctrl-C in parent
    sigaction(SIGQUIT, &sa_ignore, NULL);      // Ignore Ctrl-\ in parent

    int status;
    minishell->status = 0;
    for (int i = 0; i < count; i++) {
        waitpid(pids[i], &status, 0);
        if (WIFEXITED(status))
            minishell->status = WEXITSTATUS(status);
        else if (WIFSIGNALED(status)) {
            minishell->status = 128 + WTERMSIG(status);
            ft_putstr_fd("\n", STDOUT_FILENO); // Ensure newline for signals
        }
    }

    sigaction(SIGINT, &sa_restore, NULL); // Restore original handler
    sigaction(SIGQUIT, &sa_restore, NULL);
}

void	setup_child_fds(t_minishell *m, t_command *cmd, int *pipes, int ctx[2])
{
	int	child_index;
	int	cmd_count;

	child_index = ctx[0];
	cmd_count = ctx[1];
	if (child_index > 0 && dup2(pipes[(child_index - 1) * 2], STDIN_FILENO) < 0)
		util_free_child(m);
	if (child_index < cmd_count - 1
		&& dup2(pipes[child_index * 2 + 1], STDOUT_FILENO) < 0)
		util_free_child(m);
	pipe_close_all(pipes, (cmd_count - 1) * 2);
	if (cmd->redir && redir_setup(cmd->redir) != 0)
		util_free_child(m);
}

void	exec_run_child_command(t_minishell *m, t_command *cmd,
	int *pipes, int ctx[2])
{
	char	*cmd_path;

	setup_child_fds(m, cmd, pipes, ctx);
	if (!cmd->argv || !cmd->argv[0])
		util_free_child(m);
	if (builtin_check(cmd->argv, m) >= 0)
		util_free_child(m);
	cmd_path = define_full_path(cmd->argv[0], m->path);
	if (!cmd_path)
	{
		error(cmd->argv[0], ": Command not found", 127);
		util_free_child(m);
	}
	execve(cmd_path, cmd->argv, m->envp);
    signal(SIGINT, SIG_DFL);  // Restore default Ctrl-C behavior
    signal(SIGQUIT, SIG_DFL);
	perror("execve");
	util_free_child(m);
}

