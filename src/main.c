/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorales <emorales@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 19:14:55 by emorales          #+#    #+#             */
/*   Updated: 2024/09/25 19:01:52 by emorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* main.c */

#include "shell.h"

void free_tokens(t_token *head) {
    t_token *current = head;
    t_token *next;
    while (current != NULL) {
        next = current->next;
        free(current->value);
        free(current);
        current = next;
    }
}

void print_tokens(t_token *head) {
    t_token *current = head;
    while (current != NULL) {
        printf("Token Value: '%s', Token Type: %d\n", current->value, current->type);
        current = current->next;
    }
}

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

        // Call the tokenizer
        tokens = tokenizer(input);

        // Print the tokens
        print_tokens(tokens);

        // Free tokens
        free_tokens(tokens); // Implement this function to free the token list

        free(input);
    }
	clear_history(); // Clear the history list (readlline f)
    return 0;
}