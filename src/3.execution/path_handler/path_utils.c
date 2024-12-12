/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:18:48 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/12 17:27:41 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

// Helper function to join three strings
char *ft_strjoin_three(const char *s1, const char *s2, const char *s3) {
    char *temp = ft_strjoin(s1, s2);
    if (!temp)
        return NULL;
    char *result = ft_strjoin(temp, s3);
    free(temp);
    return result;
}

// Helper function to check file access
int has_access(const char *path, int mode) {
    return (access(path, mode) == 0);
}

// Build the full path for a binary
char *build_full_path(const char *dir, const char *bin) {
    if (dir[strlen(dir) - 1] != '/')
        return ft_strjoin_three(dir, "/", bin);
    return ft_strjoin(dir, bin);
}
