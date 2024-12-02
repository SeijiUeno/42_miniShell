/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:40:02 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/01 21:03:01 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
#define AST_H

#include "../shell.h"
#include "../token/tokenizer.h"
#include "../execution/execution.h"

#define COMMAND_NODE 1
#define PIPE_NODE 2

// Function prototypes

char        **generate_argv(t_token *tokens, t_minishell *minishell);
t_token     *find_last_pipe(t_token *tokens);
t_token     *find_previous_pipe(t_token *token, t_minishell *minishell);
t_command   *new_tree_node(char **args);
t_command   *generate_command_node(t_token *token, t_minishell *minishell);
t_command   *generate_pipe_node(t_token *token, t_minishell *minishell);
void        tree_add_on_left(t_command **tree_root, t_command *new_node);
void        generate_tree(t_minishell *minishell);

// External functions used within the AST code
char        *expand_vars_and_quotes(char *content, t_minishell *minishell);
t_token     *generate_redirs(t_token **token, t_minishell *minishell);
char        **ft_split(const char *str, char c);
void        *ft_calloc(size_t count, size_t size);

#endif
