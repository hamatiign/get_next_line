#include "./get_next_line.h"
#include <stdlib.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

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

char	*update(char *stash, char *buffer, ssize_t bytes_read)
{
	size_t	stash_len;
	char	*new_stash;
	int		i;

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
