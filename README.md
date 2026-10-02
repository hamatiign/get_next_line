*This project has been created as part of the 42 curriculum by nkato.*

# get_next_line

## Description

`get_next_line` is a C function that returns one line at a time from a file
descriptor. Repeated calls continue from the previous position until the end
of the input is reached.

The project focuses on buffered input, dynamic memory management, and keeping
state between function calls. The returned line includes its terminating
newline when one exists. The function returns `NULL` when there is nothing
left to read or when an error occurs.

```c
char	*get_next_line(int fd);
```

This repository implements the mandatory part of the project. It keeps one
static stash and therefore does not manage several file descriptors
independently at the same time.

## Instructions

### Requirements

- A C compiler such as `cc`
- A POSIX-compatible environment providing `read()`

### Compilation

Compile the implementation with a test file:

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
    get_next_line.c get_next_line_utils.c your_test.c -o gnl_test
```

Then run the resulting program:

```sh
./gnl_test
```

`BUFFER_SIZE` controls the maximum number of bytes requested by each
`read()` call. It can be changed at compilation time:

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=1 \
    get_next_line.c get_next_line_utils.c your_test.c -o gnl_test
```

The project also compiles without `-D BUFFER_SIZE`; in that case the default
value defined in `get_next_line.h` is used.

Useful sizes to test, as suggested by the subject, include `1`, `42`, `9999`,
and `10000000`.

### Usage

The caller owns every non-`NULL` line returned by `get_next_line()` and must
release it with `free()`.

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("example.txt", O_RDONLY);
	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	while (line != NULL)
	{
		/* Use line here. */
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
```

## Algorithm and design choices

The implementation uses a static string named `stash` to preserve bytes that
were read but do not belong to the line currently being returned.

1. Validate the file descriptor and `BUFFER_SIZE`, then allocate a temporary
   read buffer.
2. If `stash` does not contain a newline, call `read()` repeatedly and append
   each successful read to it.
3. Stop reading when a newline is present or `read()` reports end-of-file.
4. Allocate and return a new string containing the first complete line, or all
   remaining bytes when the input ends without a newline.
5. Remove the returned line from `stash`. The remaining bytes are preserved
   for the next call.
6. Release temporary and replaced allocations on success and error paths.

This design was selected because a single `read()` may return less than
`BUFFER_SIZE`, more than one logical line may be present in one buffer, and a
line may span several reads. Keeping the unread suffix in `stash` allows each
call to return exactly one line without reading and storing the whole file in
advance.

The helper functions have distinct ownership roles:

- `append_stash()` consumes the old stash and returns its expanded replacement.
- `extract_line()` only reads the stash and allocates the line for the caller.
- `trim_stash()` consumes the old stash and returns the unread remainder.
- Cleanup helpers free owned memory and clear persistent pointers where needed.

Repeatedly expanding `stash` copies its existing contents, so a very long line
may require more copying than a chunked data structure. The chosen approach is
kept intentionally small and explicit for this project's restricted API and
memory-management learning goals.

## Resources

- subject-pdf(42 Intranet project subject)
- Local manual pages: `man 2 read`, `man 3 malloc`, and `man 3 free`
- https://zenn.dev/grigri_grin/articles/bf45a9fa50f25f
- https://zenn.dev/jugeeeemu/articles/8a2f6342ef8e00
- https://ja.wikipedia.org/wiki/End_Of_File

## AI Usage

- AI was used to summarize and translate the assignment requirements.
- AI was used as a supplementary tool for design discussions, code improvements, and brainstorming.
- AI was used to extract the README requirements from the subject PDF and help structure this document against the implemented code.

When I use AI, I use generative AI solely for auxiliary purposes. Whenever I use AI, I carefully review the generated content, compare it with the source code, and verify it using local tools as needed. The responsibility for understanding and explaining all submitted code and documentation remains with nkato.