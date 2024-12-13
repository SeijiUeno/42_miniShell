/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   even_more_token_aux.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorales <emorales@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:53:20 by emorales          #+#    #+#             */
/*   Updated: 2024/12/13 13:12:25 by emorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

int	validate_all_quotes(char *input)
{
	int		index;
	char	*quote;

	index = 0;
	while (input[index])
	{
		if (ft_strchr(QUOTES, input[index]))
		{
			quote = &input[index];
			index++;
			while (input[index] && input[index] != *quote)
				index++;
			if (!input[index])
				return (EXIT_FAILURE);
		}
		index++;
	}
	return (EXIT_SUCCESS);
}

int	is_only_spaces(char *input)
{
	int	i;

	i = 0;
	while (input[i] && ft_strchr(WHITESPACE, input[i]))
		i++;
	return (input[i] == '\0');
}

int	assign_redir_type(char op_char, char *content)
{
	if (op_char == '<')
	{
		if (content[1] == '<') // Handle '<<'
			return (HEREDOC);
		else
			return (REDIR_IN);
	}
	else if (op_char == '>')
	{
		if (content[1] == '>') // Handle '>>'
			return (APPEND);
		else
			return (REDIR_OUT);
	}
	return (OPERATOR); // Default case for unexpected input
}

void	process_symbol(char *input, int *index, t_token **tokens, t_token **current)
{
	t_token_data	data;

	data.tokens = tokens;
	data.current = current;
	data.input = input;
	if ((input[*index] == '|' && input[*index + 1] == '|')
		|| (input[*index] == '<' && input[*index + 1] == '>'))
	{
		error("minishell", "syntax error near unexpected token", -1);
		return ;
	}
	if ((input[*index] == '<' && input[*index + 1] == '<') || (input[*index] == '>' && input[*index + 1] == '>'))
	{
		add_token(&data, *index, *index + 2);
		*index += 2;
	}
	else
	{
		add_token(&data, *index, *index + 1);
		(*index)++;
	}
}

void	process_word(char *input, int *index, t_token **tokens, t_token **current)
{
	int				start;
	t_token_data	data;

	start = *index;
	data.tokens = tokens;
	data.current = current;
	data.input = input;
	while (input[*index] && !ft_strchr(WHITESPACE, input[*index]) && !ft_strchr(SYMBOLS, input[*index]))
	{
		if (ft_strchr(QUOTES, input[*index]))
			skip_quoted_token(input, index); // Skip quoted segments
		else if (ft_strchr(SYMBOLS, input[*index]) && !ft_strchr(QUOTES, input[start]))
			break ;
		else
			(*index)++;
	}
	add_token(&data, start, *index);
}
