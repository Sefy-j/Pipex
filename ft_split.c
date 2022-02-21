/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopez-f <jlopez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 16:42:27 by jlopez-f          #+#    #+#             */
/*   Updated: 2022/01/27 15:12:37 by jlopez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_free(char **result, int i)
{
	while (--i >= 0)
		free(result[i]);
	free(result);
	return (0);
}

static int	ft_count(char const *str, char c)
{
	int	cpal;
	int	i;

	cpal = 0;
	i = 0;
	while (str[i] == c && str[i] != '\0')
		i++;
	while (str[i] != '\0')
	{
		while (str[i] == c && str[i] != '\0')
			i++;
		if (str[i] == '\0')
			break ;
		while (str[i] != c && str[i] != '\0')
			i++;
		if (str[i] == c || str[i] == '\0')
			cpal++;
	}
	return (cpal);
}

static int	ft_countj(const char *str, char c, int i)
{
	while (str[i] != c && str[i] != '\0')
		i++;
	return (i);
}

static char	**ft_split2(const char *str, char c, char **result, int l)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	while (str[i] != '\0' && l < ft_count(str, c))
	{
		k = 0;
		while (str[i] == c)
			i++;
		j = ft_countj(str, c, i);
		result[l] = malloc((j - i + 1) * sizeof(char));
		if (!result[l])
			return (ft_free(result, l));
		while (str[i] != c && str[i] != '\0')
		{
			result[l][k] = str[i];
			i++;
			k++;
		}
		result[l][k] = '\0';
		l++;
	}
	result[l] = NULL;
	return (result);
}

char	**ft_split(char const *str, char c)
{
	int		l;
	char	**result;

	l = 0;
	if (!str)
		return (NULL);
	result = malloc((ft_count(str, c) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	result = ft_split2(str, c, result, l);
	return (result);
}
