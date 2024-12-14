/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:38:03 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/14 16:54:00 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

static char *resolve_home_dir(const char *path, const char *home) {
    if (!path || ft_strncmp(path, "~", 2) == 0) {
        if (home)
            return (ft_strdup(home));
        return (NULL);
    }
    if (ft_strncmp(path, "~/", 2) == 0) {
        if (home)
            return (ft_strjoin(home, path + 1));
        return (NULL);
    }
    return (ft_strdup(path));
}

static int handle_cd_error(const char *path, const char *error_msg, int error_code, t_minishell *m) {
    m->status = error_code;
    return (error(path, (char *)error_msg, error_code));
}

static char *get_resolved_path(char **args, const char *home) {
    if (!args[1])
        return (resolve_home_dir(NULL, home));
    if (*args[1] == '\0' || ft_strncmp(args[1], ".", 2) == 0)
        return (ft_strdup(""));
    return (resolve_home_dir(args[1], home));
}

int change_dir(char **args, t_minishell *m) {
    char *resolved_path;
    const char *home;

    home = getenv("HOME");
    if (args[1] && args[2])
        return (handle_cd_error(NULL, "too many arguments", 1, m));
    if (!args[1] && !home)
        return (handle_cd_error(NULL, "HOME not set", 1, m));
    resolved_path = get_resolved_path(args, home);
    if (!resolved_path || chdir(resolved_path) == -1) {
        free(resolved_path);
        return (handle_cd_error(args[1], strerror(errno), 1, m));
    }
    update_pwd(m);
    free(resolved_path);
    m->status = 0; // Set exit status to success
    return (0);
}