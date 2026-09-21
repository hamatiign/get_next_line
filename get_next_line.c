/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkato <nkato@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 18:41:42 by nkato             #+#    #+#             */
/*   Updated: 2026/09/22 06:43:30 by nkato            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*buffer;
	ssize_t		bytes_read;
	char		*line;
  size_t stash_len;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (buffer == NULL)
	{
		free(buffer);
		return (NULL);
	}
  stash_len = ft_strlen(stash);
	while (find_newline(stash) == -1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(stash);
			free(buffer);
			stash = NULL;
			return (NULL);
		} if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		stash = append_stash(stash, buffer, bytes_read, &stash_len);
	}
	if (stash == NULL)
	{
		free(buffer);
		return (NULL);
	}
	line = extract_line(stash);
	if (line == NULL)
	{
		free(stash);
		free(buffer);
		stash = NULL;
		return (NULL);
	}
	stash = trim_stash(stash);
  free(buffer);
	return (line);
}
