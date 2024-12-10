/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 18:56:46 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/10 18:51:16 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

static int parse_input(t_minishell *minishell)
{
    generate_tokens(minishell->input, &(minishell->tokens));
    if (!(minishell->tokens) || !(minishell->tokens->content))
        return error("minishell: ", "Empty or invalid input", 1);
    if (validate_tokens(minishell->tokens) != EXIT_SUCCESS)
        return error("minishell: ", "Invalid syntax in input", 1);
    return EXIT_SUCCESS;
}

static int handle_heredocs(t_minishell *minishell)
{
    int status = verify_heredoc(minishell);
    if (status != EXIT_SUCCESS)
    {
        minishell->status = status;
        return status;
    }
    return EXIT_SUCCESS;
}

int build_commands(t_minishell *minishell)
{
    if (parse_input(minishell) != EXIT_SUCCESS)
        return EXIT_FAILURE;

    if (handle_heredocs(minishell) != EXIT_SUCCESS)
        return EXIT_FAILURE;

    generate_ast(minishell);
    return EXIT_SUCCESS;
}