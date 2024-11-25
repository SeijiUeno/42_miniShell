/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_holders.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:29:07 by sueno-te          #+#    #+#             */
/*   Updated: 2024/11/25 18:07:19 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

// Function to store and retrieve the current working directory
char *static_pwd(char *new_pwd, int to_gc_deallocate)
{
    static char *pwd = NULL;

    if (to_gc_deallocate)
    {
        if (pwd)
            gc_deallocate(pwd);
        pwd = NULL;
        return NULL;
    }
    if (new_pwd)
    {
        if (pwd)
            gc_deallocate(pwd);
        pwd = new_pwd;
    }
    return pwd;
}

// Function to store and retrieve the previous working directory
char *static_old_pwd(char *new_old_pwd, int to_gc_deallocate)
{
    static char *old_pwd = NULL;

    if (to_gc_deallocate)
    {
        if (old_pwd)
            gc_deallocate(old_pwd);
        old_pwd = NULL;
        return NULL;
    }
    if (new_old_pwd)
    {
        if (old_pwd)
            gc_deallocate(old_pwd);
        old_pwd = new_old_pwd;
    }
    return old_pwd;
}