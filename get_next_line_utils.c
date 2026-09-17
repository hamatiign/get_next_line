#include "./get_next_line.h"
#include <stddef.h>
#include <stdlib.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if(s == NULL) return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	find_newline(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (-1);
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*append_stash(char *stash, char *buffer, ssize_t bytes_read)
{
	size_t	stash_len;
	char	*new_stash;
    size_t		i;

	i = 0;
	if (stash == NULL)
		stash_len = 0;
	else
		stash_len = ft_strlen(stash);
	new_stash = (char *)malloc((sizeof(char)) * (stash_len + bytes_read + 1));
	if (new_stash == NULL)
	{
		free(stash);
		return (NULL);
	}
	while (i < stash_len)
	{
		new_stash[i] = stash[i];
		i++;
	}
	while (i < bytes_read + stash_len)
	{
		new_stash[i] = *buffer;
		buffer++;
		i++;
	}
	new_stash[i] = '\0';
	free(stash);
	return (new_stash);
}

char	*extract_line(char *stash)
{
	char		*ret_str;
	int			line_len;
	const int	newline_index = find_newline(stash);
	int			i;

	if(stash == NULL) line_len = 0;

	if (newline_index == -1)
		line_len = ft_strlen(stash);
	else
		line_len = newline_index + 1;
	i = 0;
	ret_str = (char *)malloc(sizeof(char) * (line_len + 1));
	if (ret_str == NULL)
		return (NULL);
	while (i < line_len)
	{
		ret_str[i] = stash[i];
		i++;
	}
	ret_str[i] = '\0';
	return (ret_str);
}

char	*trim_stash(char *stash)
{
	char		*new_stash;
	const int	newline_index = find_newline(stash);
	size_t		new_size;
	size_t		i;

	if (newline_index == -1)
	{
		free(stash);
		return (NULL);
	}
	i = 0;
	new_size = ft_strlen(stash) - newline_index;
	if (new_size == 1)
	{
		free(stash);
		return (NULL);
	}
	new_stash = (char *)malloc((sizeof(char) * new_size));
	if (new_stash == NULL)
	{
		free(stash);
		return (NULL);
	}
	while (i < new_size - 1)
	{
		new_stash[i] = stash[i + newline_index + 1];
		i++;
	}
	new_stash[i] = '\0';
	free(stash);
	return (new_stash);
}
