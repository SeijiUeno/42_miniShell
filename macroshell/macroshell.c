/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macroshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 15:14:27 by sueno-te          #+#    #+#             */
/*   Updated: 2024/11/23 16:31:23 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <string.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>


// std error output
void	err(char *str)
{
	while (*str)
		write(2, str++, 1);
}

// cd -> chdir[];
int	cd(char **argv, int i)
{
	if (i != 2)
		err("error: cd: bad arg");
	if (chdir(argv[1]) == -1)
		err("error: cd canno change directory");
	return (0);
}

void	set_pipe(int	has_pipe, int *fd, int end)
{
	if (has_pipe && (dup2(fd[end], end) == -1 || close(fd[0]) == -1 || close(fd[1]) == -1))
		err("error: fatal\n"), exit(1);
}

int	exec(char **argv, int i, char **envp)
{
	int	has_pipe, fd[2], pid, status;
	has_pipe = argv[1] && !strcmp(argv[i], "|");

	if (!has_pipe && !strcmp(*argv, "cd"))
		return cd(argv, i);
	if (has_pipe && pipe(fd) == -1)
		err("Error"), exit(1);
	if ((pid = fork()) == -1)
		err("Error"), exit(1);
	if (!pid)
	{
		argv[i] = 0;
		set_pipe(has_pipe, fd, 1);
		if (!strcmp(*argv, "cd"))
				exit(cd(argv, i));
		execve(*argv, argv, envp);
	}
	waitpid(pid, &status, 0);
	set_pipe(has_pipe, fd, 0);
	return (WIFEXITED(status) && WEXITSTATUS(status));
}

int	main(int argc, char **argv, char **envp)
{
	int	i = 0, status = 0;

	while (argv[i])
	{
		
		while (argv[i] && strcmp(argv[i],"|") && strcmp(argv[i], ";"))
			i++;
		if (i)
			status = exec(argv, i , envp);
	}
	return (1);
}
