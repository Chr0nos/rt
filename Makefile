# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/19 22:06:06 by snicolet          #+#    #+#              #
#    Updated: 2016/06/09 19:11:08 by snicolet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OPSYS=$(shell uname -s)
CLANGVERSION=$(shell clang -v 2>&1 | grep "clang version" | head -c19 | tail -c 5)
NAME=rtv1
FLAGS=-Wall -Wextra -Werror -pipe -Ofast -Weverything -Wno-padded -Wno-documentation-unknown-command -Wno-documentation
ifneq ($(CLANGVERSION),3.5.2)
	FLAGS+=-Wno-reserved-id-macro
endif
DRAW=./libs/libdraw
LIBFT=./libs/libft
SDL=~/.brew/include/
INC=-I./headers -I $(DRAW)/headers/ -I $(LIBFT) -I $(SDL)
CC=clang
SDL_LINUX = -L ~/.brew/lib/ -lSDL2 -lSDL2_image;
SDL_DARWIN = -framework sdl2
ifeq ($(OPSYS), Darwin)
	SDLLINK=$(SDL_DARWIN)
else
	SDLLINK=$(SDL_LINUX)
endif
LINKER=$(FLAGS) -L $(LIBFT) -L $(DRAW) -ldraw -lft -lm $(SDLLINK)
OBJ=main.o debug.o factory.o object.o check_cube.o parse_yolo.o box.o \
	yolo_setup.o events.o camera.o rays.o bounds.o node.o puttype.o \
	putbounds.o render.o rad2deg.o display.o sphere.o yolo_setup_type.o \
	plane.o mouse.o keyboard.o keybit.o

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

pull:
	git pull
	cd ./libs/libft
	git pull
	cd ./libs/libdraw
	git pull

.PHONY: all re clean fclean pull
