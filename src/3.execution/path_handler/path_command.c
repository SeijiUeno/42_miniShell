/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorales <emorales@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:21:48 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/14 19:52:01 by emorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

static int	handle_path_validation(const char *cmd, char **full_path,
		struct stat *path_stat)
{
	*full_path = strdup(cmd);
	if (!*full_path)
		return (error(cmd, ": Memory allocation failed", 1));
	// Check if the path exists
	if (access(*full_path, F_OK) < 0)
	{
		free(*full_path);
		*full_path = NULL;
		return (error(cmd, ": No such file or directory", 127));
			// Fix: Return 127 for nonexistent paths
	}
	// Check if `stat` can retrieve details about the path
	if (stat(*full_path, path_stat) < 0)
	{
		free(*full_path);
		*full_path = NULL;
		return (error(cmd, ": Not a directory", 126));
			// Leave as-is for other `stat` errors
	}
	return (EXIT_SUCCESS);
}

static int	check_command_type(const char *cmd, char **full_path,
		struct stat *path_stat)
{
	if (S_ISDIR(path_stat->st_mode))
	{
		free(*full_path);
		*full_path = NULL;
		return (error(cmd, ": Is a directory", 126)); // Directory case
	}
	if (access(*full_path, X_OK) < 0)
	{
		free(*full_path);
		*full_path = NULL;
		return (error(cmd, ": Permission denied", 126));
			// No execute permission
	}
	return (EXIT_SUCCESS);
}

int	is_valid_command(char **full_path, const char *cmd, char **env_path)
{
	struct stat	path_stat;
	int			status;

	// Check absolute or relative path
	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
	{
		status = handle_path_validation(cmd, full_path, &path_stat);
		if (status != EXIT_SUCCESS)
			return (status);
		return (check_command_type(cmd, full_path, &path_stat));
	}
	// Search in PATH
	*full_path = search_path(cmd, env_path);
	if (!*full_path)
		return (error(cmd, " Command not found", 127));
			// Command not found in PATH
	return (EXIT_SUCCESS);
}
