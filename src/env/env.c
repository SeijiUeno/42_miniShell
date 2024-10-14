#include <env.h>

void    ft_clear_list(char ***list);
char    *ft_strdup(const char *s);

void    environ_initializer(t_minishell program)
{
    extern char **environ;
    char    **new_environ;
    int     i;

    i = 0;
    while (environ[i])
        i++;
    new_environ = malloc(sizeof(char *) * (i + 1));
    if (!new_environ)
        exit(EXIT_FAILURE);
    if (!environ_copy(new_environ, environ))
    {
        ft_clear_list(&new_environ);
        exit(EXIT_FAILURE);
    }
    program->env = new_environ;
}

int environ_copy(char **dest, char **src)
{
    int i;

    i = 0;
    while (src[i])
    {
        dest[i] = ft_strdup(src[i]);
        if (!dest[i])
            return (0);
        i++;
    }
    dest[i] = NULL;
    return (1);
}

char    *ft_strdup(const char *s)
{
    char    *dup;
    size_t  len;
    size_t  i;

    if (!s)
        return (NULL);
    len = strlen(s);
    dup = (char *)malloc(sizeof(char) * (len + 1));
    if (!dup)
        return (NULL);
    i = 0;
    while (s[i])
    {
        dup[i] = s[i];
        i++;
    }
    dup[i] = '\0';
    return (dup);
}

void    ft_clear_list(char ***list)
{
    int i;

    if (!list || !*list)
        return;
    i = 0;
    while ((*list)[i])
    {
        free((*list)[i]);
        i++;
    }
    free(*list);
    *list = NULL;
}

