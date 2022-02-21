/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipexutils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopez-f <jlopez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 17:45:11 by jlopez-f          #+#    #+#             */
/*   Updated: 2022/01/25 18:57:33 by jlopez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_errors(int error, char *name)
{
	if (error == ERRFILE)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(name, 2);
		ft_putstr_fd(": ", 2);
		perror(NULL);
	}
	if (error == ERRGENERAL)
	{
		perror(name);
		exit (ERRGENERAL);
	}
	if (error == ERRARG)
	{
		ft_putstr_fd("Error: invalid number of arguments\n", 2);
		ft_putstr_fd("Use: ./pipex <file1> <cmd1> ... <cmdn> <file2>\n", 2);
		ft_putstr_fd("Use: ./pipex here_doc LIMITER <cmd1> <cmd2> <file>\n", 2);
		exit (ERRGENERAL);
	}
}

int	ft_openfile(char *filename, int file)
{
	int	fd;

	fd = 0;
	if (file == INFILE)
		fd = open(filename, O_RDONLY | O_CLOEXEC);
	else if (file == OUTFILE)
		fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC | O_CLOEXEC, 0600);
	else if (file == HEREDOC)
		fd = open(filename, O_CREAT | O_WRONLY | O_APPEND | O_CLOEXEC, 0600);
	if (fd == -1)
		ft_errors(ERRFILE, filename);
	return (fd);
}

void	ft_closefd(int fd)
{
	if (close(fd) == -1)
		ft_errors(ERRGENERAL, "close");
}

void	ft_dupfd(int fd, int fd2)
{
	if (dup2(fd, fd2) == -1)
		ft_errors(ERRGENERAL, "dup2");
}
