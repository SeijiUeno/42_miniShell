/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:00:43 by sueno-te          #+#    #+#             */
/*   Updated: 2025/01/03 20:12:33 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

t_token	*remove_empty_tokens(t_token **tokens)
{
	t_token	*current;
	t_token	*temp;

	if (!tokens || !*tokens)
		return (*tokens);
	current = *tokens;
	while (current)
	{
		if (current->content && strcmp(current->content, "$EMPTY") == 0)
		{
			temp = current->next;
			remove_token_from_list(tokens, &current);
			current = temp;
			continue ;
		}
		current = current->next;
	}
	return (*tokens);
}

char	*expand_single_quotes(const char *input_str, int *index)
{
	int	start_index;
	int	len;

	len = 0;
	if (input_str[*index] == '\'')
		(*index)++;
	start_index = *index;
	while (input_str[*index] && input_str[*index] != '\'')
	{
		(*index)++;
		len++;
	}
	if (input_str[*index] == '\'')
		(*index)++;
	return (ft_substr(input_str, start_index, len));
}

static char	*handle_escape_sequence(const char *input_str, int *index)
{
	if (input_str[*index] == '\\' && input_str[*index + 1] == '$')
	{
		*index += 2;
		return (ft_strdup("$"));
	}
	return (NULL);
}

static char	*process_inside_quotes(const char *input_str, int *index, t_ms *m)
{
	char	*temp_str;

	temp_str = handle_escape_sequence(input_str, index);
	if (temp_str)
		return (temp_str);
	if (input_str[*index] == '$')
		return (expand_parameter(input_str, index, m));
	return (expand_until_char(input_str, index, '"'));
}

char	*expand_double_quotes(const char *input_str, int *index, t_ms *m)
{
	char	*result;
	char	*temp_str;

	result = NULL;
	if (input_str[*index] == '"')
		(*index)++;
	if (input_str[*index] == '"')
		(*index)++;
	while (input_str[*index] && input_str[*index] != '"')
	{
		temp_str = process_inside_quotes(input_str, index, m);
		result = join_word(result, temp_str);
		if (!temp_str || !(result))
		{
			gc_deallocate(result);
			return (NULL);
		}
	}
	if (input_str[*index] == '"')
		(*index)++;
	return (result);
}
