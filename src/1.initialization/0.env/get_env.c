/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:53:41 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/15 19:52:48 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

int	is_key_in_envp(const char *key, t_ms *minishell)
{
	int	i;

	if (!key || !minishell || !minishell->envp)
		return (EXIT_FAILURE);
	i = 0;
	while (minishell->envp[i])
	{
		if (ft_strncmp(minishell->envp[i], key, ft_strlen(key)) == 0
			&& minishell->envp[i][ft_strlen(key)] == '=')
			return (EXIT_SUCCESS);
		i++;
	}
	return (EXIT_FAILURE);
}

static char	**alloc_env_ar(char **envir, int *count)
{
	char	**new_env;

	*count = 0;
	while (envir[*count])
		(*count)++;
	new_env = ft_calloc(*count + 1, sizeof(char *));
	gc_track(new_env);
	return (new_env);
}

char	**free_envir_array(char **envir, int index)
{
	while (--index >= 0)
		gc_deallocate(envir[index]);
	gc_deallocate(envir);
	envir = NULL;
	return (NULL);
}

char	**get_env(char **envir)
{
	char	**new_env;
	int		env_count;
	int		index;

	new_env = alloc_env_ar(envir, &env_count);
	if (!new_env)
		return (NULL);
	index = 0;
	while (index < env_count)
	{
		new_env[index] = ft_strdup(envir[index]);
		if (!new_env[index])
			return (free_envir_array(new_env, index));
		index++;
	}
	new_env[env_count] = (NULL);
	gc_track(new_env);
	return (new_env);
}
