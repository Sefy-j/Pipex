SRCS	= pipex.c ft_execcmd.c ft_pipexutils.c ft_utils.c ft_split.c ft_argvsplit.c ft_splitutils.c\
		ft_childutils.c get_next_line.c get_next_line_utils.c

OBJS	= ${SRCS:.c=.o}

SRCSB	= pipex.c ft_execcmd.c ft_pipexutils.c ft_utils.c ft_split.c ft_argvsplit.c ft_splitutils.c\
		ft_childutils.c get_next_line.c get_next_line_utils.c

OBJB	= ${SRCSB:.c=.o}

NAME	= pipex

CC	= gcc

RM	= rm -f

CFLAGS	= -Wall -Wextra -Werror

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
				${CC} ${CFLAGS} -o $(NAME) $(OBJS)

bonus:		all ${OBJB}
				@make OBJS="${OBJB}"

all:		${NAME}

clean:
				${RM} ${OBJS} ${OBJB}

fclean: 	clean
				${RM} ${NAME}

re: 		fclean all

rebonus:	fclean bonus

.PHONY:		all bonus clean fclean re rebonus
