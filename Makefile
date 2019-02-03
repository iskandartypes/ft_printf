# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ikourkji <ikourkji@student.42.us.or>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/26 19:40:37 by ikourkji          #+#    #+#              #
#    Updated: 2019/02/03 01:58:55 by ikourkji         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRC = ft_printf.c ft_printf_cont.c pf_*.c

LFTSRC = libft/ft_*.c

OBJ = ft_printf.o ft_printf_cont.o pf_*.o

LFTOBJ = ft_*.o

CFLAGS = -Wall -Wextra -Werror

LFT = ./libft/libft.a

TST = test.c

DFLAGS = -g

FS = -fsanitize=address

all: $(NAME)

$(NAME):
	gcc $(CFLAGS) -c $(SRC) $(LFTSRC)
	ar rc $(NAME) $(OBJ) $(LFTOBJ)
	ranlib $(NAME)

clean:
	rm -f $(OBJ) $(LFTOBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

test:
	gcc $(TST) $(SRC) $(LFT)

testd:
	gcc $(DFLAGS) $(FS) $(TST) $(SRC) $(LFT)
