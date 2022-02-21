/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_childutils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopez-f <jlopez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 17:38:48 by jlopez-f          #+#    #+#             */
/*   Updated: 2022/01/25 18:17:44 by jlopez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_writeheredoc(char *limiter, int *pfd)
{
	size_t	len;
	char	*line;

	len = ft_strlen(limiter);
	while (limiter)
	{
		line = get_next_line(STDIN_FILENO);
		if (!line)
		{
			ft_closefd(pfd[0]);
			ft_closefd(pfd[1]);
			exit (ERRGENERAL);
		}
		if (!ft_strncmp(line, limiter, len) && line[len] == '\n')
		{
			ft_closefd(pfd[0]);
			ft_closefd(pfd[1]);
			exit (0);
		}
		ft_putstr_fd(line, pfd[1]);
		free(line);
	}
}

void	ft_readheredoc(char **argv)
{
	int		pfd[2];
	pid_t	pid;

	if (pipe(pfd) == -1)
		ft_errors(ERRGENERAL, "pipe");
	pid = fork();
	if (pid == -1)
		ft_errors(ERRGENERAL, "fork");
	if (pid == 0)
		ft_writeheredoc(argv[2], pfd);
	ft_closefd(pfd[1]);
	ft_dupfd(pfd[0], STDIN_FILENO);
	ft_closefd(pfd[0]);
	waitpid(pid, NULL, 0);
}

void	ft_fdschild(int *pfd, int *fd, int lastcmd)
{
	ft_closefd(pfd[0]);
	if (fd[INFILE] == -1 && lastcmd == -1)
	{
		ft_closefd(pfd[1]);
		if (fd[OUTFILE] != -1)
			ft_closefd(fd[OUTFILE]);
		exit (ERRFILE);
	}
	if (lastcmd == 1)
	{
		if (fd[OUTFILE] == -1)
		{
			ft_closefd(pfd[1]);
			exit (ERRGENERAL);
		}
		ft_dupfd(fd[OUTFILE], STDOUT_FILENO);
	}
	else
		ft_dupfd(pfd[1], STDOUT_FILENO);
	if (fd[OUTFILE] != -1)
		ft_closefd(fd[OUTFILE]);
	ft_closefd(pfd[1]);
}
