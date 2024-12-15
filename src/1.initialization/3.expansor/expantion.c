/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:45:18 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/15 05:54:36 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

char	*join_word(char *word, char *new_word)
{
	char	*combined;

	if (!word)
		return (new_word);
	combined = ft_strjoin(word, new_word);
	free(word);
	free(new_word);
	return (combined);
}

static char	*handle_expansion(const char *input_str, int *index,
		t_ms *minishell)
{
	if (input_str[*index] == '\'')
		return (expand_single_quotes(input_str, index));
	if (input_str[*index] == '"')
		return (expand_double_quotes(input_str, index, minishell));
	if (input_str[*index] == '$')
		return (expand_parameter(input_str, index, minishell));
	return (expand_word(input_str, index));
}

char	*expansor(const char *input_str, t_ms *minishell)
{
	char	*result;
	char	*temp_str;
	int		index;

	result = NULL;
	index = 0;
	while (input_str[index])
	{
		temp_str = handle_expansion(input_str, &index, minishell);
		if (!temp_str)
		{
			free(result);
			return (NULL);
		}
		result = join_word(result, temp_str);
		if (!result)
			return (NULL);
	}
	return (result);
}
