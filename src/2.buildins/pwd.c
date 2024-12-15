/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:16:00 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/15 05:21:23 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int pwd(char **args, t_ms *m) {
    char *cwd;
	
	(void)args;
	(void)m;
	cwd = getcwd(NULL, 0);
    if (!cwd)
        return error("pwd", "failed to get current directory", 1);
    ft_putstr_fd(cwd, STDOUT_FILENO);
    ft_putchar_fd('\n', STDOUT_FILENO);
    free(cwd);
    return (0);
}
