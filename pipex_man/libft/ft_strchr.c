/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnantaki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 21:11:35 by tnantaki          #+#    #+#             */
/*   Updated: 2022/09/22 10:40:29 by tnantaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	size_t	i;
	char	care;

	i = 0;
	care = (char)c;
	while (str[i])
	{
		if (str[i] == care)
			return ((char *)str + i);
		i++;
	}
	if (care == '\0')
		return ((char *)str + i);
	return (0);
}
