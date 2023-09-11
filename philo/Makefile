# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/01 17:44:14 by tguerin           #+#    #+#              #
#    Updated: 2023/01/23 17:18:25 by tguerin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS += -s -j

SRCS :=		main.c \
			parse.c \
			ft_atoi.c \
			philo.c \
			routine.c \
			routine2.c \
			thread.c \
			message.c \
			utils.c

RPATH		:= `realpath --relative-to=${PWD} ${CURDIR}`/
RPATH		:= ${shell if [ "${RPATH}" != "./" ]; then echo ${RPATH}; fi}
NORMAL		:= ${shell tput sgr0}
RED			:= ${shell tput setaf 1}
GREEN		:= ${shell tput setaf 2}
BLUE		:= ${shell tput setaf 4}

OBJS	:=	${SRCS:.c=.o}
NAME	:=	philo
CC		:=	clang
CFLAGS	:=	-Wall -Wextra -Werror -pthread

.c.o:
			@${CC} -c ${CFLAGS} $< -o ${<:.c=.o}
			@printf "$(BLUE)[$(GREEN)+$(BLUE)]$(BLUE) ${RPATH}${<:.c=.o}$(NORMAL)\n"

${NAME}:	${OBJS}
			@${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${FTFLAGS}
			@printf "$(BLUE)[$(GREEN)+$(BLUE)]$(BLUE) ${RPATH}${NAME}$(NORMAL)\n"

clean:
			@${RM} ${OBJS}
			@${foreach OBJ, ${OBJS}, printf "$(BLUE)[$(RED)-$(BLUE)]$(BLUE) ${RPATH}${OBJ}$(NORMAL)\n";}

fclean:		clean
			@${RM} ${NAME}
			@printf "$(BLUE)[$(RED)-$(BLUE)]$(BLUE) ${RPATH}${NAME}$(NORMAL)\n"

re:			fclean
			@${MAKE} all

all:		${NAME}

.PHONY: clean, fclean, re, all
