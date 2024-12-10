/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:42:46 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/09 19:42:04 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "tokenizer.h"


int validate_input(char *input);
t_token *tokenize_input(char *input);
int validate_all_quotes(char *input);

void generate_tokens(char *input, t_token **tokens)
{
    if (validate_input(input))
    {
        *tokens = NULL; // Set tokens to NULL if input is invalid
        return;
    }
    *tokens = tokenize_input(input);
    if (tokens)
        assign_operator_token_types(tokens);
}

int is_only_spaces(char *input)
{
    int i = 0;
    while (input[i] && ft_strchr(WHITESPACE, input[i]))
        i++;
    return (input[i] == '\0');
}

int validate_input(char *input)
{
    if (!input || !input[0])
        return error("minishell: ", "Empty input", EXIT_FAILURE);

    if (validate_all_quotes(input) != EXIT_SUCCESS)
        return error("minishell: ", "Unmatched quotes in input", EXIT_FAILURE);

    if (is_only_spaces(input))
        return error("minishell: ", "Input contains only whitespace", EXIT_FAILURE);

    return EXIT_SUCCESS;
}

void skip_quoted_token(char *input, int *index)
{
    char quote = input[*index];
    (*index)++; // Skip opening quote

    while (input[*index] && input[*index] != quote)
        (*index)++;

    if (input[*index] == quote)
        (*index)++; // Skip closing quote
}

void skip_whitespace(char *input, int *index)
{
    while (input[*index] && ft_strchr(WHITESPACE, input[*index]))
        (*index)++;
}

int validate_all_quotes(char *input)
{
    int index = 0;

    while (input[index])
    {
        if (ft_strchr(QUOTES, input[index]))
        {
            char quote = input[index];
            index++;
            while (input[index] && input[index] != quote)
                index++;

            if (!input[index])
                return EXIT_FAILURE;
        }
        index++;
    }
    return EXIT_SUCCESS;
}


void add_token(t_token **tokens, t_token **current, char *input, int start, int end)
{
    t_token *new_token = (t_token *)malloc(sizeof(t_token));
    if (!new_token)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    new_token->content = ft_substr(input, start, end - start);
    new_token->type = ft_strchr(SYMBOLS, input[start]) ? OPERATOR : WORD;
    new_token->next = NULL;
    new_token->prev = NULL;

    if (*current)
    {
        (*current)->next = new_token;
        new_token->prev = *current;
    }
    else
    {
        *tokens = new_token;
    }
    *current = new_token;
}

void assign_operator_token_types(t_token **tokens)
{
    t_token *current = *tokens;

    while (current)
    {
        if (current->type == OPERATOR) // Only process operator tokens
        {
            char op_char = current->content[0];

            // Assign specific operator type
            if (op_char == '|')
            {
                current->type = PIPE;
            }
            else if (op_char == '<')
            {
                if (current->content[1] == '<') // Handle '<<'
                    current->type = HEREDOC;
                else
                    current->type = REDIR_IN;
            }
            else if (op_char == '>')
            {
                if (current->content[1] == '>') // Handle '>>'
                    current->type = APPEND;
                else
                    current->type = REDIR_OUT;
            }
        }
        current = current->next;
    }
}

t_token *tokenize_input(char *input)
{
    t_token *tokens = NULL;
    t_token *current = NULL;
    int index = 0;

    while (input[index])
    {
        skip_whitespace(input, &index); // Skip leading whitespace

        if (input[index] && ft_strchr(SYMBOLS, input[index]))
        {
            if ((input[index] == '<' && input[index + 1] == '<') 
                || (input[index] == '>' && input[index + 1] == '>'))
            {
                add_token(&tokens, &current, input, index, index + 2);
                index += 2;
            }
            else
            {
                add_token(&tokens, &current, input, index, index + 1);
                index++;
            }
        }
        else if (input[index])
        {
            // Process words (handles quotes)
            int start = index;
            while (input[index] && !ft_strchr(WHITESPACE, input[index]) && !ft_strchr(SYMBOLS, input[index]))
            {
                if (ft_strchr(QUOTES, input[index]))
                    skip_quoted_token(input, &index); // Skip quoted segments
                else
                    index++;
            }
            add_token(&tokens, &current, input, start, index);
        }
    }

    return tokens;
}