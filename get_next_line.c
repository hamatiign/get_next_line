#include "./get_next_line.h"
#include <sys/types.h>

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*buffer[BUFFER_SIZE + 1];
	ssize_t		bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (find_newline(stash) == -1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (NULL);
	}
}
