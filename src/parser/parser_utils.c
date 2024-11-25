/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:44:14 by marvin            #+#    #+#             */
/*   Updated: 2024/11/25 18:15:59 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_command	*create_new_command(void)
{
	t_command	*cmd;

	cmd = gc_allocate(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->input_file = NULL;
	cmd->output_file = NULL;
	cmd->append = 0;
	cmd->next = NULL;
	return (cmd);
}

void	gc_deallocate_command(t_command *cmd)
{
	int	i;

	if (cmd)
	{
		if (cmd->args)
		{
			i = 0;
			while (cmd->args[i])
			{
				gc_deallocate(cmd->args[i]);
				i++;
			}
			gc_deallocate(cmd->args);
		}
		if (cmd->input_file)
			gc_deallocate(cmd->input_file);
		if (cmd->output_file)
			gc_deallocate(cmd->output_file);
		gc_deallocate(cmd);
	}
}

void	gc_deallocate_command_list(t_command *cmd_head)
{
	t_command	*tmp;

	while (cmd_head)
	{
		tmp = cmd_head->next;
		gc_deallocate_command(cmd_head);
		cmd_head = tmp;
	}
}

int	add_argument_to_command(t_command *cmd, char *arg)
{
	char	**new_args;
	int		argc;
	int		i;

	//Check if cmd or arg is NULL
	if (!cmd || !arg)
		return (0);
	//Count current number of arguments
	argc = 0;
	if (cmd->args)
	{
		while (cmd->args[argc])
			argc++;
	}
	//Allocate memory for new_args (argc + 2 for the new arg and NULL terminator)
	new_args = gc_allocate(sizeof(char *) * (argc + 2));
	if (!new_args)
		return (0); // Allocation failed
	// Copy existing arguments to new_args
	i = 0;
	while (i < argc)
	{
		new_args[i] = cmd->args[i];
		i++;
	}
	//Duplicate the new argument and add to new_args
	new_args[argc] = gc_strdup(arg);
	if (!new_args[argc])
	{
		gc_deallocate(new_args);
		return (0); // Allocation failed
	}
	new_args[argc + 1] = NULL; // Null-terminate the array
	//gc_deallocate the old args array if it exists
	gc_deallocate(cmd->args);
	//Update cmd->args to point to the new array
	cmd->args = new_args;
	return (1); // Success
}
