/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:41:27 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/15 05:24:44 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

// Frees a null-terminated array of strings.
void	util_free_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL; // Prevent dangling pointer
		i++;
	}
	free(arr);
	arr = NULL; // Prevent dangling pointer
}

// Frees a linked list of `t_list` nodes.
void	clear_li(t_list **list)
{
	t_list	*temp;

	if (!list || !*list)
		return ;
	while (*list)
	{
		temp = *list;
		*list = (*list)->next;
		free(temp);
		temp = NULL; // Prevent dangling pointer
	}
}

// Recursively frees a binary tree of `t_command` nodes.
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
	free(node);
	*tree = NULL; // Prevent dangling pointer
}

// Frees all resources associated with the minishell and exits.
void	util_free_child(t_ms *minishell)
{
	if (!minishell)
		return ;
	clear_al(minishell); // Function assumed to handle internal free operations
	exit(minishell->status);
}
