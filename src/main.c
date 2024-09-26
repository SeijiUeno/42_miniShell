/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 19:14:55 by emorales          #+#    #+#             */
/*   Updated: 2024/09/26 18:10:43 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* main.c */

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
