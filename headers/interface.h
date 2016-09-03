/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <dboudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/16 11:40:18 by dboudy            #+#    #+#             */
/*   Updated: 2016/09/03 15:38:20 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERFACE_H
# define INTERFACE_H

# include "rt.h"
# include "libft.h"
# include <SDL2/SDL_ttf.h>
# include <SDL2/SDL.h>

# define INTERF_ITEMS	18
# define INTERF_FONTS	2

enum					e_inter_flag
{
	INTER_SELECTED = 1,
	INTER_ENABLED = 1 << 1
};

typedef	struct s_rt		t_rt;

typedef struct			s_interface_font
{
	const char			*path;
	const int			size;
	const unsigned int	color;
	TTF_Font			*font;
}						t_interface_font;

typedef struct			s_interface_cfg
{
	const char			*name;
	char				*value;
	t_v2i				offset;
	int					flags;
	SDL_Surface			*title;
}						t_inteface_cfg;

typedef struct			s_interface
{
	int					flags;
	SDL_Surface			*screen;
	t_interface_font	fonts[INTERF_FONTS];
	t_obj				*obj_selected;
}						t_interf;

static t_inteface_cfg	g_interface[INTERF_ITEMS] = {
	(t_inteface_cfg){"Id ......... :", NULL, (t_v2i){0, 0}, 0, NULL},
	(t_inteface_cfg){"Type ....... :", NULL, (t_v2i){0, 6}, 0, NULL},
	(t_inteface_cfg){"Name ....... :", NULL, (t_v2i){0, 9}, 0, NULL},
	(t_inteface_cfg){"Texture .... :", NULL, (t_v2i){0, 12}, 0, NULL},
	(t_inteface_cfg){"pos.X ...... :", NULL, (t_v2i){0, 18}, 0, NULL},
	(t_inteface_cfg){"pos.Y ...... :", NULL, (t_v2i){0, 21}, 0, NULL},
	(t_inteface_cfg){"pos.Z ...... :", NULL, (t_v2i){0, 24}, 0, NULL},
	(t_inteface_cfg){"dir.X ...... :", NULL, (t_v2i){0, 30}, 0, NULL},
	(t_inteface_cfg){"dir.Y ...... :", NULL, (t_v2i){0, 33}, 0, NULL},
	(t_inteface_cfg){"dir.Z ...... :", NULL, (t_v2i){0, 36}, 0, NULL},
	(t_inteface_cfg){"color.R ... :", NULL, (t_v2i){0, 40}, 0, NULL},
	(t_inteface_cfg){"color.G ... :", NULL, (t_v2i){0, 43}, 0, NULL},
	(t_inteface_cfg){"color.B ... :", NULL, (t_v2i){0, 46}, 0, NULL},
	(t_inteface_cfg){"Transparence :", NULL, (t_v2i){0, 50}, 0, NULL},
	(t_inteface_cfg){"Reflection . :", NULL, (t_v2i){0, 53}, 0, NULL},
	(t_inteface_cfg){"Refraction . :", NULL, (t_v2i){0, 56}, 0, NULL},
	(t_inteface_cfg){"Size ....... :", NULL, (t_v2i){0, 59}, 0, NULL},
	(t_inteface_cfg){"----------- ENTER ----------", NULL, (t_v2i){0, 62}, 0,
		NULL}
};

void					interface_init(t_rt *rt);
void					interface_event(const t_v2i *mouse_pos, t_rt *rt);
void					interface_display(t_rt *rt);

#endif
