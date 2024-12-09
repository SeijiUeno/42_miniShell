/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_acess.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 20:29:30 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/09 20:37:21 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

char	*ft_strjoin_three(char *s1, char *s2, char *s3)
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

char	*verify_path(char *bin, char **path)
{
	int		i;
	char	*full_path;

	// Return NULL if the binary is empty or path is NULL
	if (!bin || !*bin || !path)
		return (NULL);

	i = 0;
	while (path[i])
	{
		// Ensure the directory ends with a '/' before concatenation
		if (path[i][ft_strlen(path[i]) - 1] != '/')
			full_path = ft_strjoin_three(path[i], "/", bin); // Custom function
		else
			full_path = ft_strjoin(path[i], bin);

		if (!full_path)
		{
			perror("minishell: memory allocation failed");
			return (NULL);
		}

		// Check if the file exists and is executable
		if (access(full_path, F_OK) == 0)
		{
			if (access(full_path, X_OK) == 0)
				return (full_path); // Found a valid path
			else
			{
				// File exists but is not executable
				fprintf(stderr, "minishell: permission denied: %s\n", full_path);
				free(full_path);
				return (NULL);
			}
		}

		// Free the allocated path and proceed to the next directory
		free(full_path);
		i++;
	}

	// Return NULL if the binary is not found in any directory
	fprintf(stderr, "minishell: command not found: %s\n", bin);
	return (NULL);
}
