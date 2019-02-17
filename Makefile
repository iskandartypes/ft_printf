# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ikourkji <ikourkji@student.42.us.or>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/26 19:40:37 by ikourkji          #+#    #+#              #
#    Updated: 2019/02/17 07:22:53 by ikourkji         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRC = ft_printf.c ft_printf_cont.c pf_*.c

LFTSRC = libft/ft_*.c

OBJ = ft_printf.o ft_printf_cont.o pf_*.o

LFTOBJ = libft/ft_*.o

CFLAGS = -Wall -Wextra -Werror

TST = tests/test4.c

all: $(NAME)

$(NAME):
	make -C libft
	gcc $(CFLAGS) -c $(SRC) $(LFTSRC)
	ar rc $(NAME) $(OBJ) $(LFTOBJ)
	ranlib $(NAME)

clean:
	make -C libft clean
	rm -f ft_*.o
	rm -f $(OBJ)

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all

test:
	gcc $(TST) $(SRC) $(LFT) -g -fsanitize=address

.PHONY: all clean fclean re
