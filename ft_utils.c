/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopez-f <jlopez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 16:40:12 by jlopez-f          #+#    #+#             */
/*   Updated: 2022/02/14 12:47:28 by jlopez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (!s)
		return ;
	i = -1;
	while (s[++i])
		write(fd, &s[i], 1);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_strncmp(const char *sr1, const char *sr2, size_t n)
{
	size_t			c;
	unsigned char	*s1;
	unsigned char	*s2;

	s1 = (unsigned char *)sr1;
	s2 = (unsigned char *)sr2;
	c = 0;
	if (n == 0)
		return (0);
	while ((s1[c] != '\0') && (s2[c] != '\0') \
			&& (s1[c] == s2[c]) && (c < (n - 1)))
		c++;
	return (s1[c] - s2[c]);
}

char	*ft_strjoin(const char *s1, char const *s2)
{
	size_t	i;
	size_t	k;
	size_t	len1;
	size_t	len2;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	i = -1;
	k = -1;
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	while (++i < len1)
		str[i] = s1[i];
	while (++k < len2)
	{
		str[i] = s2[k];
		i++;
	}
	str[i] = '\0';
	return (str);
}
