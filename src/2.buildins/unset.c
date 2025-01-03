/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 19:11:01 by sueno-te          #+#    #+#             */
/*   Updated: 2025/01/03 14:39:29 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

static int	get_filtered_envp_len(char **envp, const char *key)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!envp || !key)
		return (0);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, ft_strlen(key)) != 0
			|| envp[i][ft_strlen(key)] != '=')
			count++;
		i++;
	}
	return (count);
}

static char	**allocate_new_env(int new_len)
{
	char	**new_env;

	new_env = (char **)gc_allocate(sizeof(char *) * (new_len + 1));
	if (!new_env)
		return (NULL);
	new_env[new_len] = NULL;
	return (new_env);
}

static int	copy_filtered_env(char **new_env, char **envp, const char *key)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, ft_strlen(key)) != 0
			|| envp[i][ft_strlen(key)] != '=')
		{
			new_env[j++] = envp[i];
		}
		else
		{
			gc_deallocate(envp[i]);
		}
		i++;
	}
	return (j);
}

static int	unset_env(const char *key, t_ms *minishell)
{
	char	**new_env;
	int		new_len;

	if (!key || !minishell || !minishell->envp)
		return (EXIT_FAILURE);
	new_len = get_filtered_envp_len(minishell->envp, key);
	new_env = allocate_new_env(new_len);
	if (!new_env)
		return (EXIT_FAILURE);
	copy_filtered_env(new_env, minishell->envp, key);
	gc_deallocate(minishell->envp);
	minishell->envp = new_env;
	return (EXIT_SUCCESS);
}

int	unset(const char **keys, t_ms *minishell)
{
	int		status_error;
	char	**key_iter;

	status_error = 0;
	if (!keys || !keys[1])
		return (0);
	key_iter = (char **)(keys + 1);
	while (*key_iter)
	{
		if (var_validate_name(*key_iter))
		{
			minishell->status = error(*key_iter, "not a valid identifier", 1);
		}
		else if (is_key_in_envp(*key_iter, minishell) == EXIT_SUCCESS)
		{
			if (unset_env(*key_iter, minishell) == EXIT_FAILURE)
				minishell->status = error(*key_iter,
						"memory allocation failed", 1);
		}
		key_iter++;
	}
	util_free_array(minishell->path);
	minishell->path = get_paths(minishell->envp);
	return (status_error);
}
