/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:41:27 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/10 14:42:38 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Frees a null-terminated array of strings.
void free_arr(char **arr)
{
    int i;

    if (!arr)
        return;

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
void free_list(t_list **list)
{
    t_list *temp;

    if (!list || !*list)
        return;

    while (*list)
    {
        temp = *list;
        *list = (*list)->next;
        free(temp);
        temp = NULL; // Prevent dangling pointer
    }
}

// Recursively frees a binary tree of `t_command` nodes.
void free_tree(t_command **tree)
{
    if (!tree || !*tree)
        return;

    t_command *node = *tree;

    if (node->left)
        free_tree(&node->left);
    if (node->right)
        free_tree(&node->right);
    if (node->argv)
        free_arr(node->argv);
    if (node->redir)
        free_all_tokens(&(node->redir));

    free(node);
    *tree = NULL; // Prevent dangling pointer
}

//free 
void	free_prompt(t_minishell *minishell)
{
	if (minishell->input)
		free(minishell->input);
	if (minishell->tokens)
		free_all_tokens(&(minishell->tokens));
	if (minishell->tree_cmd)
		free_tree(&(minishell->tree_cmd));
	if (minishell->pid_list)
		free_list(&(minishell->pid_list));
	minishell->input = NULL;
	minishell->tokens = NULL;
	minishell->tree_cmd = NULL;
	minishell->pid_list = NULL;
}

// Frees all resources associated with the minishell and exits.
void free_child(t_minishell *minishell)
{
    if (!minishell)
        return;

    free_all(minishell); // Function assumed to handle internal free operations
    exit(minishell->status);
}
