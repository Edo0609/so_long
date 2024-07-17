/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epenaloz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 20:05:14 by epenaloz          #+#    #+#             */
/*   Updated: 2023/11/08 16:16:54 by epenaloz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"
#include <stdio.h>

char	*ft_free(char *ptr)
{
	if (ptr)
		free(ptr);
	return (NULL);
}

char	*find_line(int fd, char *storage)
{
	char	*r_buf;
	int		bytes_read;

	r_buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!r_buf)
		return (ft_free(storage));
	bytes_read = 1;
	while (!ft_strchr_gnl(storage, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, r_buf, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(r_buf), ft_free(storage));
		r_buf[bytes_read] = '\0';
		storage = ft_strjoin_gnl(storage, r_buf);
		if (!storage)
			return (free(r_buf), NULL);
	}
	free(r_buf);
	return (storage);
}

char	*line_get(char *storage)
{
	size_t	i;
	size_t	j;
	char	*line;

	i = 0;
	j = 0;
	if (storage[i] == '\0' || !storage)
		return (NULL);
	while (storage[i] != '\n' && storage[i] != '\0')
		i++;
	if (storage[i] == '\n')
		i++;
	line = (char *)malloc((sizeof(char) * (i + 1)));
	if (!line)
		return (ft_free(storage));
	i = 0;
	while (storage[i] != '\n' && storage[i])
		line[j++] = storage[i++];
	if (storage[i] == '\n')
		line[j++] = storage[i++];
	line[j] = '\0';
	return (line);
}

char	*update_storage(char *storage)
{
	size_t	i;
	size_t	j;
	char	*new;

	i = 0;
	j = 0;
	if (!ft_strchr_gnl(storage, '\n'))
		return (ft_free(storage));
	while (storage[i] != '\n')
		i++;
	new = (char *)malloc(sizeof(char) * (ft_strlen_gnl(storage) - i + 1));
	if (!new)
		return (ft_free(storage));
	i++;
	while (storage[i] != '\0')
		new[j++] = storage[i++];
	new[j] = '\0';
	free(storage);
	return (new);
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	storage = find_line(fd, storage);
	if (!storage)
		return (NULL);
	line = line_get(storage);
	storage = update_storage(storage);
	return (line);
}
