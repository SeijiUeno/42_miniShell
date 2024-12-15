/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:21:48 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/15 00:36:06 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>

// Function prototypes
static int handle_path_validation(const char *cmd, char **full_path, struct stat *path_stat);
static int check_command_type(const char *cmd, char **full_path, struct stat *path_stat);
char *search_path(const char *cmd, char **env_path);

// Validates the command path
#include <errno.h>

static int handle_path_validation(const char *cmd, char **full_path, struct stat *path_stat) {
    *full_path = strdup(cmd);
    if (!*full_path)
        return error(cmd, ": Memory allocation failed", 1);

    if (stat(*full_path, path_stat) < 0) {
        int err = errno; // Capture the specific error
        free(*full_path);
        *full_path = NULL;

        // Distinguish between "Not a directory" and "No such file"
        if (err == ENOTDIR)
            return error(cmd, ": Not a directory", 126);
        return error(cmd, ": No such file or directory", 127);
    }
    return EXIT_SUCCESS;
}

static int check_command_type(const char *cmd, char **full_path, struct stat *path_stat) {
    if (S_ISDIR(path_stat->st_mode)) {
        free(*full_path);
        *full_path = NULL;
        return error(cmd, ": Is a directory", 126);
    }

    if (access(*full_path, X_OK) < 0) {
        free(*full_path);
        *full_path = NULL;

        // Use errno for better messaging
        if (errno == EACCES)
            return error(cmd, ": Permission denied", 126);
        return error(cmd, ": Command not found", 127);
    }
    return EXIT_SUCCESS;
}

// Determines if a command is valid
int is_valid_command(char **full_path, const char *cmd, char **env_path) {
    struct stat path_stat;
    int status;

    // Check if the command is an absolute or relative path
    if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/')) {
        status = handle_path_validation(cmd, full_path, &path_stat);
        if (status != EXIT_SUCCESS)
            return status;
        return check_command_type(cmd, full_path, &path_stat);
    }

    // Search for the command in the PATH
    *full_path = search_path(cmd, env_path);
    if (!*full_path)
        return error(cmd, ": Command not found", 127);

    // Validate the found command in PATH
    if (stat(*full_path, &path_stat) < 0) {
        free(*full_path);
        *full_path = NULL;
        return error(cmd, ": No such file or directory", 127);
    }
    return check_command_type(cmd, full_path, &path_stat);
}
