/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorales <emorales@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:45:18 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/13 15:30:26 by emorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

// Function to join words
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

static char	*handle_expansion(const char *input_str,
	int *index, t_minishell *minishell)
{
	if (input_str[*index] == '\'')
		return (expand_single_quotes(input_str, index));
	if (input_str[*index] == '"')
		return (expand_double_quotes(input_str, index, minishell));
	if (input_str[*index] == '$')
		return (expand_parameter(input_str, index, minishell));
	return (expand_word(input_str, index));
}

char	*expansor(const char *input_str, t_minishell *minishell)
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
