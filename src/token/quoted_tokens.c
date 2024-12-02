/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoted_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:51:36 by emorales          #+#    #+#             */
/*   Updated: 2024/12/01 20:51:55 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

// Count and validate a quoted section in the input
int validate_and_count_quote(char quote, int start_index, char *input) {
    int index = start_index;

    // Check for the opening quote
    if (input[index] && input[index] == quote) {
        index++;
        // Look for the closing quote
        while (input[index] && input[index] != quote) {
            index++;
        }
        // If no closing quote is found, return an error
        if (!input[index]) {
            return -1;
        }
    }
    return index + 1; // Move past the closing quote
}

// Count and validate all quotes in the input
int validate_all_quotes(char *input) {
    int index = 0;

    while (input[index]) {
        if (ft_strchr(QUOTES, input[index])) {
            // Handle either single or double quotes
            if (input[index] == '"') {
                index = validate_and_count_quote('"', index, input);
            } else {
                index = validate_and_count_quote('\'', index, input);
            }
            // Return an error if unmatched quotes are found
            if (index < 0) {
                return error("minishell: ", "You need to close your quotes!", 1);
            }
        } else {
            index++; // Move to the next character
        }
    }
    return 0; // No unmatched quotes
}

// Process a quoted token in the input
void skip_quoted_token(char *input, int *current_index) {
    int index = *current_index;
    char quote_type = input[index];

    index++; // Move past the opening quote
    // Look for the closing quote
    while (input[index] && input[index] != quote_type) {
        index++;
    }
    // Move past the closing quote if it exists
    if (input[index] == quote_type) {
        index++;
    }

    *current_index = index; // Update the original index
}
