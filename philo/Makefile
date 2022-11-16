NAME = philo
CC = gcc
FLAGS = -Wall -Werror -Wextra
SRC =	src/main.c \
		src/utils.c \
		src/philosopher.c \
		src/threads.c \
		src/monitoring.c \
		src/print.c \
		src/protected_threads.c

OBJ = ${SRC:%.c=%.o}

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re