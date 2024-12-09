/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:06:50 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/07 16:31:03 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

#include "../shell.h"

typedef struct s_env_list {
    char                *key;
    char                *value;
    struct s_env_list   *next;
} t_env_list;

// Function prototypes
void        environ_list_initializer(void);
t_env_list *environ_list_holder(t_env_list *new_env_list, int to_free);
void        add_env_variable(t_env_list **env_list, char *key, char *value);
void        remove_env_variable(t_env_list **env_list, const char *key);
void        free_env_list(t_env_list *env_list);

char        *get_env_value(t_env_list *env_list, const char *key);
char        *static_pwd(char *new_pwd, int to_free);
char        *static_old_pwd(char *new_old_pwd, int to_free);

//status
int	last_exit_status(int exit_status);

//out

char	**get_env(char **envp);
char	*get_single_env(char *env_name, char **envp);
char	*get_env_value(char *env_name, char **envp);
char	**insert_paths(char *paths);
char	**get_paths(char **env);
int	    print_env(char **envp);

#endif