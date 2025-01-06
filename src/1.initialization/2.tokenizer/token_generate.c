/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_generate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:42:46 by sueno-te          #+#    #+#             */
/*   Updated: 2025/01/06 16:41:11 by sueno-te         ###   ########.fr       */
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
		*tokens = NULL;
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
		return (1);
	}
	return (EXIT_SUCCESS);
}

void	add_token(t_token_data *data, int start, int end)
{
	t_token	*new_token;

	new_token = (t_token *)gc_allocate(sizeof(t_token));
	if (!new_token)
	{
		perror("gc_allocate");
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
	t_token		*current;
	char		op_char;

	if (!tokens || !*tokens)
		return ;
	current = *tokens;
	while (current)
	{
		if (current->type == OPERATOR)
		{
			op_char = current->content[0];
			if (op_char == '|')
				current->type = PIPE;
			else if (op_char == '<' || op_char == '>')
				current->type = assign_redir_type(op_char, current->content);
			else if (current->content[1] != '\0')
			{
				error("minishell", "syntax error near unexpected token", 0);
				status_control(2);
			}
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
		skip_whitespace(input, &index);
		if (input[index] && ft_strchr(SYMBOLS, input[index]))
		{
			process_symbol(input, &index, &tokens, &current);
			if (!tokens)
				return (NULL);
		}
		else if (input[index])
			process_word(input, &index, &tokens, &current);
	}
	return (tokens);
}
