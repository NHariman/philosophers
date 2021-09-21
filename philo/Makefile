# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: nhariman <nhariman@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/10/31 23:42:48 by nhariman      #+#    #+#                  #
#    Updated: 2021/09/21 12:23:52 by nhariman      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

COMPILE = gcc

FLAGS = -Wall -Werror -Wextra

PHILO = main.c \
		str_functions.c \
		is_something.c \
		time_functions.c \
		make_philos.c \
		philo_forks.c \
		philos_do.c

OPHILO = $(PHILO:.c=.o)

NAME = philo

all: $(NAME)

$(NAME): $(OPHILO)
	@$(COMPILE) $(OPHILO) -o $@

%.o: %.c philo.h
	@$(COMPILE) -c $(FLAGS) -o $@ -c $<

clean:
	@$(RM) $(OPHILO)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

two: re
	./philo 2 10 2 2

one: re
	./philo 1 10 2 2

sanitize: fclean
	@$(COMPILE) $(PHILO) -g -fsanitize=address -o $(NAME)

try_two:
	./philo 2 10 2 2 