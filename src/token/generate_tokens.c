/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:42:46 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/01 21:16:51 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "tokenizer.h"

static void advance_until_delimiter(char *input, int *current_index) {
    while (input[*current_index]
           && !ft_strchr(WHITESPACE, input[*current_index])
           && !ft_strchr(SYMBOLS, input[*current_index])) {
        if (ft_strchr(QUOTES, input[*current_index])) {
            skip_quoted_token(input, current_index); // Handle quoted sections
        } else {
            (*current_index)++;
        }
    }
}

// Process a word token from the input
void extract_word_token(char *input, t_token **tokens, int *current_index) {
    int start_index = *current_index;

    (*tokens)->type = WORD;

    // Use the auxiliary function to advance the index
    advance_until_delimiter(input, current_index);

    if (*current_index > start_index) {
        create_new_token(tokens, input, start_index, *current_index);
    }
}


// Split the input into tokens
static void tokenize_input(char *input, t_token **tokens) {
    t_token *aux = *tokens;
    int i = 0;

    while (input[i]) {
        skip_whitespace(input, &i);
        if (input[i] && ft_strchr(SYMBOLS, input[i]))
            process_operator_token(input, &aux, &i);
        else if (input[i])
            extract_word_token(input, &aux, &i);
    }
}

// Remove tokens with null content from the list
static void remove_empty_tokens(t_token **tokens) {
    t_token *current = *tokens;
    t_token *prev = NULL;

    while (current) {
        if (!current->content) {
            t_token *to_free = current;
            if (prev)
                prev->next = current->next;
            else
                *tokens = current->next;
            current = current->next;
            gc_deallocate(to_free);
        } else {
            prev = current;
            current = current->next;
        }
    }
}

// Check if the input contains only whitespace characters
static int is_only_spaces(char *input) {
    int i = 0;
    while (input[i] && ft_strchr(WHITESPACE, input[i]))
        i++;
    return (input[i] == '\0');
}

// Main function to tokenize the input string
void generate_tokens(char *input, t_token **tokens) {
    if (!input || !input[0] || validate_all_quotes(input) || is_only_spaces(input))
        return;
    initialize_token_list(tokens);
    tokenize_input(input, tokens);
    remove_empty_tokens(tokens);
}
