/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:25:42 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/10 14:25:44 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int run_single_command(t_minishell *m, t_command *c) {
    if (c->redir && setup_redirs(c->redir) != 0)
        return (EXIT_FAILURE);
    if (!c->argv)
        return (0);
    if (is_builtin(c->argv, m) >= 0)
        return (m->status);
    return (exec_command(c->argv, 0, m));
}

void fork_children(t_minishell *m, t_command **cmds, int cmd_count, int *pipes) {
    pid_t *pids = ft_calloc(sizeof(pid_t), cmd_count);

    for (int i = 0; i < cmd_count; i++) {
        if ((pids[i] = fork()) == 0) {
            int ctx[] = {i, cmd_count};
            run_child_command(m, cmds[i], pipes, ctx);
        }
    }
    close_all_pipes(pipes, (cmd_count - 1) * 2);
    wait_for_children(m, pids, cmd_count);
    free(pids);
}

void run_pipeline(t_minishell *m, t_command **cmds, int cmd_count) {
    if (cmd_count == 1) {
        m->status = run_single_command(m, cmds[0]);
        return;
    }
    int *pipes = ft_calloc(sizeof(int), (cmd_count - 1) * 2);
    if (!pipes)
        return;
    if (create_pipes(pipes, cmd_count) != EXIT_SUCCESS) {
        free(pipes);
        return;
    }
    fork_children(m, cmds, cmd_count, pipes);
    free(pipes);
}
