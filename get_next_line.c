/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnantaki <tnantaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 21:55:17 by tnantaki          #+#    #+#             */
/*   Updated: 2022/12/12 11:06:41 by tnantaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_read_line(int fd, char *str)
{
	int		readable;
	int		read_exnl;
	char	*tmp;

	readable = 1;
	tmp = malloc(sizeof(char) * BUFFER_SIZE);
	if (!tmp)
		return (NULL);
	while (readable)
	{
		readable = read(fd, tmp, BUFFER_SIZE);
		if (readable <= 0)
			break ;
		str = ft_strjoin(str, tmp, readable);
		read_exnl = ft_newline_len(tmp, readable);
		if (read_exnl < readable)
			break ;
	}
	free(tmp);
	return (str);
}

static char	*ft_cut_line(char *str)
{
	char	*tmp;
	int		len;
	int		read_innl;

	len = ft_strlen(str);
	read_innl = ft_newline_len(str, len) + 1;
	if (read_innl < len)
	{
		tmp = str;
		str = ft_strjoin(NULL, str + read_innl, len - read_innl);
		free (tmp);
	}
	else
	{
		free(str);
		return (NULL);
	}
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*line;
	int			len;
	int			read_exnl;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	len = ft_strlen(str);
	read_exnl = ft_newline_len(str, len);
	if (read_exnl == len)
		str = ft_read_line(fd, str);
	if (str)
	{
		line = ft_strdup(str);
		str = ft_cut_line(str);
	}
	return (line);
}
/*
int	main(void)
{
	char *str;
	int	fd = 0;
	fd = open("../collect/text.txt", O_RDONLY);
	printf("fd :%d\n", fd);
	str = get_next_line(fd);
	printf("len :%d\n", ft_strlen(str));
	printf("first :%s\n", str);
	free (str);
	// char c = 0;
	// read(fd, &c, 1);
	// printf ("printf :%c\n", c);
	str = get_next_line(fd);
	printf("second:%s\n", str);
	free (str);
	str = get_next_line(fd);
	printf("third :%s\n", str);
	free (str);
	str = get_next_line(fd);
	printf("fourth :%s\n", str);
	free (str);
	str = get_next_line(fd);
	printf("fifth :%s\n", str);
	free (str);
	fd = close (fd);
}
*/
