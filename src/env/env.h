/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:08:17 by sueno-te          #+#    #+#             */
/*   Updated: 2024/10/14 18:29:27 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRON_UTILS_H
# define ENVIRON_UTILS_H

#include <stdlib.h>
#include <unistd.h>
#include <../shell.h>

// Function prototypes
void    environ_initializer(void);
int     environ_copy(char **dest, char **src);
char    **environ_holder(char **new_environ, int to_free);

// libft
char    *ft_strdup(const char *s);
void    ft_clear_list(char ***list);

#endif
