/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkato <nkato@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 16:57:01 by nkato             #+#    #+#             */
/*   Updated: 2026/10/01 16:57:02 by nkato            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif

#include <stdlib.h>
#include <unistd.h>
char *get_next_line(int fd);
size_t ft_strlen(const char *s);
int find_newline(char *str);
char *append_stash(char *stash, char *buffer, ssize_t bytes_read,
                   size_t *stash_len);
char *extract_line(char *stash);
char *trim_stash(char *stash);
#endif
