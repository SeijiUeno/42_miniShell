/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:36:28 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/10 14:36:31 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
    free_prompt(minishell);
    reset_fds(minishell); // Restore stdin and stdout
}

void shell_loop(t_minishell *minishell)
{
    while (1)
    {
        minishell->input = handle_input();
        if (!minishell->input) // Handle EOF (Ctrl+D)
        {
            ft_printf("BY SHELL!\n");
            break;
        }
        process_commands(minishell);
        cleanup_iteration(minishell);
    }
}