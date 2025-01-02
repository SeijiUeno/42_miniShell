/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_verification.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:19:18 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/15 19:10:59 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

int	verify_abs_path(const char *path)
{
	return (has_access(path, F_OK) && has_access(path, X_OK));
}

char	*define_full_path(char *cmd, char **path)
{
	char	*full_path;

	if (verify_abs_path(cmd))
		return (cmd);
	full_path = search_path(cmd, path);
	return (full_path);
}

char	*search_path(const char *bin, char **path)
{
	int		i;
	char	*full_path;

	i = 0;
	if (!bin || !*bin || !path)
		return (NULL);
	while (path[i])
	{
		full_path = build_full_path(path[i], bin);
		if (!full_path)
		{
			error("ERROR: ", "memory allocation failed", 1);
			return (NULL);
		}
		if (has_access(full_path, F_OK))
		{
			if (has_access(full_path, X_OK))
				return (full_path);
			gc_deallocate(full_path);
			return (NULL);
		}
		gc_deallocate(full_path);
		i++;
	}
	return (NULL);
}
