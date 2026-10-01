/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkato <nkato@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 18:41:42 by nkato             #+#    #+#             */
/*   Updated: 2026/09/23 10:28:53 by nkato            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

static char	*cleanup(char **stash, char *buffer)
{
	free(*stash);
	*stash = NULL;
	free(buffer);
	return (NULL);
}

int	find_newline(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (-1);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		return (i);
	return (-1);
}

static int	read_to_stash(int fd, char **stash, char *buffer, size_t *stash_len)
{
	ssize_t	bytes_read;

	while (find_newline(*stash) == -1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (-1);
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		*stash = append_stash(*stash, buffer, bytes_read, stash_len);
		if (*stash == NULL)
			return (-1);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*buffer;
	char		*line;
	size_t		stash_len;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (NULL);
	stash_len = ft_strlen(stash);
	if (read_to_stash(fd, &stash, buffer, &stash_len) == -1)
		return (cleanup(&stash, buffer));
	if (stash == NULL)
		return (cleanup(&stash, buffer));
	line = extract_line(stash);
	if (line == NULL)
		return (cleanup(&stash, buffer));
	stash = trim_stash(stash);
	free(buffer);
	return (line);
}
