/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:41:27 by sueno-te          #+#    #+#             */
/*   Updated: 2025/01/02 17:37:20 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	util_free_array(char **arr)
{
	arr = (NULL);
}

void	clear_li(t_list **list)
{
	t_list	*temp;

	if (!list || !*list)
		return ;
	while (*list)
	{
		temp = *list;
		*list = (*list)->next;
		gc_deallocate(temp);
		temp = NULL;
	}
}

void	clear_tr(t_command **tree)
{
	*tree = NULL;
}

void	util_free_child(t_ms *minishell)
{
	if (!minishell)
		return ;
	clear_al(minishell);
	exit(minishell->status);
}
