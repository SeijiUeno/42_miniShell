/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:39:59 by sueno-te          #+#    #+#             */
/*   Updated: 2024/10/30 18:43:00 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_token *pipe_search(t_token *list_tokens) {
    t_token *token = list_tokens;
    t_token *before_split = NULL;

    while (token != NULL) {
        if (token->type == TOKEN_OPERATOR) {
            return before_split;
        }
        before_split = token; // Move after checking the pipe
        token = token->next;
    }
    return NULL;
}

t_token *token_spliter(t_token *list, t_token *boundary) {
    t_token *new_node = NULL;
    t_token *temp;

    if (!list || !boundary || !(temp = boundary->next))
        return NULL;

    if (temp->next != NULL)
        new_node = temp->next;

    boundary->next = NULL;
    free(temp); // Ensure this is safe to do
    return new_node;
}

int single_node_creation(t_ast *ast_node, t_token *list_tokens, t_token *boundary)
{
    t_token *right_branch;

    if(!ast_node || !list_tokens || !boundary)
        return(0);
    ast_node->type = (boundary->type);
    right_branch = token_spliter(list_tokens, boundary);
    if (!right_branch)
        return(1); //ERROR IN SPLITTER!!!!
    ast_node->left = tree_constructor(list_tokens);
    ast_node->right = tree_constructor(right_branch);
    return(0);
}

static void create_nodes(t_ast *ast_node, t_token *list_tokens)
{
    t_token *boundary_token;

    boundary_token = pipe_search(list_tokens);
    if (boundary_token != NULL)
    {
        if (single_node_creation(ast_node, list_tokens, boundary_token) != 0)
        {
            return;
        }
        ast_node->type = TOKEN_PIPE;
        ast_node->exec = NULL;
    }
    else
    {
        ast_node->type = list_tokens->type;
        ast_node->exec = list_tokens;
        ast_node->left = NULL;
        ast_node->right = NULL;
    }
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


// print aux

void print_type(int type) {
    if (type == TOKEN_PIPE)
        printf("Type: PIPE\n");
    else if (type == TOKEN_WORD)
        printf("Type: WORD\n");
    else
        printf("Type: UNKNOWN (%d)\n", type);
}

// Print a single token's value (handles null tokens safely)
void print_token(t_token *token) {
    if (token && token->value)
        printf("Exec: %s\n", token->value);
    else
        printf("Exec: (null)\n");
}

// Recursive function to print the AST nodes in pre-order (Node, Left, Right)
void print_ast(t_ast *node, int indent) {
    if (node == NULL) {
        printf("%*s(NULL)\n", indent, "");
        return;
    }

    // Print current node's details with indentation
    printf("%*sNode:\n", indent, "");
    printf("%*s", indent + 2, "");
    print_token(node->exec);  // Print token value (command or word)
    printf("%*s", indent + 2, "");
    print_type(node->type);   // Print the node's type

    // Recursively print the left and right children
    printf("%*sLeft:\n", indent, "");
    print_ast(node->left, indent + 4);  // Increase indentation for children

    printf("%*sRight:\n", indent, "");
    print_ast(node->right, indent + 4);
}