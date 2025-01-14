/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   even_more_token_aux.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:53:20 by emorales          #+#    #+#             */
/*   Updated: 2025/01/06 16:35:35 by sueno-te         ###   ########.fr       */
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
		if (content[1] == '<')
			return (HEREDOC);
		else
			return (REDIR_IN);
	}
	else if (op_char == '>')
	{
		if (content[1] == '>')
			return (APPEND);
		else
			return (REDIR_OUT);
	}
	return (OPERATOR);
}

void	process_symbol(char *input, int *index,
		t_token **tokens, t_token **current)
{
	t_token_data	data;

	data.tokens = tokens;
	data.current = current;
	data.input = input;
	if ((input[*index] == '|' && input[*index + 1] == '|')
		|| (input[*index] == '<' && input[*index + 1] == '>'))
	{
		error("minishell", "syntax error near unexpected token", 0);
		status_control(2);
		(*index)++;
		*tokens = NULL;
		return ;
	}
	if ((input[*index] == '<' && input[*index + 1] == '<')
		|| (input[*index] == '>' && input[*index + 1] == '>'))
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

void	process_word(char *input, int *index,
		t_token **tokens, t_token **current)
{
	int				start;
	t_token_data	data;

	start = *index;
	data.tokens = tokens;
	data.current = current;
	data.input = input;
	while (input[*index] && !ft_strchr(WHITESPACE, input[*index])
		&& !ft_strchr(SYMBOLS, input[*index]))
	{
		if (ft_strchr(QUOTES, input[*index]))
			skip_quoted_token(input, index);
		else if (ft_strchr(SYMBOLS, input[*index])
			&& !ft_strchr(QUOTES, input[start]))
			break ;
		else
			(*index)++;
	}
	add_token(&data, start, *index);
}
