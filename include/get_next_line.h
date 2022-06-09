/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:25:18 by omanie            #+#    #+#             */
/*   Updated: 2021/10/19 16:05:54 by omanie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# define BUFFER_SIZE 20

size_t	ftt_strlen(const char *str);
size_t	ftt_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ftt_strchr(const char *s, int c);
char	*buf_clean(char **str, char **buf);
char	*get_next_line(int fd);
#endif
