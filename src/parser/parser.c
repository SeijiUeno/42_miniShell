/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 16:25:18 by marvin            #+#    #+#             */
/*   Updated: 2024/10/12 16:25:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token *current_token;

void advance_token() {
    if (current_token != NULL)
        current_token = current_token->next;
}

void parse_input(t_token *head_of_tokens) {
    // Initialize current_token as the head of the token list
    current_token = head_of_tokens;  // 'head_of_tokens' is the start of the linked list

    // Check if we have a pipeline or a simple command
    if (current_token && current_token->type == TOKEN_WORD) {
        parse_pipeline();
    } else if (current_token && current_token->type == TOKEN_EOF) {
        printf("End of input\n");
    } else {
        printf("Error: Invalid input\n");
    }
}

void parse_command() {
    // The command should start with a TOKEN_WORD (command name)
    if (current_token && current_token->type == TOKEN_WORD) {
        printf("Command: %s\n", current_token->value);
        advance_token();
        
        // While we have TOKEN_WORD, continue as arguments
        while (current_token && current_token->type == TOKEN_WORD) {
            printf("Argument: %s\n", current_token->value);
            advance_token();
        }

        // Handle possible redirections
        parse_redirection();
    } else {
        printf("Error: Expected a command\n");
    }
}

void parse_pipeline() {
    // Start with the first command
    parse_command();

    // While we find TOKEN_PIPE, continue parsing the next command
    while (current_token && current_token->type == TOKEN_PIPE) {
        printf("Pipe found\n");
        advance_token();  // Consume the '|'
        
        // Parse the next command after the pipe
        parse_command();
    }
}

void parse_redirection() {
    while (current_token && 
           (current_token->type == TOKEN_REDIRECT_IN ||
            current_token->type == TOKEN_REDIRECT_OUT ||
            current_token->type == TOKEN_REDIRECT_APPEND ||
            current_token->type == TOKEN_HEREDOC)) {
        
        t_token_type redir_type = current_token->type;
        advance_token();  // Consume the redirection token
        
        if (current_token && current_token->type == TOKEN_WORD) {
            printf("Redirection of type %d to file: %s\n", redir_type, current_token->value);
            advance_token();  // Consume the file name
        } else {
            printf("Error: Expected a file name after redirection\n");
        }
    }
}
