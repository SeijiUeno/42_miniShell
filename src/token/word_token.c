/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:39:52 by sueno-te          #+#    #+#             */
/*   Updated: 2024/11/25 18:15:59 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

static int	initialize_token_buffer(t_token **token, char **buffer, char *input, int index)
{
	*token = gc_allocate(sizeof(t_token));
	if (!(*token))
		return (0);
	*buffer = gc_allocate(strlen(input) - index + 1);
	if (!(*buffer))
	{
		gc_deallocate(*token);
		return (0);
	}
	return (1);
}

static int	process_quotes_and_escapes(char *input, int *i, char *buffer, int *buf_index)
{
	int	in_single_quote;
	int	in_double_quote;

	in_single_quote = 0;
	in_double_quote = 0;
	while (input[*i] != '\0'
		&& (in_single_quote || in_double_quote
			|| (!is_operator(input[*i]) && !isspace((unsigned char)input[*i]))))
	{
		if (input[*i] == '\'' && !in_double_quote)
		{
			in_single_quote = !in_single_quote;
			(*i)++;
		}
		else if (input[*i] == '"' && !in_single_quote)
		{
			in_double_quote = !in_double_quote;
			(*i)++;
		}
		else if (input[*i] == '\\' && !in_single_quote)
		{
			if (input[*i + 1] != '\0')
			{
				(*i)++;
				buffer[(*buf_index)++] = input[(*i)++];
			}
			else
			{
				fprintf(stderr, "Error: Incomplete escape sequence\n");
				return (-1);
			}
		}
		else
			buffer[(*buf_index)++] = input[(*i)++];
	}
	if (in_single_quote || in_double_quote)
	{
		fprintf(stderr, "Error: Unclosed quote\n");
		return (-1);
	}
	buffer[*buf_index] = '\0';
	return (0);
}

static t_token	*finalize_word_token(t_token *token, char *buffer)
{
	token->value = gc_strdup(buffer);
	gc_deallocate(buffer);
	if (!token->value)
	{
		gc_deallocate(token);
		return (NULL);
	}
	token->type = TOKEN_WORD;
	token->next = NULL;
	return (token);
}

t_token	*create_word_token(char *input, int *index)
{
	t_token	*token;
	char	*buffer;
	int		buf_index;
	int		i;

	buf_index = 0;
	i = *index;
	if (!initialize_token_buffer(&token, &buffer, input, i))
		return (NULL);
	if (process_quotes_and_escapes(input, &i, buffer, &buf_index) == -1)
	{
		gc_deallocate(token);
		gc_deallocate(buffer);
		return (NULL);
	}
	token = finalize_word_token(token, buffer);
	if (!token)
		return (NULL);
	*index = i;
	return (token);
}
