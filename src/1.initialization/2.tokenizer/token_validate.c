/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_validate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorales <emorales@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 20:07:10 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/12 20:55:46 by emorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

// Check if the first token is an invalid leading pipe
static int	check_leading_pipe(t_token *token)
{
	char	*error_msg;

	error_msg = "leading pipe error near token ";
	if (token && token->content[0] == '|')
		return (error(error_msg, token->content, -1));
	return (0);
}

// Check for syntax errors between consecutive operators or trailing operators
static int	check_consecutive_operators(t_token *current)
{
	char	*error_msg;

	if (current->type == PIPE)
	{
		if (!current->next)
		{
			error_msg = "trailing operator ";
			// Trailing operator (e.g., "echo hello |")
			return (error(error_msg, current->content, -1));
		}
		else if (current->next->type == PIPE)
		{
			error_msg = "consecutive operators ";
			// Consecutive operators (e.g., "echo hello ||")
			return (error(error_msg, current->next->content, -1));
		}
	}
	return (0);
}

// Validate the token list for syntax errors
int	validate_tokens(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	// Step 1: Check for a leading pipe
	if (check_leading_pipe(current))
		return (1);
	// Step 2: Iterate through tokens and check for syntax errors
	while (current)
	{
		if (check_consecutive_operators(current))
			return (1);
		current = current->next;
	}
	assign_operator_token_types(&tokens);
	return (EXIT_SUCCESS); // No syntax errors found
}
