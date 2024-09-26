/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorales <emorales@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:51:36 by emorales          #+#    #+#             */
/*   Updated: 2024/09/25 19:40:20 by emorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

int is_operator(char c) {
    return (c == '|' || c == '>' || c == '<' || c == '&' || c == ';');
}

t_token *create_operator_token(char *input, int *index) {
    t_token *token;
    int     i;
    char    op[3];

    token = (t_token *)malloc(sizeof(t_token));
    if (!token)
        return (NULL);
    i = *index;

    // Handle operators with two characters (like '>>' and '<<')
    if ((input[i] == '>' && input[i + 1] == '>') ||
        (input[i] == '<' && input[i + 1] == '<')) {
        op[0] = input[i++];
        op[1] = input[i++];
        op[2] = '\0';
    } else {
        op[0] = input[i++];
        op[1] = '\0';
    }

    token->value = ft_strdup(op);
    *index = i;

    // Assign the correct token type based on the operator
    if (ft_strcmp(token->value, "|") == 0)
        token->type = TOKEN_PIPE;
    else if (ft_strcmp(token->value, ">") == 0)
        token->type = TOKEN_REDIRECT_OUT;
    else if (ft_strcmp(token->value, ">>") == 0)
        token->type = TOKEN_REDIRECT_APPEND;
    else if (ft_strcmp(token->value, "<") == 0)
        token->type = TOKEN_REDIRECT_IN;
    else if (ft_strcmp(token->value, "<<") == 0)
        token->type = TOKEN_HEREDOC;
    else
        token->type = TOKEN_OPERATOR; // For any other operators
    token->next = NULL;
    return (token);
}

t_token *create_word_token(char *input, int *index) {
    t_token *token;
    int     i = *index;
    int     start = i;
    int     in_single_quote = 0;
    int     in_double_quote = 0;

    token = (t_token *)malloc(sizeof(t_token));
    if (!token)
        return (NULL);

    while (input[i] != '\0' && 
           (in_single_quote || in_double_quote || 
           (!is_operator(input[i]) && input[i] != ' ' && input[i] != '\t'))) {

        if (input[i] == '\'' && !in_double_quote)
            in_single_quote = !in_single_quote;
        else if (input[i] == '\"' && !in_single_quote)
            in_double_quote = !in_double_quote;
        i++;
    }

    token->value = ft_substr(input, start, i - start);
    token->type = TOKEN_WORD;
    token->next = NULL;
    *index = i;
    return (token);
}

t_token *tokenizer(char *input) {
    int     i;
    t_token *new_token;
    t_token *head;
    t_token *current;

    i = 0;
    head = NULL;
    current = NULL;
    while (input[i] != '\0') {
        while (input[i] == ' ' || input[i] == '\t')
            i++;
        if (input[i] == '\0')
            break;
        if (is_operator(input[i]))
            new_token = create_operator_token(input, &i);
        else
            new_token = create_word_token(input, &i); // to be implemented
        if (head == NULL) {
            head = new_token;
            current = new_token;
        } else {
            current->next = new_token;
            current = new_token;
        }
    }
    return (head);
}
