NAME = philo

SRCS = main.c philo.c input_check.c sleep.c end_death.c init.c utils.c

OBJS = ${SRCS:.c=.o}

CC = cc -Wall -Werror -Wextra

all: ${NAME}

${NAME}: ${SRCS} makefile philo.h 
		${CC} ${SRCS} -g3 -o ${NAME}

clean:
		rm -rf ${OBJS}

fclean:
		rm -rf ${NAME} ${OBJS}

re: fclean all

