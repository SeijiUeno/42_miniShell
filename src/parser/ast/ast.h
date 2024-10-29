#ifndef PARSER_H
# define PARSER_H

# include <stdlib.h>
# include "../libft/libft.h"

// Command Node Structure for Abstract Syntax Tree (AST)
typedef struct s_ast {
	char				**argv;
	int					argc;
	t_token_type		type;
	struct s_command	*left;
	struct s_command	*right;
	struct s_command	*parent;
}	t_ast;

// Minishell Structure (Main Shell Context)

typedef struct s_minishell {
	t_token		*tokens;    // Token list for the input commands
	t_command	*tree_cmd;  // Root of the command tree
}	t_minishell;

// Function Prototypes

// Generate command and pipe nodes
t_ast	*generate_command_node(t_token *token, t_minishell *shell);
t_ast	*generate_pipe_node(t_token *token, t_minishell *shell);

// Generate the full AST for the shell
void		generate_command_tree(t_minishell *shell);

// Token utilities
t_token		*find_last_pipe(t_token *tokens);
t_token		*find_previous_pipe(t_token *current, t_minishell *shell);

// Create a new command node
t_ast	*create_command_node(char **args);

// Generate argv from token list
char		**generate_argv(t_token *token_list, t_minishell *shell);

// Add nodes to the left or right of the tree
void		tree_add_left(t_ast **root, t_ast *new_node);
void		tree_add_right(t_ast **root, t_ast *new_node);

#endif
