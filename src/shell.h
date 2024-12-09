/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:05:19 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/09 19:59:10 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

#include <errno.h>
#include <limits.h>
#include <unistd.h> // For STDOUT_FILENO and getcwd
#include <stdlib.h> // For EXIT_FAILURE and EXIT_SUCCESS
/* Include Readline */
# include <readline/readline.h>
# include <readline/history.h>
/* Include Signal */
# include <signal.h>
/* Include lib */

/* Include env */
#include "../env/env.h"

# include "token/tokenizer.h"
# include "execution/execution.h"

	# define STATUS_GET -1
	# define STATUS_SIGINT 130
	# define STATUS_SIGQUIT 131

# define WHITESPACE " \t\n\r\v\f"
# define SYMBOLS "|<>"
# define QUOTES "'\""

typedef struct s_minishell	t_minishell;
typedef struct s_token		t_token;
typedef enum e_token_type	t_token_type;

struct s_minishell
{
	int			status;
	char		*input;
	char		**envp;
	char		**path;
	int			stdin_backup;
	int			stdout_backup;
	t_token		*tokens;
	t_command	*tree_cmd;
};

struct s_token
{
	int				type;
	char			*content;
	struct s_token	*next;
	struct s_token	*prev;
};

enum e_operator_type
{
	PIPE = 1,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
	WORD,
	OPERATOR,
};

// Tokenizer Functions
void generate_tokens(char *input, t_token **tokens);
void assign_operator_token_types(t_token **tokens);
void initialize_token_list(t_token **tokens);
void append_token(t_token **token_list, t_token *new_token);
void free_all_tokens(t_token **tokens);

// Token Validation Functions
int validate_tokens(t_token *tokens);
int check_leading_token(t_token *tokens);
int check_trailing_token(t_token *tokens);
int check_token_sequence(t_token *tokens);
int is_redirection(int token_type);
void append_redirection(t_token **redirections, t_token *redir, t_token *redir_target, t_minishell *minishell);

#endif