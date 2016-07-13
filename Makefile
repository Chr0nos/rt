# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alhote <alhote@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/19 22:06:06 by snicolet          #+#    #+#              #
#    Updated: 2016/07/13 20:43:28 by alhote           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OPSYS=$(shell uname -s)
HOSTNAME=$(shell hostname)
CLANGVERSION=$(shell clang -v 2>&1 | grep "clang version" | head -c19 | tail -c 5)
NAME=rt
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
	ifeq ("$(wildcard $(SDLHERE))", "")
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
LINKER=$(FLAGS) -L $(LIBFT) -L $(DRAW) -ldraw -lft -lm $(SDLLINK) -lpthread

YOLODIR=parser/yolo
YOLO=yolo_parse.o yolo_setup_type.o yolo_setup_cube.o yolo_setup_camera.o \
	yolo_setup_plan.o yolo_setup.o yolo_setup_color.o yolo_setup_cone.o \
	yolo_setup_cyl.o yolo_setup_plight.o yolo_parse_settings.o \
	yolo_setting_ambiant.o yolo_setup_tore.o yolo_setup_texture.o \
	yolo_setup_cone_inf.o

SDA_DIR=parser/sda
SDA=sda_parse.o sda_eval.o sda_lvl.o sda_settings.o sda_setup_pos.o \
	sda_setup_color.o sda_setup_al.o sda_setup_rot.o sda_setup_fov.o \
	sda_setup_size.o sda_setup_intensity.o sda_defaults.o sda_setup_refract.o \
	sda_setup_include.o sda_setup_angle.o sda_setup_copy.o sda_setup_name.o

OBJ=main.o debug.o factory.o check_cube.o box.o camera.o \
	rays.o bounds.o node.o puttype.o putbounds.o rad2deg.o display.o \
	configure.o blend.o putbits.o parser/parser.o check_camera.o

RENDER_DIR=render
RENDER=render.o render_light.o render_tree.o refract.o

TYPEDIR=type
TYPE=cube.o sphere.o plane.o cone.o cyl.o tore.o cone_inf.o

EVENTDIR=events
EVENT=mouse.o keyboard.o keybit.o events.o resize.o

OBJECTS_DIR=objects
OBJECTS=obj_child.o obj_nparent.o obj_init.o obj_rotate.o obj_byid.o \
		obj_copy.o obj_byname.o

MENU_DIR=menu
MENU=ls_dir.o init.o menu_display.o menu_move.o ls_isdir.o menu_positions.o \
	menu_camera.o menu_degrade.o menu_background.o menu_clean.o menu_configure.o

FILTER_DIR=filter
FILTER=filter.o rgb.o ymc.o sepia.o

SHADER_DIR=shaders
SHADER=shaders.o shaders_init.o ambiant.o light.o shadow.o damier.o reflection.o

ALLOBJ=$(OBJ:%.o=$(OBJBUILDDIR)/%.o) \
	$(YOLO:%.o=$(OBJBUILDDIR)/$(YOLODIR)/%.o) \
	$(SDA:%.o=$(OBJBUILDDIR)/$(SDA_DIR)/%.o) \
	$(TYPE:%.o=$(OBJBUILDDIR)/$(TYPEDIR)/%.o) \
	$(EVENT:%.o=$(OBJBUILDDIR)/$(EVENTDIR)/%.o) \
	$(OBJECTS:%.o=$(OBJBUILDDIR)/$(OBJECTS_DIR)/%.o) \
	$(MENU:%.o=$(OBJBUILDDIR)/$(MENU_DIR)/%.o) \
	$(FILTER:%.o=$(OBJBUILDDIR)/$(FILTER_DIR)/%.o) \
	$(RENDER:%.o=$(OBJBUILDDIR)/$(RENDER_DIR)/%.o) \
	$(SHADER:%.o=$(OBJBUILDDIR)/$(SHADER_DIR)/%.o)

ALLSRC=$(OBJ:%.o=$(OBJBUILDDIR)/%.c) \
	$(YOLO:%.o=$(YOLODIR)/%.c) \
	$(SDA:%.o=$(SDA_DIR)/%.c) \
	$(TYPE:%.o=$(TYPEDIR)/%.c) \
	$(EVENT:%.o=$(EVENTDIR)/%.c) \
	$(OBJECTS:%.o=$(OBJECTS_DIR)/%.c) \
	$(MENU:%.o=$(MENU_DIR)/%.c) \
	$(FILTER:%.o=$(FILTER_DIR)/%.c) \
	$(RENDER:%.o=$(RENDER_DIR)/%.c) \
	$(SHADER:%.o=$(SHADER_DIR)/%.c)

ALLDIR=$(OBJBUILDDIR) \
		$(OBJBUILDDIR)/$(YOLODIR) \
		$(OBJBUILDDIR)/$(SDA_DIR) \
		$(OBJBUILDDIR)/$(TYPEDIR) \
		$(OBJBUILDDIR)/$(EVENTDIR) \
		$(OBJBUILDDIR)/$(OBJECTS_DIR) \
		$(OBJBUILDDIR)/$(MENU_DIR) \
		$(OBJBUILDDIR)/$(FILTER_DIR) \
		$(OBJBUILDDIR)/$(RENDER_DIR) \
		$(OBJBUILDDIR)/$(SHADER_DIR)

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

norme:
ifeq ($(OPSYS),Darwin)
	@printf "\e[33mChecking 42 Norme :\e[m\n"
	@norminette $(ALLSRC) headers/*.h | awk 'BEGIN { FS=":"; filename="" }\
	 	$$1 == "Norme" { filename=$$2; }\
		$$1 ~ /Error .+/ { \
			if (filename != "") {\
				print "\n\033[1;31mErrors on :\033[0;36m"filename;\
				filename=""\
			} \
			sub("Error ","",$$1);\
			if ($$2 == " C++ comment") { print "\033[0;33m"$$1"\033[32m"$$2 }\
			else { print "\033[0;33m"$$1"\033[0m"$$2 }\
		}'
else
	@printf "\e[33mNo Norminette here\e[m\n"
endif

.PHONY: all re clean fclean pull norme
