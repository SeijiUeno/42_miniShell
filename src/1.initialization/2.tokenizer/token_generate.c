/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_generate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorales <emorales@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:42:46 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/12 16:08:27 by emorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

int		validate_input(char *input);
t_token	*tokenize_input(char *input);
int		validate_all_quotes(char *input);

void	generate_tokens(char *input, t_token **tokens)
{
	if (validate_input(input))
	{
		*tokens = NULL; // Set tokens to NULL if input is invalid
		return ;
	}
	*tokens = tokenize_input(input);
	if (tokens)
		assign_operator_token_types(tokens);
}

int	validate_input(char *input)
{
	if (!input || !input[0])
		return (error("minishell: ", "Empty input", EXIT_FAILURE));
	if (validate_all_quotes(input) != EXIT_SUCCESS)
		return (error("minishell: ", "Unmatched quotes in input", EXIT_FAILURE));
	if (is_only_spaces(input))
		return (error("minishell: ", "Input contains only whitespace", EXIT_FAILURE));
	return (EXIT_SUCCESS);
}

void	add_token(t_token **tokens, t_token **current, char *input, int start, int end)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	new_token->content = ft_substr(input, start, end - start);
	new_token->type = ft_strchr(SYMBOLS, input[start]) ? OPERATOR : WORD;
	new_token->next = NULL;
	new_token->prev = NULL;
	if (*current)
	{
		(*current)->next = new_token;
		new_token->prev = *current;
	}
	else
		*tokens = new_token;
	*current = new_token;
}

void	assign_operator_token_types(t_token **tokens)
{
	t_token	*current;
	char	op_char;

	current = *tokens;
	while (current)
	{
		if (current->type == OPERATOR)
		{
			op_char = current->content[0];
			if (op_char == '|')
				current->type = PIPE;
			else
				current->type = assign_redirection_type(op_char, current->content);
		}
		current = current->next;
	}
}


t_token	*tokenize_input(char *input)
{
	t_token	*tokens;
	t_token	*current;
	int		index;
	int		start;

	tokens = NULL;
	current = NULL;
	index = 0;
	while (input[index])
	{
		skip_whitespace(input, &index); // Skip leading whitespace
		if (input[index] && ft_strchr(SYMBOLS, input[index]))
		{
			if ((input[index] == '<' && input[index + 1] == '<')
				|| (input[index] == '>' && input[index + 1] == '>'))
			{
				add_token(&tokens, &current, input, index, index + 2);
				index += 2;
			}
			else
			{
				add_token(&tokens, &current, input, index, index + 1);
				index++;
			}
		}
		else if (input[index])
		{
			// Process words (handles quotes)
			start = index;
			while (input[index] && !ft_strchr(WHITESPACE, input[index]) && !ft_strchr(SYMBOLS, input[index]))
			{
				if (ft_strchr(QUOTES, input[index]))
					skip_quoted_token(input, &index); // Skip quoted segments
				else
					index++;
			}
			add_token(&tokens, &current, input, start, index);
		}
	}
	return (tokens);
}
