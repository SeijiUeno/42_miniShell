/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_validate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 20:07:10 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/10 19:57:31 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"


static int syntax_error(const char *message, const char *token) 
{
    (void)message;
	error((char *)"syntax error near unexpected token ", (char *)token, 1);

	return (1);
}

// Check if the first token is an invalid leading pipe
static int check_leading_pipe(t_token *token) {
    if (token && token->type == OPERATOR && token->content[0] == '|') {
        return syntax_error("leading pipe", token->content);
    }
    return 0;
}

// Check for syntax errors between consecutive operators or trailing operators
static int check_consecutive_operators(t_token *current) {
    if (current->type == OPERATOR) {
        if (!current->next) {
            // Trailing operator (e.g., "echo hello |")
            return syntax_error("trailing operator", "`newline'");
        } else if (current->next->type == OPERATOR) {
            // Consecutive operators (e.g., "echo hello ||")
            return syntax_error("consecutive operators", current->next->content);
        }
    }
    return 0;
}

// Validate the token list for syntax errors
int validate_tokens(t_token *tokens) {
    t_token *current = tokens;

    // Step 1: Check for a leading pipe
    if (check_leading_pipe(current)) {
        return 1;
    }

    // Step 2: Iterate through tokens and check for syntax errors
    while (current) {
        if (check_consecutive_operators(current)) {
            return 1;
        }
        current = current->next;
    }

    return EXIT_SUCCESS; // No syntax errors found
}
