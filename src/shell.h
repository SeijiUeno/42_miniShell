/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:05:19 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/10 14:46:01 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define MINISHELL_H

# include <limits.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <termios.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/types.h>
# include <dirent.h>

# define STATUS_GET -1
# define STATUS_SIGINT 130
# define STATUS_SIGQUIT 131

# define WHITESPACE " \t\n\r\v\f"
# define SYMBOLS "|<>"
# define QUOTES "'\""

typedef struct s_minishell	t_minishell;
typedef struct s_token		t_token;
typedef struct s_command	t_command;
typedef struct s_pid		t_pid;
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
	t_list		*pid_list;
};

struct s_token
{
	int				type;
	char			*content;
	struct s_token	*next;
	struct s_token	*prev;
};

struct s_command
{
	char				**argv;
	t_token				*redir;
	int					argc;
	int					fd[2];
	int					type;
	struct s_command	*left;
	struct s_command	*right;
	struct s_command	*parent;
};

struct s_pid
{
	int				pid;
	struct s_pid	*next;
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


void shell_loop(t_minishell *minishell);
void init_minishell(t_minishell *minishell);

// signals
void		prepare_signals(void);
void		handle_signal(int signum);
void		handle_signal_exec(int signum);
// status
int			control_status(int status);
int			filter_status(int status);

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

// AST Functions
void generate_ast(t_minishell *minishell);
t_command *parse_pipeline(t_token **tokens, t_minishell *minishell);
t_command *parse_command(t_token **tokens, t_minishell *minishell);
t_token *parse_redirections(t_token **tokens, t_minishell *minishell);
void free_tree(t_command **tree);
// Argument Parsing for Commands
char **generate_argv(t_token *tokens, t_minishell *minishell);
int count_args(t_token *tokens);

// Debugging Functions
void debug_print_tree(t_command *node, int level);

// get envs
char		**get_env(char **envp);
char		**get_paths(char **env);
char		*get_single_env(char *env_name, char **envp);
int			verify_abs_path(char *path);
char		*verify_path(char *bin, char **path);

// bultins
int			pwd(void);
int			change_dir(char **path, t_minishell *minishell);
int			unset(const char **key, t_minishell *minishell);
int			export(char **args, t_minishell *minishell);
char		*validate_var_name(char *var);
int			print_order_env(char **env);
int			echo(char **args);
int			exit_builtin(char **args, t_minishell *minishell);
int			is_builtin(char **command, t_minishell *minishell);
// builds
int			build_commands(t_minishell *minishell);
void		process_input(t_minishell *minishell);
// expansor

// Function declarations
char *expand_vars_and_quotes(const char *input_str, t_minishell *minishell);
char *expand_double_quotes(const char *input_str, int *index, t_minishell *minishell);
char *expand_word(const char *input_str, int *index);
char *expand_env(const char *var_name, char **envp);
char *expand_parameter(const char *input_str, int *index, t_minishell *minishell);
char *join_word(char *word, char *new_word);
char *expand_num_or_status(const char *input_str, int *index, t_minishell *minishell);
char *expand_until_char(const char *input_str, int *index, char stop_char);

// redirections
t_token		*ft_generate_redirs(t_token **token, t_minishell *minishell);
void		add_redir(t_token **rds, t_token *new_rd, t_minishell *minishell);
int			setup_redirs(t_token *redir);
int			redirect_input(char *filename);
int			redirect_output(char *filename);
int			append_output(char *filename);
int			heredoc(char **str, int index);
int			verify_heredoc(t_minishell *minishell);
void		reset_fds(t_minishell *minishell);

// execute commands
int			exec_command(char **arrstr, int id, t_minishell *minishell);
char		*verify_path(char *bin, char **path);
int			print_env(char **envp);
void		execute_tree_commands(t_minishell *minishell);
void		execute_single_command(t_minishell *minishell);
void		close_upcoming_fds(t_command *parent);
void		close_all_fds(t_minishell *minishell);
void		execute_pipe_command(t_minishell *minishell, t_command *temp_tree);
void		child_process(t_minishell *minishell, t_command *temp_tree,
				int is_left);
void		execute_command(t_minishell *minishell, t_command *temp_tree,
				int is_left);
int			handle_fds(t_minishell *minishell, t_command *temp_tree,
				int is_left);
int	is_valid_command(char **full_path, char *path, t_minishell *minishell);

// utils
void		free_arr(char **arr);
void		sort_arr(char **arr);
void		swap_arr(char **wordA, char **wordB);
int			error(char *content, char *error, int num_error);
void		free_child(t_minishell *minishell);

// free functions
void		free_prompt(t_minishell *minishell);
void		free_all_tokens(t_token **tokens);
void		free_all(t_minishell *minishell);
void		free_tree(t_command **tree);
void		free_list(t_list **list);

#endif