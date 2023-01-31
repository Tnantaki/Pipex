/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnantaki <tnantaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 13:55:01 by tnantaki          #+#    #+#             */
/*   Updated: 2023/01/30 19:47:03 by tnantaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_front(char *s1, char *set)
{
	size_t	i;
	size_t	begin;

	i = 0;
	begin = 0;
	while (set[i])
	{
		i++;
		if (set[i - 1] == s1[begin])
		{
			begin++;
			i = 0;
		}
	}
	return (begin);
}

static size_t	ft_end(char *s1, char *set, size_t lens1, size_t be)
{
	size_t	i;
	size_t	last;

	i = 0;
	last = 0;
	while (set[i] && lens1 > be)
	{
		i++;
		if (set[i - 1] == s1[lens1 - 1])
		{
			lens1--;
			last++;
			i = 0;
		}
	}
	return (last);
}

char	*ft_strtrim(char *s1, char *set)
{
	char	*dst;
	size_t	i;
	size_t	begin;
	size_t	endlen;
	size_t	lendst;

	if (!s1 || !set)
		return (NULL);
	begin = ft_front(s1, set);
	endlen = ft_end(s1, set, ft_strlen(s1), begin);
	lendst = ft_strlen(s1) - begin - endlen;
	dst = malloc(sizeof(char) * lendst + 1);
	if (!dst)
		return (NULL);
	i = 0;
	while (i < lendst)
		dst[i++] = s1[begin++];
	dst[i] = '\0';
	return (dst);
}
