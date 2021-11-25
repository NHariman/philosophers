# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: nhariman <nhariman@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/10/31 23:42:48 by nhariman      #+#    #+#                  #
#    Updated: 2021/11/25 17:30:35 by nhariman      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

COMPILE = gcc

FLAGS = -Wall -Werror -Wextra

C_FILES = main.c \
		str_functions.c \
		is_something.c \
		time_functions.c \
		philo_lifecycle.c \
		philo_mutex.c \
		philo_death.c \
		philo_setup.c

O_FILES = $(C_FILES:.c=.o)

NAME = philo

all: $(NAME)

$(NAME): $(O_FILES)
	@$(COMPILE) $(O_FILES) -o $@ -O3

%.o: %.c philo.h
	@$(COMPILE) -c $(FLAGS) -o $@ -c $<

clean:
	@$(RM) $(O_FILES)
	@rm -rf philo.dSYM

fclean: clean
	@$(RM) $(NAME)

re: fclean all

two: re
	./philo 4 400 200 200

one: re
	./philo 1 10 20 2

sanitize: fclean
	@$(COMPILE) $(C_FILES) -g -fsanitize=address -o $(NAME)

thread: fclean
	@$(COMPILE) $(C_FILES) -g -fsanitize=thread -o $(NAME)

try_two:
	./philo 4 400 200 200