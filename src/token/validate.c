/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoted_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:51:36 by emorales          #+#    #+#             */
/*   Updated: 2024/12/09 16:47:27 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

// Count and validate a quoted sect
int check_trailing_token(t_token *tokens)
{
    t_token *current = tokens;

    // Traverse to the last token
    while (current && current->next)
        current = current->next;

    if (current->type == PIPE || current->type == REDIR_IN || current->type == REDIR_OUT ||
        current->type == APPEND || current->type == HEREDOC)
    {
        return error("minishell: ", "Syntax error near unexpected token `newline`", 1);
    }

    return 0; // No trailing issues
}

int check_token_sequence(t_token *tokens)
{
    t_token *current = tokens;

    while (current)
    {
        // Check for consecutive operators
        if (current->type == PIPE || current->type == REDIR_IN ||
            current->type == REDIR_OUT || current->type == APPEND || current->type == HEREDOC)
        {
            if (!current->next || (current->next->type == PIPE ||
                                    current->next->type == REDIR_IN ||
                                    current->next->type == REDIR_OUT ||
                                    current->next->type == APPEND ||
                                    current->next->type == HEREDOC))
            {
                return error("minishell: ", "Syntax error near unexpected token", 1);
            }
        }

        current = current->next;
    }

    return 0; // No sequence issues
}

int check_leading_token(t_token *tokens)
{
    if (!tokens)
        return error("minishell: ", "Empty input", 1);

    if (tokens->type == PIPE || tokens->type == REDIR_IN || tokens->type == REDIR_OUT ||
        tokens->type == APPEND || tokens->type == HEREDOC)
    {
        return error("minishell: ", "Syntax error near unexpected token", 1);
    }

    return 0; // No leading issues
}

int validate_tokens(t_token *tokens)
{
    // Check for leading syntax errors
    if (check_leading_token(tokens))
        return 1;

    // Check for syntax errors in the token sequence
    if (check_token_sequence(tokens))
        return 1;

    // Check for trailing syntax errors
    if (check_trailing_token(tokens))
        return 1;

    return 0; // No syntax errors found
}