/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjuan-pa <gjuan-pa@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 16:10:22 by gjuan-pa          #+#    #+#             */
/*   Updated: 2026/06/02 16:41:14 by gjuan-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_file(int fd, char *buffer_line)
{
	int		bytes_read;
	char	*buffer_read;
	char	*buffer_temp;

	buffer_read = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer_read)
		return (NULL);
	bytes_read = 1;
	while (bytes_read >= 0)
	{
		bytes_read = read(fd, buffer_read, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(buffer_read), free(buffer_line), NULL);
		if (bytes_read == 0)
			break ;
		buffer_read[bytes_read] = '\0';
		buffer_temp = ft_strjoin(buffer_line, buffer_read);
		free(buffer_line);
		buffer_line = buffer_temp;
		if (ft_strchr(buffer_read, '\n'))
			break ;
	}
	free(buffer_read);
	return (buffer_line);
}

static char	*cut_line(char *buffer_line)
{
	size_t	i;
	size_t	len;
	char	*delivered_line;

	i = 0;
	len = 0;
	if (!buffer_line || !buffer_line[0])
		return (NULL);
	while (buffer_line[len] && buffer_line[len] != '\n')
		len++;
	if (buffer_line[len] == '\n')
		len++;
	delivered_line = malloc((len + 1) * sizeof(char));
	if (!delivered_line)
		return (NULL);
	while (i < len)
	{
		delivered_line[i] = buffer_line[i];
		i++;
	}
	delivered_line[len] = '\0';
	return (delivered_line);
}

static char	*saved_content(char *buffer_line)
{
	char	*content;
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	while (buffer_line[len] && buffer_line[len] != '\n')
		len++;
	if (!buffer_line[len])
		return (free(buffer_line), NULL);
	len++;
	content = malloc((ft_strlen(buffer_line) - len + 1) * sizeof(char));
	if (!content)
		return (free(buffer_line), NULL);
	i = 0;
	while (buffer_line[len])
	{
		content[i] = buffer_line[len];
		i++;
		len++;
	}
	content[i] = '\0';
	free(buffer_line);
	return (content);
}

/* == coge la line de fd == */
char	*get_next_line(int fd)
{
	static char	*buffer_line;
	char		*return_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer_line = read_file(fd, buffer_line);
	if (!buffer_line)
		return (NULL);
	return_line = cut_line(buffer_line);
	buffer_line = saved_content(buffer_line);
	return (return_line);
}
