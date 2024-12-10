/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:20:43 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/10 14:25:59 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include ""

void execute_tree_commands(t_minishell *m) {
    t_command **commands = ast_to_command_list(m->tree_cmd);
    if (!commands) {
        prepare_signals();
        return;
    }
    debug_print_commands_array(commands);
    int cmd_count = count_commands_in_array(commands);
    if (cmd_count > 0)
        run_pipeline(m, commands, cmd_count);
    free(commands);
    prepare_signals();
}

