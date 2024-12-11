/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 19:43:12 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/11 19:46:53 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

int open_file(char *filename, int flags, int mode)
{
	int fd;

	fd = open(filename, flags, mode);
	if (fd < 0)
	{
		fprintf(stderr, "minishell: error opening file '%s': %s\n",
			filename, strerror(errno));
	}
	return (fd);
}

int redirect_fd(int fd, int std_fd)
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

void remove_token_from_list(t_token **head, t_token *node)
{
    if (!head || !*head || !node)
        return;
    if (node->prev)
        node->prev->next = node->next;
    else
        *head = node->next;
    if (node->next)
        node->next->prev = node->prev;
    free(node->content);
    free(node);
}

void append_redirection_node(t_token **redirs, int type, char *filename)
{
    t_token *new_rd;

    initialize_token_list(&new_rd);
    if (!new_rd)
    {
        free(filename);
        return;
    }
    new_rd->content = filename;
    new_rd->type = type;
    append_token(redirs, new_rd);
}
