/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:05:19 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/12 16:32:23 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "../libs/libft/includes/libft.h"
# include "../libs/garbage_collector/includes/garbage_collector.h"
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

# define STATUS_QUIT 3
# define STATUS_CTRL_C 2
# define STATUS_MAX 255
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
	int			stdin_backup;
	int			stdout_backup;
	char		**envp;
	char		**path;
	char		*input;
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

struct s_command
{
	int					argc;
	int					type;
	int					fd[2];
	char				**argv;
	t_token				*redir;
	t_command			*left;
	t_command			*right;
	t_command			*root;
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
void		save_terminal_settings(struct termios *original);
void	restore_terminal_settings(const struct termios *original);
void	handle_sig_heredoc(int signal);
char	*get_env_value(char *env_name, char **envp);

// Tokenizer Functions
void generate_tokens(char *input, t_token **tokens);
void assign_operator_token_types(t_token **tokens);
void initialize_token_list(t_token **tokens);
void append_token(t_token **token_list, t_token *new_token);
void free_all_tokens(t_token **tokens);
void skip_whitespace(char *input, int *index);
void skip_quoted_token(char *input, int *index);
int	validate_all_quotes(char *input);
int	is_only_spaces(char *input);
int assign_redirection_type(char op_char, char *content);
void process_symbol(char *input, int *index, t_token **tokens, t_token **current);
void process_word(char *input, int *index, t_token **tokens, t_token **current);
void	add_token(t_token **tokens, t_token **current, char *input, int start, int end);

// Token Validation Functions
int validate_tokens(t_token *tokens);
int check_leading_token(t_token *tokens);
int check_trailing_token(t_token *tokens);
int check_token_sequence(t_token *tokens);
int is_redirection(int token_type);
void append_redirection(t_token **redirections, t_token *redir, t_token *redir_target, t_minishell *minishell);

// AST Functions
t_command *create_command_node(t_token *tokens, t_minishell *minishell);

// parsing
void generate_ast(t_minishell *minishell);
t_command **ast_to_command_list(t_command *root);
t_command *create_pipe_node(t_command *left_cmd, t_command *right_cmd);
int count_commands_in_array(t_command **commands);
char **build_argument_vector(t_token *tokens, t_minishell *minishell);
void advance_to_next_pipe(t_token **tokens);
t_command *build_pipeline_ast(t_minishell *minishell, t_command *root_cmd);
t_command *create_command_node(t_token *tokens, t_minishell *minishell);
char **allocate_argument_array(t_token *tokens, t_minishell *minishell, int count);
char *extract_var_name(const char *input_str, int *index);

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


char *expand_single_quotes(const char *input_str, int *index);;
char *expand_vars_and_quotes(const char *input_str, t_minishell *minishell);
char *expand_double_quotes(const char *input_str, int *index, t_minishell *minishell);
char *expand_word(const char *input_str, int *index);
char *expand_env(const char *var_name, char **envp);
char *expand_parameter(const char *input_str, int *index, t_minishell *minishell);
char *join_word(char *word, char *new_word);
char *expand_num_or_status(const char *input_str, int *index, t_minishell *minishell);
char *expand_until_char(const char *input_str, int *index, char stop_char);

// heredoc
int	read_heredoc(const char *delim, int fd);
int	heredoc(char **str, int index);
char	*generate_heredoc_name(int index);

/* Utils */
int open_file(char *filename, int flags, int mode);
int redirect_fd(int fd, int std_fd);
void remove_token_from_list(t_token **head, t_token *node);

/* Redirections */
int redirect_input(char *filename);
int redirect_output(char *filename);
int append_output(char *filename);

/* Setup */
int process_redirection(t_token *redir);
int setup_redirs(t_token *redir);
void append_redirection_node(t_token **redirs, int type, char *filename);
t_token		*ft_generate_redirs(t_token **token, t_minishell *minishell);
void		add_redir(t_token **rds, t_token *new_rd, t_minishell *minishell);
int			heredoc(char **str, int index);
int			verify_heredoc(t_minishell *minishell);
void		reset_fds(t_minishell *minishell);

// execute commands
int			exec_command(char **arrstr, int id, t_minishell *minishell);
char		*verify_path(char *bin, char **path);
int			print_env(char **envp);
void		execute_tree_commands(t_minishell *minishell);
void		execute_single_command(t_minishell *minishell);
void		close_upcoming_fds(t_command *root);
void		close_all_fds(t_minishell *minishell);
void		execute_pipe_command(t_minishell *minishell, t_command *temp_tree);
void		child_process(t_minishell *minishell, t_command *temp_tree,
				int is_left);
void		execute_command(t_minishell *minishell, t_command *temp_tree,
				int is_left);
int			handle_fds(t_minishell *minishell, t_command *temp_tree,
				int is_left);
int			is_valid_command(char **full_path, char *path, t_minishell *minishell);
void run_child_command(t_minishell *m, t_command *cmd, int *pipes, int ctx[2]);
void wait_for_children(t_minishell *minishell, pid_t *pids, int count);
//pipes
void 		close_all_pipes(int *pipes, int total_fds);
int			create_pipes(int *pipes, int command_count);
void 		run_pipeline(t_minishell *m, t_command **cmds, int cmd_count);
//paths
char 		*define_full_path(char *cmd, char **path);

// utils
void		free_arr(char **arr);
void		sort_arr(char **arr);
void		swap_arr(char **wordA, char **wordB);
int			error(char *content, char *error, int num_error);
void		free_child(t_minishell *minishell);

// free functions
void		prompt_clear(t_minishell *minishell);
void		free_all_tokens(t_token **tokens);
void		free_all(t_minishell *minishell);
void		free_tree(t_command **tree);
void		free_list(t_list **list);

//debug
void debug_print_commands_array(t_command **commands);

#endif