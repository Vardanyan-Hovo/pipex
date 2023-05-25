# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hvardany <hvardany@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/18 19:17:29 by hvardany          #+#    #+#              #
#    Updated: 2022/08/30 21:15:11 by hvardany         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRCS	= pipex.c access_if.c ft_split.c ft_strlen.c ft_strjoin.c featch1.c

OBG	= ${SRCS:.c=.o}

NAME	= pipex

CC		= cc

WALL	= -Wall -Werror -Wextra -I.

RMIF		= rm -f

.c.o:
	${CC} ${WALL} -c $< -o ${<:.c=.o}

${NAME}:	${OBG}

all:		${NAME}

clean:
			${RMIF} ${OBG}

fclean:		clean
			${RMIF}	${NAME}

bonus:		${NAME}

re:			fclean all

.PHONY:		all clean fclean re
