/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execcmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopez-f <jlopez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 16:19:08 by jlopez-f          #+#    #+#             */
/*   Updated: 2022/01/25 18:17:38 by jlopez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_freepaths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

static char	*ft_checkpath2(char *argv, char **paths)
{
	int		i;
	char	*path;
	char	*temp;

	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(temp, argv);
		free(temp);
		if (!access(path, F_OK | X_OK))
		{
			ft_freepaths(paths);
			return (path);
		}
		else
			free(path);
		i++;
	}
	ft_freepaths(paths);
	return (NULL);
}

static char	*ft_checkpath(char *argv, char **envp)
{
	int		i;
	char	**paths;
	char	*path;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	path = ft_checkpath2(argv, paths);
	return (path);
}

void	ft_execcmd(char *argv, char **envp)
{
	char	*path;
	char	**cmdargs;
	int		freeable;

	freeable = 0;
	cmdargs = ft_argvsplit(argv);
	if (cmdargs[0][0] == '/')
		path = cmdargs[0];
	else
	{
		path = ft_checkpath(cmdargs[0], envp);
		freeable++;
	}
	if (path != NULL)
		execve(path, cmdargs, envp);
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(cmdargs[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	if (freeable != 0 && path)
		free(path);
	ft_freepaths(cmdargs);
	exit (ERRNOTCMD);
}
