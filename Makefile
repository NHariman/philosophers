# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: nhariman <nhariman@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/10/31 23:42:48 by nhariman      #+#    #+#                  #
#    Updated: 2021/07/26 14:29:35 by nhariman      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

COMPILE = gcc

FLAGS = -Wall -Werror -Wextra

PHILO =

OPHILO = $(PHILO:.c=.o)

NAME = philo

all: $(NAME)

$(NAME): $(OPHILO)
	@$(COMPILE) $(OPHILO) -o $@

%.o: %.c philo/philo.h
	@$(COMPILE) -c $(FLAGS) -o $@ -c $<

clean:
	@$(RM) $(OPHILO)

fclean: clean
	@$(RM) $(NAME)

re: fclean all