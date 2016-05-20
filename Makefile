# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/19 22:06:06 by snicolet          #+#    #+#              #
#    Updated: 2016/05/20 16:35:32 by snicolet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=rtv1
FLAGS=-Wall -Wextra -Werror -pipe -Ofast
DRAW=./libs/libdraw
LIBFT=./libs/libft
SDL=~/.brew/include/
INC=-I./headers -I $(DRAW)/headers/ -I $(LIBFT) -I $(SDL)
CC=clang
SDLLINK=-L ~/.brew/lib/ -lSDL2 -lSDL2_image
LINKER=$(FLAGS) -L $(LIBFT) -L $(DRAW) -ldraw -lft -lm $(SDLLINK)
OBJ=main.o 

all: $(NAME)

$(NAME): $(LIBFT)/libft.a $(DRAW)/libdraw.a $(OBJ)
	$(CC) $(OBJ) $(LINKER) -o $(NAME)

%.o: %.c
	$(CC) -c $< $(INC) $(FLAGS)

$(LIBFT)/libft.a:
	make -j -C $(LIBFT) FLAGS="$(FLAGS)"

$(DRAW)/libdraw.a:
	make -j -C $(DRAW) FLAGS="$(FLAGS)"

clean:
	make -C $(LIBFT) clean
	make -C $(DRAW) clean
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFT) fclean
	make -C $(DRAW) fclean

re: fclean all

relibs: fcleanlibs $(LIBFT)/libft.a $(DRAW)/libdraw.a $(OBJ)

linux:
	make FLAGS="$(FLAGS)" LINKER="$(FLAGS) -L $(DRAW) -ldraw -L $(LIBFT) -lft -lm"

.PHONY: all re clean fclean
