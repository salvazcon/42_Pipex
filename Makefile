# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: saazcon- <saazcon-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/23 18:29:28 by saazcon-          #+#    #+#              #
#    Updated: 2023/05/23 18:29:28 by saazcon-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= pipex
SRCS	= pipex.c
OBJS	= ${SRCS:.c=.o}
CC		= gcc
CFLAGS	= -g -Wall -Wextra -Werror
RM		= rm -f

${NAME}:	${OBJS}
			${CC} ${CFLAGS} ${OBJS} -o ${NAME}

all:		${NAME}

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re