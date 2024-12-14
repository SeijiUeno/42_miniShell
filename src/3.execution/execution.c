/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:20:43 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/14 17:21:31 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

static void child_single(char *full_path, char **argv, t_minishell *minishell)
{
    int fd;

    fd = 3;
    while (fd < 1024)
    {
        close(fd);
        fd++;
    }
    signal(SIGINT, SIG_DFL);  // Restore default Ctrl-C behavior
    signal(SIGQUIT, SIG_DFL); // Restore default Ctrl-\ behavior
    execve(full_path, argv, minishell->envp);
    perror("execve");
    free(full_path);
    free_all(minishell);
    _exit(EXIT_FAILURE);
}

int fork_and_execute(char *full_path, char **arrstr, t_minishell *minishell) {
    pid_t child_pid = fork();

    if (child_pid < 0) {
        perror("fork");
        return EXIT_FAILURE;
    }

    if (child_pid == 0)
        child_single(full_path, arrstr, minishell);

    return child_pid;
}

int exec_run_command(char **arrstr, int id, t_minishell *minishell) {
    char *full_path;
    int exec_status;
    pid_t child_pid;

    (void)id;

    exec_status = is_valid_command(&full_path, arrstr[0], minishell->path);
    if (exec_status != EXIT_SUCCESS) {
        if (full_path)
            free(full_path);
        return exec_status;
    }

    child_pid = fork_and_execute(full_path, arrstr, minishell);
    if (child_pid > 0) {
        waitpid(child_pid, &exec_status, 0);
        exec_status = status_filter(exec_status);
    }

    if (full_path)
        free(full_path);

    fds_reset(minishell);
    return exec_status;
}


void execute(t_minishell *m) {
    t_command **commands = ast_to_command_list(m->tree_cmd);
    if (!commands) {
        signal_setup();
        return;
    }
    int cmd_count = count_commands_in_array(commands);
    if (cmd_count > 0)
        pipe_run_pipeline(m, commands, cmd_count);
    free(commands);
    signal_setup();
}

