/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:05:50 by sueno-te          #+#    #+#             */
/*   Updated: 2025/01/08 20:55:03 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

char	*extract_var_name(const char *input_str, int *index)
{
	int	start_index;
	int	var_len;

	start_index = *index;
	var_len = 0;
	while (input_str[*index]
		&& (isalnum((unsigned char)input_str[*index])
			|| input_str[*index] == '_'))
	{
		(*index)++;
		var_len++;
	}
	return (ft_substr(input_str, start_index, var_len));
}

static char	*expand_special_parameter(const char *input_str,
	int *index, t_ms *minishell)
{
	if (input_str[*index] == '?')
	{
		(*index)++;
		return (ft_itoa(minishell->status));
	}
	(*index)++;
	return (ft_strdup(""));
}

static char	*get_variable_value(const char *input_str,
	int *index, t_ms *minishell)
{
	char	*var_name;
	char	*expanded_value;

	var_name = extract_var_name(input_str, index);
	if (!var_name)
		return (NULL);
	expanded_value = expand_env(var_name, minishell->envp);
	gc_deallocate(var_name);
	return (expanded_value);
}

char	*expand_parameter(const char *input_str, int *index, t_ms *minishell)
{
	if (*index > 0 && input_str[*index - 1] == '\\')
	{
		(*index)++;
		return (ft_strdup("$"));
	}
	(*index)++;
	if (!input_str[*index]
		|| (!isalnum((unsigned char)input_str[*index])
			&& input_str[*index] != '_' && input_str[*index] != '?'))
	{
		return (ft_strdup("$"));
	}
	if (input_str[*index] == '?' || isdigit((unsigned char)input_str[*index]))
		return (expand_special_parameter(input_str, index, minishell));
	return (get_variable_value(input_str, index, minishell));
}
