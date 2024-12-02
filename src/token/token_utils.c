/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:39:52 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/01 20:39:06 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void initialize_token_list(t_token **tokens) {
    *tokens = (t_token *)gc_allocate(sizeof(t_token));
    if (!(*tokens))
        return;
    (*tokens)->type = -1;
    (*tokens)->content = NULL;
    (*tokens)->next = NULL;
    (*tokens)->prev = NULL;
}

// Add a new token to the end of the list
void append_token(t_token **token_list, t_token *new_token) {
    t_token *current = *token_list;

    // If the list is empty, set the new token as the first element
    if (!current) {
        *token_list = new_token;
        return;
    }

    // Traverse the list to find the last token
    while (current->next) {
        current = current->next;
    }

    // Add the new token at the end of the list
    current->next = new_token;
    new_token->prev = current; // Link the new token back to the previous one
}

// Free all tokens in the list
void free_all_tokens(t_token **token_list) {
    t_token *current = *token_list;
    t_token *next_token;

    // Iterate through the list and free each token
    while (current) {
        next_token = current->next; // Save the next token
        if (current->content) {
            gc_deallocate(current->content); // Free the token's content
        }
        gc_deallocate(current);             // Free the token itself
        current = next_token;      // Move to the next token
    }

    *token_list = NULL; // Set the list pointer to NULL after freeing
}

// Skip whitespace characters in the input string
void skip_whitespace(char *input, int *index) {
    // Advance the index while the current character is a whitespace
    while (input[*index] && ft_strchr(WHITESPACE, input[*index])) {
        (*index)++;
    }
}

// Allocate a new token with content from input[start] to input[end]
void create_new_token(t_token **tokens, char *input, int start, int end) {
    tokens[0]->content = gc_substr(input, start, end - start);

    if (input[end] != '\0') {
        initialize_token_list(&(tokens[0]->next)); // Initialize the next token
        tokens[0]->next->prev = tokens[0];        // Link the new token to the current one
        tokens[0] = tokens[0]->next;              // Move to the new token
    }
}

