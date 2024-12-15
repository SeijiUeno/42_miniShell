/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 20:24:23 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/12 19:15:49 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int					ft_tochr(int c);
int					ft_isdigit(int c);
size_t				ft_strlen(const char *s);
char				*ft_itoa(int n);
int					ft_atoi(const char *str);
void				ft_putnbr(int n);
int					ft_strcmp(const char *s1, const char *s2);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_calloc(size_t number_elements, size_t size);
void				ft_bzero(void *s, size_t n);
void				ft_putchar_fd(const char c, int fd);
void				ft_putstr_fd(const char *s, int fd);
void				ft_putendl_fd(const char *s, int fd);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
void				ft_error(const char *prefix, const char *arg,
						const char *suffix);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
char				*ft_strchr(const char *s, int c);
char				*ft_strdup(const char *s);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strndup(const char *s, size_t n);
char				*ft_strjoin(char const *s1, char const *s2);
char				**ft_split(char const *s, char c);
size_t				ft_putstr_len(const char *s, int fd);
int					ft_printf(const char *format, ...);
size_t				ft_putptr_len(void *ptr, int fd);
size_t				ft_putnbr_len(long long number, char *base, int fd);

#endif
