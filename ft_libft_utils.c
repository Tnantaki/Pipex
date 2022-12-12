/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnantaki <tnantaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 08:33:29 by tnantaki          #+#    #+#             */
/*   Updated: 2022/12/12 11:08:58 by tnantaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	ft_newline_len(char *str, int len)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (i < len)
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (i);
}

char	*ft_strjoin(char *s1, char *s2, int lens2)
{
	char	*dst;
	int		lens1;
	int		i;
	int		j;

	if (!s2)
		return (NULL);
	lens1 = ft_strlen(s1);
	dst = malloc(sizeof(char) * (lens1 + lens2 + 1));
	if (!dst)
		return (NULL);
	i = 0;
	j = 0;
	while (lens1--)
		dst[i++] = s1[j++];
	j = 0;
	while (lens2--)
		dst[i++] = s2[j++];
	dst[i] = '\0';
	if (s1)
		free(s1);
	return (dst);
}

char	*ft_strdup(char *s1)
{
	char	*dst;
	size_t	i;
	size_t	len;
	size_t	len_innl;

	i = 0;
	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	len_innl = ft_newline_len(s1, len) + 1;
	dst = malloc((sizeof(char)) * (len_innl + 1));
	if (!dst)
		return (NULL);
	while (len_innl--)
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
