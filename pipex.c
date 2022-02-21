/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopez-f <jlopez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 11:27:44 by jlopez-f          #+#    #+#             */
/*   Updated: 2022/02/11 19:03:51 by jlopez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static pid_t	ft_createchild(char *argv, char **envp, int *fd, int lastcmd)
{
	int		pfd[2];
	pid_t	pid;

	if (pipe(pfd) == -1)
		ft_errors(ERRGENERAL, "pipe");
	pid = fork();
	if (pid == -1)
		ft_errors(ERRGENERAL, "fork");
	if (pid == 0)
	{
		ft_fdschild(pfd, fd, lastcmd);
		ft_execcmd(argv, envp);
	}
	else
	{
		ft_closefd(pfd[1]);
		ft_dupfd(pfd[0], STDIN_FILENO);
		ft_closefd(pfd[0]);
	}
	return (pid);
}

static t_format	ft_launchchild(t_format c, char **argv, int argc, char **envp)
{
	while (c.i < argc - 1)
	{
		if (c.i == c.j)
			ft_createchild(argv[c.i], envp, c.fd, -1);
		else if (c.i == argc - 2)
			c.lastpid = ft_createchild(argv[c.i], envp, c.fd, 1);
		else
			ft_createchild(argv[c.i], envp, c.fd, 0);
		c.i++;
	}
	c.i = c.j;
	while (c.i < argc - 1)
	{
		c.pid = waitpid(-1, &c.status, 0);
		if (WIFEXITED(c.status) && c.pid == c.lastpid)
			c.j = WEXITSTATUS(c.status);
		c.i++;
	}
	return (c);
}

t_format	ft_startfd(t_format c, char **argv, int argc)
{
	if (!ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])))
	{
		if (argc < 6)
			ft_errors(ERRARG, NULL);
		c.i = 3;
		c.j = 3;
		ft_readheredoc(argv);
		c.fd[OUTFILE] = ft_openfile(argv[argc - 1], HEREDOC);
	}
	else
	{
		c.i = 2;
		c.j = 2;
		c.fd[INFILE] = ft_openfile(argv[1], INFILE);
		c.fd[OUTFILE] = ft_openfile(argv[argc - 1], OUTFILE);
		if (c.fd[INFILE] != -1)
		{
			ft_dupfd(c.fd[INFILE], STDIN_FILENO);
			ft_closefd(c.fd[INFILE]);
		}
	}
	return (c);
}

int	main(int argc, char **argv, char **envp)
{
	t_format	c;

	c.i = 0;
	if (*envp == NULL)
	{
		envp[0] = "PATH=/usr/bin:";
		envp[1] = NULL;
	}
	if (argc >= 5)
	{
		c = ft_startfd(c, argv, argc);
		c = ft_launchchild(c, argv, argc, envp);
		if (c.fd[OUTFILE] != -1)
			ft_closefd(c.fd[OUTFILE]);
		ft_closefd(STDIN_FILENO);
		exit (c.j);
	}
	else
		ft_errors(ERRARG, NULL);
}

/*
https://github.com/gmarcha/pipexMedic.git
https://github.com/vfurmane/pipex-tester
https://github.com/denisgodoy/pipex-tester
*/