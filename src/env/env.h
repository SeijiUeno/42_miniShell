/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:06:50 by sueno-te          #+#    #+#             */
/*   Updated: 2024/11/25 15:56:24 by sueno-te         ###   ########.fr       */
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
char       *get_env_value(t_env_list *env_list, const char *key);
void        free_env_list(t_env_list *env_list);

//status
int	last_exit_status(int exit_status);

#endif