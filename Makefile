# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/19 22:06:06 by snicolet          #+#    #+#              #
#    Updated: 2016/06/16 18:09:22 by snicolet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OPSYS=$(shell uname -s)
HOSTNAME=$(shell hostname)
CLANGVERSION=$(shell clang -v 2>&1 | grep "clang version" | head -c19 | tail -c 5)
NAME=rtv1
FLAGS=-Wall -Wextra -Werror -pipe -Ofast -march=native -mtune=native -Weverything -Wno-padded -Wno-documentation-unknown-command -Wno-documentation
ifneq ($(CLANGVERSION),3.5.2)
	FLAGS+=-Wno-reserved-id-macro
endif
DRAW=./libs/libdraw
LIBFT=./libs/libft
CC=clang
OBJBUILDDIR=build
INC=-I./headers -I $(DRAW)/headers/ -I $(LIBFT)
ifeq ($(OPSYS), Darwin)
	SDLLIB=/Library/Frameworks/SDL2.framework/Versions/A/Headers/SDL.h
	SDLHERE=$(shell test -f $(SDLLIB))
	ifneq (, $(SDLHERE))
		SDLLINK=-L ~/.brew/lib/ -lSDL2
		INC+=-I ~/.brew/include
	else
		SDLLINK=-framework sdl2
	endif
	INC+=-I ./headers/mac
else
	SDLLINK=-lSDL2
	ifeq ($(HOSTNAME),stark)
		INC+=-I./headers/mac
	else
		INC+=-I./headers/linux
	endif
endif
LINKER=$(FLAGS) -L $(LIBFT) -L $(DRAW) -ldraw -lft -lm $(SDLLINK)

YOLODIR=parser/yolo
YOLO=yolo_parse.o yolo_setup_type.o yolo_setup_cube.o yolo_setup_camera.o \
	yolo_setup_plan.o yolo_setup.o yolo_setup_color.o yolo_setup_cone.o \
	yolo_setup_cyl.o

OBJ=main.o debug.o factory.o object.o check_cube.o box.o camera.o render_tree.o \
	rays.o bounds.o node.o puttype.o putbounds.o render.o rad2deg.o display.o

TYPEDIR=type
TYPE=cube.o sphere.o plane.o cone.o cyl.o

EVENTDIR=events
EVENT=mouse.o keyboard.o keybit.o events.o

ALLOBJ=$(OBJ:%.o=$(OBJBUILDDIR)/%.o) \
	$(YOLO:%.o=$(OBJBUILDDIR)/$(YOLODIR)/%.o) \
	$(TYPE:%.o=$(OBJBUILDDIR)/$(TYPEDIR)/%.o) \
	$(EVENT:%.o=$(OBJBUILDDIR)/$(EVENTDIR)/%.o)

ALLDIR=$(OBJBUILDDIR) \
		$(OBJBUILDDIR)/$(YOLODIR) \
		$(OBJBUILDDIR)/$(TYPEDIR) \
		$(OBJBUILDDIR)/$(EVENTDIR)

all: $(NAME)

$(NAME): $(ALLDIR) $(LIBFT)/libft.a $(DRAW)/libdraw.a $(ALLOBJ)
	$(CC) $(ALLOBJ) $(LINKER) -o $(NAME)

$(ALLDIR):
	mkdir -p $@

$(OBJBUILDDIR)/%.o: %.c
	$(CC) -c $< -o $@ $(INC) $(FLAGS)

$(LIBFT)/libft.a:
	make -j -C $(LIBFT) FLAGS="$(FLAGS)"

$(DRAW)/libdraw.a:
	make -j -C $(DRAW) FLAGS="$(FLAGS)"

clean:
	make -C $(LIBFT) clean
	make -C $(DRAW) clean
	$(RM) -r $(OBJBUILDDIR)

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFT) fclean
	make -C $(DRAW) fclean

re: fclean all

proper: all clean

relibs: fcleanlibs $(LIBFT)/libft.a $(DRAW)/libdraw.a $(ALLDIR) $(ALLOBJ)

pull:
	git pull origin master
	cd ./libs/libft && git pull origin master
	cd ./libs/libdraw && git pull origin master

.PHONY: all re clean fclean pull
