/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopez-f <jlopez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 13:38:21 by jlopez-f          #+#    #+#             */
/*   Updated: 2022/02/21 18:03:53 by jlopez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

size_t	ft_strlen(const char *str);
size_t	ft_linelen(const char *line);
char	*ft_strdup(const char *src);
char	*ft_strchr(const char *str, int c);
char	*ft_strjoingnl(char const *s1, char const *s2);
char	*get_next_line(int fd);

#endif
