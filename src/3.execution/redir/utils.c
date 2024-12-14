/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorales <emorales@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 19:43:12 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/13 19:18:34 by emorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

int	open_file(char *filename, int flags, int mode)
{
	int	fd;

	fd = open(filename, flags, mode);
	if (fd < 0)
	{
		ft_putstr_fd("Error: error opening file \n", STDERR_FILENO);
	}
	return (fd);
}

int	redirect_fd(int fd, int std_fd)
{
	if (dup2(fd, std_fd) < 0)
	{
		perror("dup2");
		close(fd);
		return (EXIT_FAILURE);
	}
	close(fd);
	return (EXIT_SUCCESS);
}

void	remove_token_from_list(t_token **head, t_token *node)
{
	if (!head || !*head || !node)
		return ;
	if (node->prev)
		node->prev->next = node->next;
	else
		*head = node->next;
	if (node->next)
		node->next->prev = node->prev;
	free(node->content);
	free(node);
}

void	redir_append_node(t_token **redirs, int type, char *filename)
{
	t_token	*new_rd;

	initialize_token_list(&new_rd);
	if (!new_rd)
	{
		free(filename);
		return ;
	}
	new_rd->content = filename;
	new_rd->type = type;
	append_token(redirs, new_rd);
}
