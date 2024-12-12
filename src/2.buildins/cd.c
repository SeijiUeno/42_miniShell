/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:38:03 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/12 19:45:31 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

static int is_current_directory(const char *path)
{
    return (*path == '\0' || !ft_strncmp(path, ".", ft_strlen(".") + 1));
}

static int print_cd_error(const char *path, const char *error_msg)
{
    if (error_msg)
    {
        ft_putstr_fd("cd: ", STDERR_FILENO);
        ft_putstr_fd(error_msg, STDERR_FILENO);
        ft_putstr_fd("\n", STDERR_FILENO);
    }
    else if (path) // Ensure `path` is not NULL
    {
        ft_putstr_fd("cd: ", STDERR_FILENO);
        ft_putstr_fd(path, STDERR_FILENO);
        ft_putstr_fd(": ", STDERR_FILENO);
        ft_putstr_fd(strerror(errno), STDERR_FILENO);
        ft_putstr_fd("\n", STDERR_FILENO);
    }
    return (EXIT_FAILURE);
}

void update_pwd(t_minishell *minishell)
{
    char *current_path = getcwd(NULL, 0);
    char *old_pwd = NULL;
    char **envp = minishell->envp;
    int i = 0;

    while (envp[i])
    {
        if (!ft_strncmp(envp[i], "PWD=", 4))
        {
            old_pwd = ft_strdup(envp[i]);
            break;
        }
        i++;
    }

    if (old_pwd)
    {
        char *old_pwd_var = ft_strjoin("OLD", old_pwd);
        free(envp[i]);
        envp[i] = ft_strjoin("PWD=", current_path);
        buildin_export((char *[]){ "buildin_export", old_pwd_var, NULL }, minishell);
        free(old_pwd_var);
        free(old_pwd);
    }
    free(current_path);
}

static char *resolve_home_directory(const char *path, const char *home)
{
    if (!path || !ft_strncmp(path, "~", ft_strlen("~") + 1))
        return (ft_strdup(home));
    if (!ft_strncmp(path, "~/", 2))
        return (ft_strjoin(home, path + 1));
    return (ft_strdup(path));
}

int verify_and_change_dir(const char *path, t_minishell *minishell)
{
    char *resolved_path;
    const char *home = getenv("HOME");

    resolved_path = resolve_home_directory(path, home);
    if (chdir(resolved_path) == -1)
    {
        free(resolved_path);
        return (print_cd_error(path, NULL));
    }

    update_pwd(minishell);
    free(resolved_path);
    return (EXIT_SUCCESS);
}

int change_dir(char **args, t_minishell *minishell)
{
    if (args[1] && args[2])
        return (print_cd_error(NULL, "too many arguments"));
    if (args[1] && is_current_directory(args[1]))
        return (EXIT_SUCCESS);
    return (verify_and_change_dir(args[1], minishell));
}