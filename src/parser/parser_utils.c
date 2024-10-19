/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:44:14 by marvin            #+#    #+#             */
/*   Updated: 2024/10/19 16:44:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_command *create_new_command() {
    t_command *cmd = malloc(sizeof(t_command));

    if (!cmd)
        return NULL;
    cmd->args = NULL;
    cmd->input_file = NULL;
    cmd->output_file = NULL;
    cmd->append = 0;
    cmd->next = NULL;
    return (cmd);
}

void free_command(t_command *cmd) {
    int i;

    if (cmd) {
        if (cmd->args) {
            i = 0;
            while (cmd->args[i]) {
                free(cmd->args[i]);
                i++;
            }
            free(cmd->args);
        }
        if (cmd->input_file)
            free(cmd->input_file);
        if (cmd->output_file)
            free(cmd->output_file);
        free(cmd);
    }
}

void free_command_list(t_command *cmd_head) {
    t_command *tmp;

    while (cmd_head) {
        tmp = cmd_head->next;
        free_command(cmd_head);
        cmd_head = tmp;
    }
}

int add_argument_to_command(t_command *cmd, char *arg) {
    char    **new_args;
    int     argc;
    int     i;

    // Check if cmd or arg is NULL
    if (!cmd || !arg)
        return (0);

    // Count current number of arguments
    argc = 0;
    if (cmd->args) {
        while (cmd->args[argc])
            argc++;
    }

    // Allocate memory for new_args (argc + 2 for the new arg and NULL terminator)
    new_args = malloc(sizeof(char *) * (argc + 2));
    if (!new_args)
        return (0); // Allocation failed

    // Copy existing arguments to new_args
    i = 0;
    while (i < argc)
    {
        new_args[i] = cmd->args[i];
        i++;
    }

    // Duplicate the new argument and add to new_args
    new_args[argc] = strdup(arg);
    if (!new_args[argc]) {
        free(new_args);
        return (0); // Allocation failed
    }

    new_args[argc + 1] = NULL; // Null-terminate the array

    // Free the old args array if it exists
    free(cmd->args);

    // Update cmd->args to point to the new array
    cmd->args = new_args;

    return (1); // Success
}
