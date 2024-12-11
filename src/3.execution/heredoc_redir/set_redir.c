/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 20:12:10 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/11 19:33:45 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

static void remove_token_from_list(t_token **head, t_token *node) {
    if (!head || !*head || !node)
        return;
    if (node->prev)
        node->prev->next = node->next;
    else
        *head = node->next;
    if (node->next)
        node->next->prev = node->prev;
    free(node->content);
    free(node);
}

static void append_redirection_node(t_token **redirs, int type, char *filename) {
    t_token *new_rd;
    initialize_token_list(&new_rd);
    if (!new_rd) {
        free(filename);
        return;
    }
    new_rd->content = filename;
    new_rd->type = type;
    append_token(redirs, new_rd);
}

/**
 * ft_generate_redirs:
 * - Scans the token list for redirection operators (<, >, >>, <<).
 * - For each operator found, retrieves its target token.
 * - Removes both operator and target tokens from the main list.
 * - Adds a corresponding node to the `redirs` list with the expanded filename.
 * Returns the `redirs` list containing all redirection info for the command.
 */
 
t_token *ft_generate_redirs(t_token **token_list, t_minishell *minishell) {
    t_token *redirs = NULL;
    t_token *current = *token_list;

    while (current && current->type != PIPE) {
        if (current->type == REDIR_IN || current->type == REDIR_OUT
            || current->type == APPEND || current->type == HEREDOC) {
            
            t_token *redir_op = current;
            t_token *redir_target = redir_op->next;

            // Validate the target
            if (!redir_target || redir_target->type != WORD) {
                // Handle syntax error if necessary
                break;
            }

            // Expand filename
            char *expanded_filename = expand_vars_and_quotes(redir_target->content, minishell);

            // Add redirection info to the redirs list
            append_redirection_node(&redirs, redir_op->type, expanded_filename);

            // Remove operator and target from the token list
            remove_token_from_list(token_list, redir_op);
            remove_token_from_list(token_list, redir_target);

            // After removal, reset current to the start of the updated list
            current = *token_list;
        } else {
            current = current->next;
        }
    }
    return redirs;
}
