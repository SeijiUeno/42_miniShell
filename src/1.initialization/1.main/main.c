/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:16:19 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/10 19:41:35 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

static void cleanup_minishell(t_minishell *minishell)
{
    free_all(minishell);
    if (minishell->stdin_backup >= 0)
        close(minishell->stdin_backup);
    if (minishell->stdout_backup >= 0)
        close(minishell->stdout_backup);
}

int main(void)
{
    t_minishell minishell;
    
    init_minishell(&minishell);
    shell_loop(&minishell);
    cleanup_minishell(&minishell);

    return EXIT_SUCCESS;
}
