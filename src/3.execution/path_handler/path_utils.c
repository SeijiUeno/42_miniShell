/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorales <emorales@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:18:48 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/14 19:51:23 by emorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

// Helper function to join three strings
char	*ft_strjoin_three(const char *s1, const char *s2, const char *s3)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(s1, s2);
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, s3);
	free(temp);
	return (result);
}

// Helper function to check file access
int	has_access(const char *path, int mode)
{
	return (access(path, mode) == 0);
}

// Build the full path for a binary
char	*build_full_path(const char *dir, const char *bin)
{
	if (dir[strlen(dir) - 1] != '/')
		return (ft_strjoin_three(dir, "/", bin));
	return (ft_strjoin(dir, bin));
}

char	**insert_paths(char *paths)
{
	char	**split;
	char	*temp;
	int		i;

	if (!paths)
		return (NULL);
	split = ft_split(paths, ':');
	if (!split)
		return (NULL);
	i = 0;
	while (split[i])
	{
		temp = split[i];
		split[i] = ft_strjoin(temp, "/");
		if (!split[i])
		{
			free(temp);
			while (--i >= 0)
				free(split[i]);
			free(split);
			return (NULL);
		}
		free(temp);
		i++;
	}
	return (split);
}

/*
** Searches for the PATH variable in the environment array and uses insert_paths
** to process it into an array of paths.
*/
char	**get_paths(char **env)
{
	char	**temp;

	if (!env)
		return (NULL);
	temp = env;
	while (*temp)
	{
		if (!ft_strncmp("PATH=", *temp, 5))
			return (insert_paths(*temp + 5));
		temp++;
	}
	return (NULL);
}
