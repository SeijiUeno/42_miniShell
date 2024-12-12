/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 19:48:54 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/12 19:33:49 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

/**
 * validate_redirection:
 * - Ensures that the redirection operator has a valid target token.
 * - Returns 0 if valid, -1 otherwise.
 */
static int validate_redirection(t_token *redir_op, t_token *redir_target)
{
    if (!redir_op)
        return (-1);
    if (!redir_target || redir_target->type != WORD)
        return (-1);
    return (0);
}

/**
 * process_single_redirection:
 * - Handles a single redirection operator and its target.
 * - Removes them from the main token list.
 */
static int process_single_redirection(
    t_token **token_list,
    t_token **redirs,
    t_token *redir_op,
    t_minishell *minishell)
{
    t_token *redir_target;
    char *expanded_filename;

    redir_target = redir_op->next;
    if (validate_redirection(redir_op, redir_target) < 0)
        return (-1);
    expanded_filename = expand_vars_and_quotes(redir_target->content, minishell);
    if (!expanded_filename)
        return (-1);
    redir_append_node(redirs, redir_op->type, expanded_filename);
    remove_token_from_list(token_list, redir_op);
    remove_token_from_list(token_list, redir_target);
    return (0);
}

/**
 * ft_generate_redirs:
 * - Processes all redirections in the token list until a PIPE is found.
 * - Builds a redirection list and removes processed tokens.
 */
t_token *ft_generate_redirs(t_token **token_list, t_minishell *minishell)
{
    t_token *redirs;
    t_token *current;

    redirs = NULL;
    current = *token_list;
    while (current && current->type != PIPE)
    {
        if (current->type == REDIR_IN || current->type == REDIR_OUT
            || current->type == APPEND || current->type == HEREDOC)
        {
            if (process_single_redirection(token_list, &redirs,
                    current, minishell) < 0)
                break;
            current = *token_list;
        }
        else
            current = current->next;
    }
    return (redirs);
}
