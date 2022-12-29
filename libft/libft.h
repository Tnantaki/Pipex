/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnantaki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 10:42:30 by tnantaki          #+#    #+#             */
/*   Updated: 2022/09/22 10:45:55 by tnantaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>

// void	*ft_memset(void *b, int c, size_t len);
// void	*ft_memchr(const void *s, int c, size_t n);
// int		ft_memcmp(const void *s1, const void *s2, size_t n);
// void	*ft_memmove(void *dst, const void *src, size_t len);
// void	*ft_memcpy(void *dst, const void *src, size_t len);
// char	*ft_strnstr(const char *str, const char *find, size_t len);
// int		ft_atoi(const char *str);
// char	*ft_strdup(const char *s1);
// char	*ft_substr(char const *s1, unsigned int start, size_t len);

int     ft_strlen(const char *str);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strjoinfree(char *s1, char *s2);
char	*ft_strtrim(char *s1, char *set);
char	**ft_split(char *s1, char c);

#endif
