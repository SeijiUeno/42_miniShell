/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:05:19 by sueno-te          #+#    #+#             */
/*   Updated: 2024/11/25 17:37:59 by sueno-te         ###   ########.fr       */
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
# include "../libft/includes/libft.h"
# include "../libft/includes/garbage_collector.h"
#include "../env/env.h"

#endif