/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:39:59 by sueno-te          #+#    #+#             */
/*   Updated: 2024/10/30 17:20:29 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_token *pipe_search(t_token *list_tokens)
{
    t_token *token;

    token = list_tokens;
    while(token != NULL)
    {
        if (token->type == TOKEN_PIPE)
            return (token);
    }
    return (NULL);
}

static void create_nodes(t_ast *ast_node, t_token *list_tokens)
{
    pipe_search(list_tokens);
    ast_node->type = TOKEN_WORD;
    ast_node->exec = list_tokens;
}

t_ast   *tree_constructor(t_token *tokens)
{
    // main root
    t_ast   *tree_root;
    
    // !!!!!ALOCATION - do not forget to free!!!!!
    tree_root = ft_calloc(1, sizeof(t_ast));
    if (!tree_root)
    {
        return (NULL);
    }
    create_nodes(tree_root, tokens);
    return(tree_root);
}


