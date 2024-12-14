/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorales <emorales@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:21:48 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/13 19:27:20 by emorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

// Verify if a command is valid and define its full path
int	is_valid_command(char **full_path, const char *cmd, char **env_path)
{
	if (verify_abs_path(cmd))
	{
		*full_path = strdup(cmd);
		return (EXIT_SUCCESS);
	}
	*full_path = search_path(cmd, env_path);
	if (!*full_path)
		return (error(cmd, ": Command not found", 127));
	return (EXIT_SUCCESS);
}