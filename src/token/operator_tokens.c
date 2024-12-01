/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:42:52 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/01 20:06:25 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

// operator_tokens.c

// Set the type of a redirection token based on its content
static void determine_redirection_type(t_token *token, char redir_char) {
    // Ensure the token and its content are valid
    if (!token || !token->content)
        return;

    // Determine the specific redirection type
    if (redir_char == '<') {
        if (token->content[1] == '<')
            token->type = HEREDOC;     // '<<' operator
        else
            token->type = REDIR_IN;    // '<' operator
    } else if (redir_char == '>') {
        if (token->content[1] == '>')
            token->type = APPEND;      // '>>' operator
        else
            token->type = REDIR_OUT;   // '>' operator
    }
}

// Iterate through the token list and set the specific operator types
void assign_operator_token_types(t_token **tokens) {
    t_token *current = *tokens;

    while (current) {
        if (current->type == OPERATOR) {
            char op_char = current->content[0];
            if (op_char == '|') {
                current->type = PIPE;
            } else {
                determine_redirection_type(current, op_char);
            }
        }
        current = current->next;
    }
}

// Handle redirection operators ('<' or '>') in the input and allocate tokens
static void process_redirection_token(char *input, t_token **tokens, int *index) {
    char redir_char = input[*index];
    int start = *index;

    if (input[start + 1] == redir_char) {
        // Double redirection operator ('<<' or '>>')
        create_new_token(tokens, input, start, start + 2);
        *index += 2;  // Move past the operator
    } else {
        // Single redirection operator ('<' or '>')
        create_new_token(tokens, input, start, start + 1);
        *index += 1;  // Move past the operator
    }
}

// Process an operator token from the input and allocate it
void process_operator_token(char *input, t_token **tokens, int *index) {
    (*tokens)->type = OPERATOR;
    int current_index = *index;

    if (input[current_index] == '|') {
        // Pipe operator '|'
        create_new_token(tokens, input, current_index, current_index + 1);
        current_index += 1;  // Move past the operator
    } else if (input[current_index] == '<' || input[current_index] == '>') {
        // Redirection operators '<', '>', '<<', '>>'
        process_redirection_token(input, tokens, &current_index);
    }

    *index = current_index;  // Update the original index
}
