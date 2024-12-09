/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:20:43 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/05 18:28:04 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


int	verify_abs_path(char *path)
{
	if (access(path, F_OK) == 0 && access(path, X_OK) == 0)
		return (1);
	return (0);
}

int	is_valid_command(char **full_path, char *path, t_minishell *minishell)
{
	if (verify_abs_path(path))
	{
		*full_path = path;
		return (EXIT_SUCCESS);
	}
	*full_path = verify_path(path, minishell->path);
	if (!*full_path)
		return (error(path, ": Command not found", 127));
	return (0);
}

void	child_single(char *full_path, char **arrstr, t_minishell *minishell)
{
	int	i;

	i = 3;
	while (i < 1024)
		close(i++);
	execve(full_path, arrstr, minishell->envp);
	free(full_path);
	free_all(minishell);
	exit(EXIT_FAILURE);
}

int	exec_command(char **arrstr, int id, t_minishell *minishell)
{
	int		i_status;
	char	*full_path;

	i_status = 0;
	full_path = NULL;
	i_status = is_valid_command(&full_path, arrstr[0], minishell);
	if (i_status)
	{
		if (full_path)
			free(full_path);
		full_path = NULL;
		return (i_status);
	}
	id = fork();
	if (id < 0)
	{
    perror("fork");
    return (EXIT_FAILURE);
	}
	if (!id)
		child_single(full_path, arrstr, minishell);
	waitpid(id, &i_status, 0);
	i_status = filter_status(i_status);
	if (full_path && ft_strncmp(full_path, arrstr[0],
			ft_strlen(full_path) + 1))
		free(full_path);
	reset_fds(minishell);
	return (i_status);
}
#include "../includes/minishell.h"

void	close_upcoming_fds(t_command *parent)
{
	t_command	*parent_tree;

	parent_tree = parent->parent;
	while (parent_tree)
	{
		close(parent_tree->fd[0]);
		close(parent_tree->fd[1]);
		parent_tree = parent_tree->parent;
	}
}

char	*define_full_path(char *cmd, char **path)
{
	char	*full_path;

	if (verify_abs_path(cmd))
		return (cmd);
	full_path = verify_path(cmd, path);
	return (full_path);
}

void	child_process(t_minishell *minishell, t_command *temp_tree,
	int is_left)
{
	char	*cmd;
	int		status;

	status = 0;
	minishell->status = handle_fds(minishell, temp_tree, is_left);
	if (minishell->status || !temp_tree->argv)
		free_child(minishell);
	status = is_builtin(temp_tree->argv, minishell);
	if (status >= 0)
	{
		minishell->status = status;
		free_child(minishell);
	}
	cmd = define_full_path(temp_tree->argv[0], minishell->path);
	if (!cmd)
	{
		minishell->status = error(temp_tree->argv[0],
				": Command not found", 127);
		close_upcoming_fds(temp_tree);
		free_child(minishell);
	}
	execve(cmd, temp_tree->argv, minishell->envp);
	free_all(minishell);
	exit(EXIT_FAILURE);
}

void	execute_command(t_minishell *minishell, t_command *temp_tree,
	int is_left)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		minishell->status = error("fork: ", strerror(errno), 1);
		return ;
	}
	if (!pid)
		child_process(minishell, temp_tree, is_left);
	ft_lstadd_back(&(minishell->pid_list), ft_lstnew((void *)((long)pid)));
}

void	execute_pipe_command(t_minishell *minishell, t_command *temp_tree)
{
	pipe(temp_tree->fd);
	(void)temp_tree;
	if (temp_tree->left && temp_tree->left->type == PIPE)
		execute_pipe_command(minishell, temp_tree->left);
	if (temp_tree->left && temp_tree->left->type != PIPE)
		execute_command(minishell, temp_tree->left, 1);
	execute_command(minishell, temp_tree->right, 0);
	close(temp_tree->fd[0]);
	close(temp_tree->fd[1]);
}
void	execute_single_command(t_minishell *minishell)
{
	t_command	*temp_cmd;
	int			status;

	status = 0;
	temp_cmd = minishell->tree_cmd;
	if (temp_cmd->redir)
		status = setup_redirs(temp_cmd->redir);
	if (status)
		minishell->status = status;
	else
	{
		if (!temp_cmd->argv)
			return ;
		status = is_builtin(temp_cmd->argv, minishell);
		if (status >= 0)
		{
			minishell->status = status;
			return ;
		}
		minishell->status = exec_command(temp_cmd->argv, 0, minishell);
	}
}

void	close_fds(t_minishell *minishell)
{
	t_command	*temp_tree;

	temp_tree = minishell->tree_cmd;
	while (temp_tree->type == PIPE)
	{
		close(temp_tree->fd[STDOUT_FILENO]);
		close(temp_tree->fd[STDIN_FILENO]);
		temp_tree = temp_tree->left;
	}
}

int	handle_fds(t_minishell *minishell, t_command *temp_tree, int is_left)
{
	t_command	*parent_tree;

	(void)minishell;
	parent_tree = temp_tree->parent;
	if (is_left)
	{
		close(parent_tree->fd[STDIN_FILENO]);
		dup2(parent_tree->fd[STDOUT_FILENO], STDOUT_FILENO);
	}
	else
	{
		dup2(parent_tree->fd[STDIN_FILENO], STDIN_FILENO);
		if (parent_tree->parent)
			dup2(parent_tree->parent->fd[1], STDOUT_FILENO);
	}
	close_all_fds(minishell);
	if (temp_tree->redir && setup_redirs(temp_tree->redir))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	close_all_fds(t_minishell *minishell)
{
	t_command	*temp;
	int			i;

	i = 3;
	while (i < 1024)
		close(i++);
	temp = minishell->tree_cmd;
	while (temp->left)
		temp = temp->left;
	close_upcoming_fds(temp);
}

void	execute_tree_commands(t_minishell *minishell)
{
	t_command	*temp_tree;
	t_list		*temp_list;

	temp_tree = minishell->tree_cmd;
	signal(SIGINT, &handle_signal_exec);
	signal(SIGQUIT, &handle_signal_exec);
	if (temp_tree->type == WORD)
		execute_single_command(minishell);
	else
	{
		execute_pipe_command(minishell, temp_tree);
		temp_list = minishell->pid_list;
		while (temp_list)
		{
			waitpid((pid_t)((long)(temp_list->content)), &minishell->status, 0);
			minishell->status = filter_status(minishell->status);
			temp_list = temp_list->next;
		}
	}
	prepare_signals();
}
