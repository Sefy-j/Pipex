/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopez-f <jlopez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 13:34:47 by jlopez-f          #+#    #+#             */
/*   Updated: 2022/01/27 15:33:47 by jlopez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_format
{
	int		fd[2];
	int		i;
	int		j;
	int		status;
	pid_t	pid;
	pid_t	lastpid;
}	t_format;

# define INFILE 0
# define OUTFILE 1
# define HEREDOC 2
# define ERRFILE 0
# define ERRGENERAL 1
# define ERRNOTCMD 127
# define ERRARG	-1

size_t	ft_strlen(const char *str);
void	ft_errors(int error, char *name);
void	ft_dupfd(int fd, int fd2);
void	ft_execcmd(char *argv, char **envp);
void	ft_closefd(int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_writeheredoc(char *limiter, int *pfd);
void	ft_readheredoc(char **argv);
void	ft_fdschild(int *pfd, int *fd, int lastcmd);
int		ft_openfile(char *filename, int infile);
int		ft_strncmp(const char *sr1, const char *sr2, size_t n);
int		*ft_splitcopy(const char *str, char **result, int *i, int l);
int		*ft_splitcopyspecial(const char *str, char **result, int *i, int l);
char	*ft_strjoin(const char *s1, char const *s2);
char	**ft_split(char const *str, char c);
char	**ft_argvsplit(char const *str);
char	**ft_free(char **result, int i);
char	*get_next_line(int fd);

#endif