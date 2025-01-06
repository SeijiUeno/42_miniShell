/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 19:11:01 by sueno-te          #+#    #+#             */
/*   Updated: 2025/01/06 15:27:20 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

static int	get_filtered_envp_len(char **envp, const char *match)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	if (!envp || !match)
		return (0);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], match, ft_strlen(match)) != 0
			|| envp[i][ft_strlen(match)] != '=')
			counter++;
		i++;
	}
	return (counter);
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

static int	copy_filtered_env(char **new_env, char **envp, const char *match)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], match, ft_strlen(match)) != 0
			|| envp[i][ft_strlen(match)] != '=')
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

static int	unset_env(const char *match, t_ms *minishell)
{
	char	**new_env;
	int		new_len;

	if (!match || !minishell || !minishell->envp)
		return (EXIT_FAILURE);
	new_len = get_filtered_envp_len(minishell->envp, match);
	new_env = allocate_new_env(new_len);
	if (!new_env)
		return (EXIT_FAILURE);
	copy_filtered_env(new_env, minishell->envp, match);
	gc_deallocate(minishell->envp);
	minishell->envp = new_env;
	return (EXIT_SUCCESS);
}

int	unset(const char **matchs, t_ms *minishell)
{
	int		status_error;
	char	**match_iter;

	status_error = 0;
	if (!matchs || !matchs[1])
		return (0);
	match_iter = (char **)(matchs + 1);
	while (*match_iter)
	{
		if (var_validate_name(*match_iter))
		{
			minishell->status = error(*match_iter, "not a valid identifier", 1);
		}
		else if (is_key_in_envp(*match_iter, minishell) == EXIT_SUCCESS)
		{
			if (unset_env(*match_iter, minishell) == EXIT_FAILURE)
				minishell->status = error(*match_iter,
						"memory allocation failed", 1);
		}
		match_iter++;
	}
	util_free_array(minishell->path);
	minishell->path = get_paths(minishell->envp);
	return (status_error);
}
