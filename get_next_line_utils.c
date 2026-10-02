/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkato <nkato@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 19:01:48 by nkato             #+#    #+#             */
/*   Updated: 2026/09/17 19:01:50 by nkato            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

static char	*free_stash(char **stash)
{
	free(*stash);
	*stash = NULL;
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char	*append_stash(char *stash, const char *buffer, size_t bytes_read,
		size_t *stash_len)
{
	char	*new_stash;
	size_t	i;

	i = 0;
	new_stash = (char *)malloc((sizeof(char)) * (*stash_len + bytes_read + 1));
	if (new_stash == NULL)
	{
		free(stash);
		return (NULL);
	}
	while (i < *stash_len)
	{
		new_stash[i] = stash[i];
		i++;
	}
	while (i < bytes_read + *stash_len)
		new_stash[i++] = *buffer++;
	new_stash[i] = '\0';
	*stash_len += bytes_read;
	free(stash);
	return (new_stash);
}

char	*extract_line(const char *stash)
{
	char			*ret_str;
	size_t			line_len;
	const ssize_t	newline_index = find_newline(stash);
	size_t			i;

	if (newline_index == -1)
		line_len = ft_strlen(stash);
	else
		line_len = (size_t)newline_index + 1;
	i = 0;
	ret_str = (char *)malloc(sizeof(char) * (line_len + 1));
	if (ret_str == NULL)
		return (NULL);
	while (i < line_len)
		ret_str[i++] = *stash++;
	ret_str[i] = '\0';
	return (ret_str);
}

char	*trim_stash(char *stash)
{
	char			*new_stash;
	const ssize_t	newline_index = find_newline(stash);
	size_t			new_size;
	size_t			i;
	size_t			stash_len;

	stash_len = ft_strlen(stash);
	if (newline_index == -1)
		return (free_stash(&stash));
	i = 0;
	new_size = stash_len - (size_t)newline_index;
	if (new_size == 1)
		return (free_stash(&stash));
	new_stash = (char *)malloc((sizeof(char) * new_size));
	if (new_stash == NULL)
		return (free_stash(&stash));
	while (i < new_size - 1)
	{
		new_stash[i] = stash[i + (size_t)newline_index + 1];
		i++;
	}
	new_stash[i] = '\0';
	free(stash);
	return (new_stash);
}
