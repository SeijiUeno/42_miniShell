/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 13:34:02 by sueno-te          #+#    #+#             */
/*   Updated: 2024/11/25 19:34:44 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATH_MAX
#define PATH_MAX 4096 // or another reasonable default
#endif

int pwd(const char **args);
int	echo(char **args);
int cd(char **args);
int unset(char **args);
int env(const char **args);
int export(char **args);


int is_valid_identifier(const char *identifier);
void ft_unsetenv(const char *name);