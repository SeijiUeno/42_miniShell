/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorales <emorales@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:20:43 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/14 14:33:43 by emorales         ###   ########.fr       */
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

static int	validate_and_get_path(char **full_path, char *cmd, t_minishell *minishell)
{
	int	exec_status;

	exec_status = is_valid_command(full_path, cmd, minishell->path);
	if (exec_status != EXIT_SUCCESS && *full_path && *full_path != cmd)
		free(*full_path);
	return (exec_status);
}

static int	handle_child_process(char *full_path, char **arrstr, t_minishell *minishell)
{
	pid_t	child_pid;
	int		exec_status;

	child_pid = fork();
	if (child_pid < 0)
	{
		perror("fork");
		if (full_path && full_path != arrstr[0])
			free(full_path);
		return (EXIT_FAILURE);
	}
	if (child_pid == 0)
		child_single(full_path, arrstr, minishell); /* Never returns on success */
	waitpid(child_pid, &exec_status, 0);
	return (status_filter(exec_status));
}

int	exec_run_command(char **arrstr, int id, t_minishell *minishell)
{
	char	*full_path;
	int		exec_status;

	(void)id;
	exec_status = validate_and_get_path(&full_path, arrstr[0], minishell);
	if (exec_status != EXIT_SUCCESS)
		return (exec_status);
	exec_status = handle_child_process(full_path, arrstr, minishell);
	if (full_path && full_path != arrstr[0])
		free(full_path);
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
