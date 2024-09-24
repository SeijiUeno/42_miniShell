/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: null <null@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 19:14:55 by emorales          #+#    #+#             */
/*   Updated: 2024/09/24 16:45:10 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* main.c */

#include "shell.h"

int main() {
    char *input;

    while (1) {
        input = readline("Champions$ > ");

        /* Handle EOF (Ctrl+D) */
        if (!input) {
            printf("\n");
            break;
        }

        /* Add non-empty input to history */
        if (*input) {
            add_history(input);
        }

        /* Echo the input back */
        printf("You entered: %s\n", input);

        /* Free the allocated memory */
        free(input);
    }

    return 0;
}
