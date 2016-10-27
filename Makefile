# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/19 22:06:06 by snicolet          #+#    #+#              #
#*   Updated: 2016/10/27 04:10:52 by snicolet         ###   ########.fr       *#
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
INC=-I./headers -I $(DRAW)/headers/ -I $(LIBFT) -I /usr/local/include/

ifeq ($(OPSYS), Darwin)
	SDLLIB=/Library/Frameworks/SDL2.framework/Versions/A/Headers/SDL.h
	SDLHERE=$(shell test -f $(SDLLIB))
	ifeq ("$(wildcard $(SDLHERE))", "")
		SDLLINK=-L /usr/local/lib/ -L ~/.brew/lib/ -lSDL2 -lSDL2_image -lSDL2_ttf
		INC+=-I ~/.brew/include
	else
		SDLLINK=-framework sdl2 -framework SDL2_image -framework SDL2_ttf
	endif
	INC+=-I ./headers/mac
else
	SDLLINK=-lSDL2 -lSDL2_image -lSDL2_ttf
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
	yolo_setting_ambiant.o yolo_setup_cone_inf.o

SDA_DIR=parser/sda
SDA=sda_settings.o

SDA_SETUP_DIR=parser/sda/setup
SDA_SETUP=sda_setup_heightmap.o sda_setup_texture_perlin.o sda_setup_vertex.o \
		sda_setup_obj.o sda_setup_refract.o sda_setup_reflect.o \
		sda_parse.o sda_eval.o sda_lvl.o sda_setup_pos.o \
		sda_setup_color.o sda_setup_al.o sda_setup_rot.o sda_setup_fov.o \
		sda_setup_size.o sda_setup_intensity.o \
		sda_setup_include.o sda_setup_angle.o sda_setup_copy.o  \
		sda_setup_texture.o sda_setup_normal.o sda_setup_name.o \
		sda_setup_sdisable.o sda_setup_skybox.o sda_setup_background.o \
		sda_setup_csg.o sda_setup_senable.o sda_setup_alpha.o

SDA_EXPORT_DIR=parser/sda/export
SDA_EXPORT=sda_export.o sda_export_color.o sda_export_pos.o \
	sda_export_size.o sda_export_texture.o sda_export_normal.o \
	sda_export_refract.o sda_export_intensity.o sda_export_name.o \
	sda_export_angle.o sda_export_reflect.o  \
	sda_export_skybox.o sda_export_file.o  \
	sda_export_sdisable.o sda_export_al.o sda_export_bitmap.o \
	sda_export_vertex.o sda_export_obj.o sda_export_background.o \
	sda_export_senable.o

SDA_DEFAULT_DIR=parser/sda/default
SDA_DEFAULT=sda_defaults.o sda_default_lights.o sda_default_camera.o \
			sda_default_setting.o sda_default_triangle.o sda_default_cone.o \
			sda_default_shaders.o sda_default_texture.o sda_default_size.o

PARSE_OBJ_DIR=parser/obj
PARSE_OBJ=parse_obj.o parse_obj_dispatch.o parser_obj_v.o parser_obj_uv.o \
		parser_obj_n.o parser_obj_max.o parser_obj_cfgbits.o \
		parser_obj_checksplit.o

OBJ=main.o debug.o factory.o check_cube.o box.o camera.o \
	rays.o pc_rays.o bounds.o node.o puttype.o putbounds.o rad2deg.o display.o \
	configure.o putbits.o parser/parser.o check_camera.o \
	rt_quit.o export.o uv.o camera_switch.o

TEXTURE_DIR=texture
TEXTURE=texture_perlin.o texture_create.o textures_used.o textures_free.o \
		texture.o textures_cleanup.o texture_last.o texture_remove.o \
		textures_display.o

RENDER_DIR=render
RENDER=render.o render_light.o render_tree.o refract.o render_mode.o \
	render_csg.o render_nocsg.o

TYPEDIR=type
TYPE=cube.o sphere.o plane.o cone.o cyl.o cone_inf.o triangle.o

EVENTDIR=events
EVENT=mouse.o keyboard.o keybit.o events.o resize.o toggle.o

OBJECTS_DIR=objects
OBJECTS=obj_child.o obj_nparent.o obj_init.o obj_rotate.o obj_byid.o \
		obj_copy.o obj_byname.o obj_set_reflect.o obj_texture.o obj_lvl.o \
		obj_get_root.o obj_normal.o obj_count.o obj_atpx.o obj_nexttype.o

MENU_DIR=menu
MENU=ls_dir.o init.o menu_display.o menu_move.o ls_isdir.o menu_positions.o \
	menu_camera.o menu_degrade.o menu_background.o menu_clean.o menu_configure.o

FILTER_DIR=filter
FILTER=filter.o rgb.o ymc.o sepia.o

SHADER_DIR=shaders
SHADER=shaders.o shaders_init.o light.o shadow.o \
	reflection.o shader_texture.o shader_normalmap.o damier.o

ARG_DIR=arguments
ARG= arguments.o arg_fs.o arg_geometry.o \
		arg_help.o

INTER_DIR=interface
INTER=interf_init.o interf_display.o interf_event.o interf_values.o \
	interf_pos.o interf_dir.o interf_tools.o interf_font.o interf_keyboard.o

ALLOBJ=$(OBJ:%.o=$(OBJBUILDDIR)/%.o) \
	$(YOLO:%.o=$(OBJBUILDDIR)/$(YOLODIR)/%.o) \
	$(SDA:%.o=$(OBJBUILDDIR)/$(SDA_DIR)/%.o) \
	$(TYPE:%.o=$(OBJBUILDDIR)/$(TYPEDIR)/%.o) \
	$(EVENT:%.o=$(OBJBUILDDIR)/$(EVENTDIR)/%.o) \
	$(OBJECTS:%.o=$(OBJBUILDDIR)/$(OBJECTS_DIR)/%.o) \
	$(MENU:%.o=$(OBJBUILDDIR)/$(MENU_DIR)/%.o) \
	$(FILTER:%.o=$(OBJBUILDDIR)/$(FILTER_DIR)/%.o) \
	$(RENDER:%.o=$(OBJBUILDDIR)/$(RENDER_DIR)/%.o) \
	$(SHADER:%.o=$(OBJBUILDDIR)/$(SHADER_DIR)/%.o) \
	$(TEXTURE:%.o=$(OBJBUILDDIR)/$(TEXTURE_DIR)/%.o) \
	$(ARG:%.o=$(OBJBUILDDIR)/$(ARG_DIR)/%.o) \
	$(INTER:%.o=$(OBJBUILDDIR)/$(INTER_DIR)/%.o) \
	$(SDA_SETUP:%.o=$(OBJBUILDDIR)/$(SDA_SETUP_DIR)/%.o) \
	$(SDA_EXPORT:%.o=$(OBJBUILDDIR)/$(SDA_EXPORT_DIR)/%.o) \
	$(SDA_DEFAULT:%.o=$(OBJBUILDDIR)/$(SDA_DEFAULT_DIR)/%.o) \
	$(PARSE_OBJ:%.o=$(OBJBUILDDIR)/$(PARSE_OBJ_DIR)/%.o)

ALLSRC=$(OBJ:%.o=$(OBJBUILDDIR)/%.c) \
	$(YOLO:%.o=$(YOLODIR)/%.c) \
	$(SDA:%.o=$(SDA_DIR)/%.c) \
	$(TYPE:%.o=$(TYPEDIR)/%.c) \
	$(EVENT:%.o=$(EVENTDIR)/%.c) \
	$(OBJECTS:%.o=$(OBJECTS_DIR)/%.c) \
	$(MENU:%.o=$(MENU_DIR)/%.c) \
	$(FILTER:%.o=$(FILTER_DIR)/%.c) \
	$(RENDER:%.o=$(RENDER_DIR)/%.c) \
	$(SHADER:%.o=$(SHADER_DIR)/%.c) \
	$(TEXTURE:%.o=$(TEXTURE_DIR)/%.c) \
	$(ARG:%.o=$(ARG_DIR)/%.c) \
	$(INTER:%.o=$(INTER_DIR)/%.c) \
	$(SDA_SETUP:%.o=$(SDA_SETUP_DIR)/%.c) \
	$(SDA_EXPORT:%.o=$(SDA_EXPORT_DIR)/%.c) \
	$(SDA_DEFAULT:%.o=$(SDA_DEFAULT_DIR)/%.c) \
	$(PARSE_OBJ:%.o=$(PARSE_OBJ_DIR)/%.c)

ALLDIR=$(OBJBUILDDIR) \
		$(OBJBUILDDIR)/$(YOLODIR) \
		$(OBJBUILDDIR)/$(SDA_DIR) \
		$(OBJBUILDDIR)/$(TYPEDIR) \
		$(OBJBUILDDIR)/$(EVENTDIR) \
		$(OBJBUILDDIR)/$(OBJECTS_DIR) \
		$(OBJBUILDDIR)/$(MENU_DIR) \
		$(OBJBUILDDIR)/$(FILTER_DIR) \
		$(OBJBUILDDIR)/$(RENDER_DIR) \
		$(OBJBUILDDIR)/$(SHADER_DIR) \
		$(OBJBUILDDIR)/$(TEXTURE_DIR) \
		$(OBJBUILDDIR)/$(ARG_DIR) \
		$(OBJBUILDDIR)/$(INTER_DIR) \
		$(OBJBUILDDIR)/$(SDA_SETUP_DIR) \
		$(OBJBUILDDIR)/$(SDA_EXPORT_DIR) \
		$(OBJBUILDDIR)/$(SDA_DEFAULT_DIR) \
		$(OBJBUILDDIR)/$(PARSE_OBJ_DIR)

all: $(NAME)
	@if [ $(OPSYS) = 'Darwin' ] ; then \
		if [ -z $(LD_LIBRARY_PATH) ] ; then \
			echo "PLIZ: export LD_LIBRARY_PATH=~/.brew/lib"; \
		fi; \
	fi

multi:
	make -j

$(NAME): $(ALLDIR) $(LIBFT)/libft.a $(DRAW)/libdraw.a $(ALLOBJ)
	$(CC) $(ALLOBJ) $(LINKER) -o $(NAME)

$(ALLDIR):
	mkdir -p $@

$(OBJBUILDDIR)/%.o: %.c
	$(CC) -c $< -o $@ $(INC) $(FLAGS)

$(LIBFT)/Makefile:
	@echo Fetching submodules
	git submodule init
	git submodule update
	
$(LIBFT)/libft.a: $(LIBFT)/Makefile
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

lldb:
	make CC="clang -g3"
	lldb "./rt"

fsanitize:
	make CC="clang -fsanitize=address"

.PHONY: all re clean fclean pull norme
