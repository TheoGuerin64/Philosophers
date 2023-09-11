MAKEFLAGS += -s -j

SRCS :=		main.c \
			parse.c \
			ft_atoi.c \
			philo.c \
			philo_routine.c \
			checking_routine.c \
			thread.c \
			process.c \
			message.c \
			utils.c

RPATH		:= `realpath --relative-to=${PWD} ${CURDIR}`/
RPATH		:= ${shell if [ "${RPATH}" != "./" ]; then echo ${RPATH}; fi}
NORMAL		:= ${shell tput sgr0}
RED			:= ${shell tput setaf 1}
GREEN		:= ${shell tput setaf 2}
BLUE		:= ${shell tput setaf 4}

OBJS	:=	${SRCS:.c=.o}
NAME	:=	philo_bonus
CC		:=	clang
CFLAGS	:=	-Wall -Wextra -Werror -pthread -g3

%.o: %.c
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
