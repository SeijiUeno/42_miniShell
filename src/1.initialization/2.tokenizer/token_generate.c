/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_generate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorales <emorales@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:42:46 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/12 17:43:07 by emorales         ###   ########.fr       */
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
	char	*error_msg;

	if (!input || !input[0])
	{
		error_msg = "Empty input";
		return (error("minishell: ", error_msg, EXIT_FAILURE));
	}
	if (validate_all_quotes(input) != EXIT_SUCCESS)
	{
		error_msg = "Unmatched quotes in input";
		return (error("minishell: ", error_msg, EXIT_FAILURE));
	}
	if (is_only_spaces(input))
	{
		error_msg = "Input contains only whitespace";
		return (error("minishell: ", error_msg, EXIT_FAILURE));
	}
	return (EXIT_SUCCESS);
}

void	add_token(t_token_data *data, int start, int end)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	new_token->content = ft_substr(data->input, start, end - start);
	if (ft_strchr(SYMBOLS, data->input[start]))
		new_token->type = OPERATOR;
	else
		new_token->type = WORD;
	new_token->next = NULL;
	new_token->prev = NULL;
	if (*data->current)
	{
		(*data->current)->next = new_token;
		new_token->prev = *data->current;
	}
	else
		*data->tokens = new_token;
	*data->current = new_token;
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
				current->type = assign_redir_type(op_char, current->content);
		}
		current = current->next;
	}
}

t_token	*tokenize_input(char *input)
{
	t_token	*tokens;
	t_token	*current;
	int		index;

	tokens = NULL;
	current = NULL;
	index = 0;
	while (input[index])
	{
		skip_whitespace(input, &index); // Skip leading whitespace
		if (input[index] && ft_strchr(SYMBOLS, input[index]))
			process_symbol(input, &index, &tokens, &current);
		else if (input[index])
			process_word(input, &index, &tokens, &current);
	}
	return (tokens);
}
