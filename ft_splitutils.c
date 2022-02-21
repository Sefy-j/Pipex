/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitutils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopez-f <jlopez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 15:39:43 by jlopez-f          #+#    #+#             */
/*   Updated: 2022/01/25 18:17:21 by jlopez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	*ft_splitcopy(const char *str, char **result, int *i, int l)
{
	result[l][i[2]] = str[i[0]];
	i[0]++;
	i[2]++;
	return (i);
}

int	*ft_splitcopyspecial(const char *str, char **result, int *i, int l)
{
	if (str[i[0]] == '\'' )
	{
		i[0]++;
		while (str[i[0]] != '\'' && str[i[0]] != '\0')
			i = ft_splitcopy(str, result, i, l);
		i[0]++;
	}
	else if (str[i[0]] == '\"' )
	{
		i[0]++;
		while (str[i[0]] != '\"' && str[i[0]] != '\0')
			i = ft_splitcopy(str, result, i, l);
		i[0]++;
	}
	else
	{
		while (str[i[0]] != ' ' && str[i[0]] != '\0')
			i = ft_splitcopy(str, result, i, l);
	}
	return (i);
}
