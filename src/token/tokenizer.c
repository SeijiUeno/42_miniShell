/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:51:36 by emorales          #+#    #+#             */
/*   Updated: 2024/09/26 17:40:38 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

t_token *tokenizer(char *input) {
    int i = 0;
    t_token *new_token;
    t_token *head = NULL;
    t_token *current = NULL;

    while (input[i] != '\0') {
        while (isspace((unsigned char)input[i]))
            i++;
        if (input[i] == '\0')
            break;

        if (is_operator(input[i]))
            new_token = create_operator_token(input, &i);
        else
            new_token = create_word_token(input, &i);

        if (!new_token) {
            free_tokens(head);
            return NULL;
        }

        if (head == NULL) {
            head = new_token;
            current = new_token;
        } else {
            current->next = new_token;
            current = new_token;
        }
    }
    return head;
}
