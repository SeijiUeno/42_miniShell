/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:24:44 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/10 18:56:13 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.c"

void wait_for_children(t_minishell *minishell, pid_t *pids, int count) {
    int status;

    minishell->status = 0;
    for (int i = 0; i < count; i++) {
        waitpid(pids[i], &status, 0);
        if (WIFEXITED(status))
            minishell->status = WEXITSTATUS(status);
        else if (WIFSIGNALED(status))
            minishell->status = 128 + WTERMSIG(status);
    }
}

void setup_child_fds(t_minishell *m, t_command *cmd, int *pipes, int ctx[2]) {
    int child_index = ctx[0], cmd_count = ctx[1];
    if (child_index > 0 && dup2(pipes[(child_index - 1) * 2], STDIN_FILENO) < 0)
        free_child(m);
    if (child_index < cmd_count - 1 && dup2(pipes[child_index * 2 + 1], STDOUT_FILENO) < 0)
        free_child(m);
    close_all_pipes(pipes, (cmd_count - 1) * 2);
    if (cmd->redir && setup_redirs(cmd->redir) != 0)
        free_child(m);
}

void run_child_command(t_minishell *m, t_command *cmd, int *pipes, int ctx[2]) {
    char *cmd_path;

    setup_child_fds(m, cmd, pipes, ctx);
    if (!cmd->argv || !cmd->argv[0])
        free_child(m);
    if (is_builtin(cmd->argv, m) >= 0)
        free_child(m);
    cmd_path = define_full_path(cmd->argv[0], m->path);
    if (!cmd_path) {
        error(cmd->argv[0], ": Command not found", 127);
        free_child(m);
    }
    execve(cmd_path, cmd->argv, m->envp);
    perror("execve");
    free_child(m);
}
