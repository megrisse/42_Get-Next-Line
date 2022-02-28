/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megrisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 09:42:47 by megrisse          #+#    #+#             */
/*   Updated: 2022/01/05 02:15:57 by megrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	char	*new_backup;
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
	new_backup = malloc((ft_strlen(rest) - i + 1) * sizeof(char));
	if (!new_backup)
		return (NULL);
	i++;
	x = 0;
	while (rest[i])
		new_backup[x++] = rest[i++];
	new_backup[x] = '\0';
	free(rest);
	rest = NULL;
	return (new_backup);
}

char	*get_next_line(int fd)
{
	static char	*rest[65535];
	char		*buff;
	char		*line;
	int			i;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
		i = 1;
		rest[fd] = ft_read(fd, buff, i, rest[fd]);
	if (!rest[fd])
		return (NULL);
	line = ft_get_line(rest[fd]);
	rest[fd] = ft_after_nl(rest[fd]);
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