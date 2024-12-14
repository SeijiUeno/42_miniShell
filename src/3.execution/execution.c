/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorales <emorales@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:20:43 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/13 19:04:36 by emorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

static void	child_single(char *full_path, char **argv, t_minishell *minishell)
{
	int	fd;

	fd = 3;
	while (fd < 1024)
	{
		close(fd);
		fd++;
	}
	execve(full_path, argv, minishell->envp);
	perror("execve");
	free(full_path);
	free_all(minishell);
	_exit(EXIT_FAILURE);
}

int	exec_run_command(char **arrstr, int id, t_minishell *minishell)
{
	char	*full_path;
	int		exec_status;
	pid_t	child_pid;

	(void)id;
	/* Validate command and retrieve full path if needed */
	exec_status = is_valid_command(&full_path, arrstr[0], minishell->path);
	if (exec_status != EXIT_SUCCESS)
	{
		/* Command not found or not valid */
		if (full_path && full_path != arrstr[0])
			free(full_path);
		return (exec_status);
	}
	/* Fork and execute the command in a child process */
	child_pid = fork();
	if (child_pid < 0)
	{
		perror("fork");
		if (full_path && full_path != arrstr[0])
			free(full_path);
		return (EXIT_FAILURE);
	}
	if (child_pid == 0)
	{
		/* Child process */
		child_single(full_path, arrstr, minishell);
		/* child_single doesn't return on success */
	}
	/* Parent process: wait for the child */
	waitpid(child_pid, &exec_status, 0);
	exec_status = status_filter(exec_status);
	/* If full_path differs from arrstr[0], it was newly allocated and must be freed */
	if (full_path && full_path != arrstr[0])
		free(full_path);
	/* Restore file descriptors to their original state */
	fds_reset(minishell);
	return (exec_status);
}

void	execute(t_minishell *m)
{
	t_command	**commands;
	int			cmd_count;

	commands = ast_to_command_list(m->tree_cmd);
	if (!commands)
	{
		signal_setup();
		return ;
	}
	debug_print_commands_array(commands);
	cmd_count = count_commands_in_array(commands);
	if (cmd_count > 0)
		pipe_run_pipeline(m, commands, cmd_count);
	free(commands);
	signal_setup();
}
