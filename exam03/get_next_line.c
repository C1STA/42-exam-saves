/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:04:12 by wcista            #+#    #+#             */
/*   Updated: 2023/05/18 15:27:24 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE	5
#endif

int	len_and_eofline(char *str, int n)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	if (n)
	{
		while (str[i])
			i++;
		return (i);
	}
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*get_line(char *line, char *buffer)
{
	int	i;
	int	j;

	if (!line)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		i++;
	j = 0;
	while (line[i])
	{
		buffer[j] = line[i];
		line[i] = '\0';
		i++;
		j++;
	}
	return (line);
}

char	*ft_strjoin(char *line, char *buffer)
{
	int		i;
	int		j;
	char	*res;

	res = malloc(len_and_eofline(line, 1) + len_and_eofline(buffer, 1) + 1);
	i = 0;
	while (line && line[i])
	{
		res[i] = line[i];
		i++;
	}
	j = 0;
	while (buffer && buffer[j])
	{
		res[i] = buffer[j];
		buffer[j] = '\0';
		i++;
		j++;
	}
	res[i] = '\0';
	if (line)
		free(line);
	return (res);
}

char	*ft_strdup(char *str)
{
	int		i;
	char	*res;

	if (!str)
		return (NULL);
	res = malloc(len_and_eofline(str, 1) + 1);
	i = 0;
	while (str[i])
	{
		res[i] = str[i];
		str[i] = '\0';
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	static int	rd;
	char		*line;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	if (rd > 0 && buffer[0])
		line = ft_strdup(buffer);
	rd = BUFFER_SIZE;
	while (!len_and_eofline(line, 0) && rd == BUFFER_SIZE)
	{
		rd = read(fd, buffer, BUFFER_SIZE);
		if (rd > 0)
			line = ft_strjoin(line, buffer);
	}
	line = get_line(line, buffer);
	return (line);
}
