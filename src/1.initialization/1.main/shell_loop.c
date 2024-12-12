/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorales <emorales@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:36:28 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/12 17:39:39 by emorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

static int get_and_reset_status(void)
{
    int current_status;

    current_status = control_status(STATUS_GET);
    control_status(0);
    return (current_status);
}

static char *handle_input(void)
{
    char *input = readline("minishell$ ");
    if (input && input[0] != '\0') // Add input to history only if non-empty
        add_history(input);
    return input;
}

static void process_commands(t_minishell *minishell)
{
    if (build_commands(minishell) == EXIT_SUCCESS)
        execute_tree_commands(minishell);
}

static void cleanup_iteration(t_minishell *minishell)
{
    prompt_clear(minishell);
    reset_fds(minishell); // Restore stdin and stdout
}

void shell_loop(t_minishell *minishell)
{
    static struct termios original_term;
    
    save_terminal_settings(&original_term);
    while (1)
    {
        minishell->input = handle_input();
        minishell->status = get_and_reset_status();
        if (!minishell->input) // Handle EOF (Ctrl+D)
        {
            //**************** ft_printf("BY SHELL!\n");
            break;
        }
        process_commands(minishell);
        cleanup_iteration(minishell);
    }
    restore_terminal_settings(&original_term); // Final cleanup
}