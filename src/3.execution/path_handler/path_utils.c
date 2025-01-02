/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:18:48 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/15 19:10:51 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

char	*ft_strjoin_three(const char *s1, const char *s2, const char *s3)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(s1, s2);
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, s3);
	gc_deallocate(temp);
	return (result);
}

int	has_access(const char *path, int mode)
{
	return (access(path, mode) == 0);
}

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
	i = -1;
	while (split[++i])
	{
		temp = split[i];
		split[i] = ft_strjoin(temp, "/");
		if (!split[i])
		{
			gc_deallocate(temp);
			while (--i >= 0)
				gc_deallocate(split[i]);
			gc_deallocate(split);
			return (NULL);
		}
		gc_deallocate(temp);
	}
	return (split);
}

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
