/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megrisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 10:38:46 by megrisse          #+#    #+#             */
/*   Updated: 2022/01/05 22:23:18 by megrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read(int fd, char *buff, int i, char *rest)
{
	char	*tmp;

	while (!ft_strchr(rest) && i != 0)
	{
		i = read(fd, buff, BUFFER_SIZE);
		if (i == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[i] = '\0';
		tmp = rest;
		if (!tmp)
		{
			tmp = malloc(1 * sizeof(char));
			tmp[0] = '\0';
		}
		rest = ft_strjoin(tmp, buff);
		free(tmp);
	}
	free(buff);
	return (rest);
}

char	*ft_get_line(char *rest)
{
	char	*line;
	int		i;

	i = 0;
	if (!rest[i])
		return (NULL);
	while (rest[i] && rest[i] != '\n')
		i++;
	if (rest[i] == '\n')
		i++;
	line = malloc((i + 1) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (rest[i] && rest[i - 1] != '\n')
	{
		line[i] = rest[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_after_nl(char *rest)
{
	char	*new;
	int		i;
	int		x;

	i = 0;
	while (rest[i] && rest[i] != '\n')
		i++;
	if (!rest[i])
	{
		free(rest);
		return (NULL);
	}
	new = malloc((ft_strlen(rest) - i + 1) * sizeof(char));
	if (!new)
		return (NULL);
	i++;
	x = 0;
	while (rest[i])
		new[x++] = rest[i++];
	new[x] = '\0';
	free(rest);
	rest = NULL;
	return (new);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*buff;
	char		*line;
	int			i;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	i = 1;
	rest = ft_read(fd, buff, i, rest);
	if (!rest)
		return (NULL);
	line = ft_get_line(rest);
	rest = ft_after_nl(rest);
	return (line);
}


int main()
{
	int		fd;
	char	*str;

	fd = open("file", O_RDONLY);
	while((str = get_next_line(fd)))
	{

		printf("%s",str);
	}
}