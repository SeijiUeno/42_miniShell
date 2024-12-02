/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:05:19 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/02 17:09:38 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
#define EXPANSION_H

#include "../shell.h"

// Main expansion function
char *expand_vars_and_quotes(const char *input_str, t_minishell *minishell);

// Function declarations
char *expand_double_quotes(const char *input_str, int *index, t_minishell *minishell);
char *expand_word(const char *input_str, int *index);
char *expand_env(const char *var_name, char **envp);
char *expand_parameter(const char *input_str, int *index, t_minishell *minishell);
char *join_word(char *word, char *new_word);
char *expand_num_or_status(const char *input_str, int *index, t_minishell *minishell);
char *expand_until_char(const char *input_str, int *index, char stop_char);

#endif // EXPANSION_H
