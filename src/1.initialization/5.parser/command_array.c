/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:17:34 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/10 14:23:41 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int count_pipeline_commands(t_command *node) {
    if (!node)
        return (0);
    if (node->type == PIPE)
        return (count_pipeline_commands(node->left) + count_pipeline_commands(node->right));
    return (1);
}

static void fill_commands_array(t_command *node, t_command **array, int *index) {
    if (!node)
        return;
    if (node->type == PIPE) {
        fill_commands_array(node->left, array, index);
        fill_commands_array(node->right, array, index);
    } else {
        array[*index] = node;
        (*index)++;
    }
}

t_command **ast_to_command_list(t_command *root) {
    t_command **array;
    int cmd_count;
    int start_index;

    if (!root)
        return (NULL);
    cmd_count = count_pipeline_commands(root);
    if (cmd_count <= 0)
        return (NULL);
    array = ft_calloc(sizeof(t_command *), cmd_count + 1);
    if (!array)
        return (NULL);
    start_index = 0;
    fill_commands_array(root, array, &start_index);
    array[cmd_count] = NULL;
    return (array);
}

int count_commands_in_array(t_command **commands) {
    int count = 0;
    while (commands && commands[count])
        count++;
    return (count);
}
