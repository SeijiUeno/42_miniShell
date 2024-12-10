/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:16:19 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/10 17:30:53 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int main(void)
{
    t_minishell minishell;

    init_minishell(&minishell);
    shell_loop(&minishell);
    cleanup_minishell(&minishell);

    return EXIT_SUCCESS;
}
