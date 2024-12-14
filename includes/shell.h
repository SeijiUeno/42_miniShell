/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorales <emorales@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:05:19 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/14 16:51:41 by emorales         ###   ########.fr       */
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
typedef struct s_token_data	t_token_data;
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

struct s_token_data 
{
	t_token	**tokens;
	t_token	**current;
	char	*input;
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
void shell_initialize(t_minishell *minishell);

// signals
void		signal_setup(void);
void		signal_handle(int signum);
void		signal_handle_execution(int signum);
// status
int			status_control(int status);
int			status_filter(int status);
void		terminal_save_settings(struct termios *original);
void	terminal_restore_settings(const struct termios *original);
void	signal_handle_heredoc(int signal);
char	*env_get_value(char *env_name, char **envp);

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
int assign_redir_type(char op_char, char *content);
void process_symbol(char *input, int *index, t_token **tokens, t_token **current);
void process_word(char *input, int *index, t_token **tokens, t_token **current);
void add_token(t_token_data *data, int start, int end);

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

// Debugging Functions
void debug_print_tree(t_command *node, int level);
void debug_print_tokens(t_token *tokens);

// get envs
char		**get_env(char **envp);
char		**get_paths(char **env);
char		*get_single_env(char *env_name, char **envp);
int			verify_abs_path(const char *path);

// bultins
int			pwd(void);
int			change_dir(char **path, t_minishell *minishell);
int			unset(const char **key, t_minishell *minishell);
int			buildin_export(char **args, t_minishell *minishell);
char		*var_validate_name(char *var);
int			echo(char **args);
int			builtin_exit(char **args, t_minishell *minishell);
int			builtin_check(char **command, t_minishell *minishell);
// builds
int			build_commands(t_minishell *minishell);
// expansor

extern volatile sig_atomic_t g_in_subprocess;

char *expand_single_quotes(const char *input_str, int *index);;
char *expansor(const char *input_str, t_minishell *minishell);
char *expand_double_quotes(const char *input_str, int *index, t_minishell *minishell);
char *expand_word(const char *input_str, int *index);
char *expand_env(const char *var_name, char **envp);
char *expand_parameter(const char *input_str, int *index, t_minishell *minishell);
char *join_word(char *word, char *new_word);
char *expand_until_char(const char *input_str, int *index, char stop_char);

// heredoc
int	heredoc_read(const char *delim, int fd);
int	heredoc(char **str, int index);
char	*heredoc_generate_name(int index);
int			verify_heredoc(t_minishell *minishell);
void		fds_reset(t_minishell *minishell);

/* Utils */
int open_file(char *filename, int flags, int mode);
int redirect_fd(int fd, int std_fd);
void remove_token_from_list(t_token **head, t_token *node);

/* Redirections */
int redirect_input(char *filename);
int redirect_output(char *filename);
int append_output(char *filename);

/* Setup */
int redir_process(t_token *redir);
int redir_setup(t_token *redir);
void redir_append_node(t_token **redirs, int type, char *filename);
t_token		*ft_generate_redirs(t_token **token, t_minishell *minishell);

// execute commands
int			exec_run_command(char **arrstr, int id, t_minishell *minishell);
int			print_env(char **envp);
void		execute(t_minishell *minishell);
void		exec_child_process(t_minishell *minishell, t_command *temp_tree,
				int is_left);
void exec_run_child_command(t_minishell *m, t_command *cmd, int *pipes, int ctx[2]);
void exec_wait_for_children(t_minishell *minishell, pid_t *pids, int count);
//pipes
void 		pipe_close_all(int *pipes, int total_fds);
int			pipe_create(int *pipes, int command_count);
void 		pipe_run_pipeline(t_minishell *m, t_command **cmds, int cmd_count);
//paths
char 		*define_full_path(char *cmd, char **path);
char *ft_strjoin_three(const char *s1, const char *s2, const char *s3);
int is_valid_command(char **full_path, const char *cmd, char **env_path);
int has_access(const char *path, int mode);
char *build_full_path(const char *dir, const char *bin);
char *search_path(const char *bin, char **path);

// utils
void		util_free_array(char **arr);
void		util_swap_array(char **wordA, char **wordB);
int			error(const char *content, char *error, int num_error);
void		util_free_child(t_minishell *minishell);

// free functions
void		prompt_clear(t_minishell *minishell);
void		free_all_tokens(t_token **tokens);
void		free_all(t_minishell *minishell);
void		free_tree(t_command **tree);
void		free_list(t_list **list);

//debug
void debug_print_commands_array(t_command **commands);

#endif