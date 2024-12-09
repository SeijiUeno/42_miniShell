/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:38:03 by sueno-te          #+#    #+#             */
/*   Updated: 2024/11/25 17:58:56 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"
#include "buildins.h"

char *malloc_pwd(void);

static char *expand_path(const char *path, t_env_list *env_list)
{
    if (path[0] == '~')
    {
        const char *home = get_env_value(env_list, "HOME");
        if (home)
            return gc_strjoin(home, path + 1);
        else
        {
            ft_putendl_fd("minishell: cd: HOME not set", 2);
            last_exit_status(1);
            return NULL;
        }
    }
    else if (ft_strcmp(path, "-") == 0)
    {
        const char *oldpwd = get_env_value(env_list, "OLDPWD");
        if (oldpwd)
        {
            ft_putendl_fd(oldpwd, 1);
            return gc_strdup(oldpwd);
        }
        else
        {
            ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
            last_exit_status(1);
            return NULL;
        }
    }
    else
    {
        return gc_strdup(path);
    }
}

void set_env_variable(t_env_list **env_list, char *key, char *value)
{
    t_env_list *current = *env_list;
    while (current)
    {
        if (ft_strcmp(current->key, key) == 0)
        {
            if (current->value)
                gc_deallocate(current->value);
            current->value = value;
            gc_deallocate(key);
            return;
        }
        current = current->next;
    }
    add_env_variable(env_list, key, value);
}

static int change_directory(char *path, t_env_list *env_list)
{
    char *oldpwd = malloc_pwd();
    if (!oldpwd)
    {
        oldpwd = gc_strdup(get_env_value(env_list, "PWD"));
        if (!oldpwd)
            oldpwd = gc_strdup("");
    }
    static_old_pwd(gc_strdup(oldpwd), 0);

    if (chdir(path) != 0)
    {
        perror("minishell: cd");
        last_exit_status(1);
        gc_deallocate(oldpwd);
        gc_deallocate(path);
        return EXIT_FAILURE;
    }

    char *newpwd = malloc_pwd();
    if (!newpwd)
    {
        ft_putendl_fd("minishell: cd: error retrieving current directory", 2);
        newpwd = gc_strdup(path);
    }
    static_pwd(gc_strdup(newpwd), 0); // Store the new pwd

    // Update PWD and OLDPWD environment variables
    set_env_variable(&env_list, gc_strdup("OLDPWD"), gc_strdup(static_old_pwd(NULL, 0)));
    set_env_variable(&env_list, gc_strdup("PWD"), gc_strdup(static_pwd(NULL, 0)));

    gc_deallocate(oldpwd);
    gc_deallocate(newpwd);
    gc_deallocate(path);

    last_exit_status(0);
    return EXIT_SUCCESS;
}

int cd(char **args)
{
    t_env_list *env_list = environ_list_holder(NULL, 0);
    char *path = NULL;
    int ret;

    if (!args[1])
    {
        const char *home = get_env_value(env_list, "HOME");
        if (home)
            path = gc_strdup(home);
        else
        {
            ft_putendl_fd("minishell: cd: HOME not set", 2);
            last_exit_status(1);
            return EXIT_FAILURE;
        }
    }
    else if (args[2])
    {
        ft_putendl_fd("minishell: cd: too many arguments", 2);
        last_exit_status(1);
        return EXIT_FAILURE;
    }
    else
    {
        path = expand_path(args[1], env_list);
        if (!path)
            return EXIT_FAILURE;
    }
    ret = change_directory(path, env_list);
    return ret;
}