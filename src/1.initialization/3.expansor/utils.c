/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:13:07 by sueno-te          #+#    #+#             */
/*   Updated: 2025/01/08 20:55:11 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

char	*expand_until_char(const char *input_str, int *index, char stop_char)
{
	int	start_index;
	int	len;

	start_index = *index;
	len = 0;
	while (input_str[*index] && input_str[*index] != stop_char
		&& input_str[*index] != '$')
	{
		(*index)++;
		len++;
	}
	return (ft_substr(input_str, start_index, len));
}

char	*expand_word(const char *input_str, int *index)
{
	int	start_index;
	int	len;

	start_index = *index;
	len = 0;
	while (input_str[*index] && !strchr(QUOTES, input_str[*index])
		&& input_str[*index] != '$')
	{
		(*index)++;
		len++;
	}
	return (ft_substr(input_str, start_index, len));
}

static char	*env_get_value_from_envp(const char *env_entry, int var_len)
{
	int	start_index;

	start_index = var_len;
	if (env_entry[start_index] == '=')
		start_index++;
	return (ft_strdup(&env_entry[start_index]));
}

char	*expand_env(const char *var_name, char **envp)
{
	int	i;
	int	var_len;

	var_len = strlen(var_name);
	i = 0;
	while (envp[i])
	{
		if (strncmp(var_name, envp[i], var_len) == 0
			&& (envp[i][var_len] == '=' || envp[i][var_len] == '\0'))
		{
			return (env_get_value_from_envp(envp[i], var_len));
		}
		i++;
	}
	return (ft_strdup(""));
}
