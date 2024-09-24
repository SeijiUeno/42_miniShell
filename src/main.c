/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 19:14:55 by emorales          #+#    #+#             */
/*   Updated: 2024/09/24 17:17:46 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* main.c */

#include "shell.h"

int main(void) {
    char *input;

    signal_init(); // init signal handling
    while (1) {
        input = readline("myshell> ");

        if (!input) {
            printf("\nExiting shell...\n");
            break;
        }

        if (*input) {
            add_history(input);
        }

        printf("You entered: %s\n", input);
        free(input);
    }
    clear_history(); // Clear the history list (readlline f)
    return 0;
}
