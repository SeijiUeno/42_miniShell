/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:42:46 by sueno-te          #+#    #+#             */
/*   Updated: 2024/09/26 18:13:31 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int is_operator(char c) {
    return (c == '|' || c == '>' || c == '<' || c == '&' || c == ';');
}
/*test main funtion
# include "shell.h"
# include "token/tokenizer.h"

int main(void) {
    char *input;
    t_token *tokens;

    while (1) {
        input = readline("myshell> ");
        if (!input) {
            printf("\nExiting shell...\n");
            break;
        }
        if (*input)
            add_history(input);

        tokens = tokenizer(input);
        if (tokens == NULL) {
            // **An error occurred during tokenization**
            // You can choose to continue or exit
            free(input);
            continue; // Skip this iteration and prompt again
        }
        print_tokens(tokens);
        free_tokens(tokens);
        free(input);
    }
	clear_history();
    return 0;
}

*/
// Function to get the token type as a string
const char *get_token_type_name(t_token_type type) {
    switch (type) {
        case TOKEN_WORD: return "TOKEN_WORD";
        case TOKEN_OPERATOR: return "TOKEN_OPERATOR";
        case TOKEN_PIPE: return "TOKEN_PIPE";
        case TOKEN_REDIRECT_IN: return "TOKEN_REDIRECT_IN";
        case TOKEN_REDIRECT_OUT: return "TOKEN_REDIRECT_OUT";
        case TOKEN_REDIRECT_APPEND: return "TOKEN_REDIRECT_APPEND";
        case TOKEN_HEREDOC: return "TOKEN_HEREDOC";
        default: return "UNKNOWN";
    }
}

// Function to print tokens
void print_tokens(t_token *head) {
    t_token *current = head;
    printf("----------------------------TOKENS------------------------------------\n");
    while (current != NULL) {
        printf("Token Value: '%s', Token Type: %s\n", current->value, get_token_type_name(current->type));
        current = current->next;
    }
    printf("------------------------------END-------------------------------------\n");
}

