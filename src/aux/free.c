/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:41:27 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/15 19:24:11 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	util_free_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		gc_deallocate(arr[i]);
		arr[i] = NULL;
		i++;
	}
	gc_deallocate(arr);
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
	t_command	*node;

	if (!tree || !*tree)
		return ;
	node = *tree;
	if (node->left)
		clear_tr(&node->left);
	if (node->right)
		clear_tr(&node->right);
	if (node->argv)
		util_free_array(node->argv);
	if (node->redir)
		clear_tok(&(node->redir));
	gc_deallocate(node);
	*tree = NULL;
}

void	util_free_child(t_ms *minishell)
{
	if (!minishell)
		return ;
	clear_al(minishell);
	exit(minishell->status);
}
