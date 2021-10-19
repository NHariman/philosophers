# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: nhariman <nhariman@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/10/31 23:42:48 by nhariman      #+#    #+#                  #
#    Updated: 2021/10/19 14:18:32 by nhariman      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

COMPILE = gcc

FLAGS = -Wall -Werror -Wextra

PHILO = main.c \
		str_functions.c \
		is_something.c \
		time_functions.c \
		philo_lifecycle.c \
		philo_monitoring.c \
		philo_mutex.c \
		philo_setup.c

OPHILO = $(PHILO:.c=.o)

NAME = philo

all: $(NAME)

$(NAME): $(OPHILO)
	@$(COMPILE) $(OPHILO) -o $@

%.o: %.c philo.h
	@$(COMPILE) -c $(FLAGS) -o $@ -c $<

clean:
	@$(RM) $(OPHILO)
	@rm -rf philo.dSYM

fclean: clean
	@$(RM) $(NAME)

re: fclean all

two: re
	./philo 4 400 200 200

one: re
	./philo 1 10 20 2

sanitize: fclean
	@$(COMPILE) $(PHILO) -g -fsanitize=address -o $(NAME)

thread: fclean
	@$(COMPILE) $(PHILO) -g -fsanitize=thread -o $(NAME)

try_two:
	./philo 4 400 200 200