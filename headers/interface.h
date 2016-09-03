/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <dboudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/16 11:40:18 by dboudy            #+#    #+#             */
/*   Updated: 2016/09/03 20:59:09 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERFACE_H
# define INTERFACE_H

# include "draw.h"
# include <SDL2/SDL_ttf.h>
# include <SDL2/SDL.h>

# define INTERF_ITEMS		18
# define INTERF_FONTS		2
# define INTERF_OFFSET		(t_v2i){15, 15}
# define INTERF_GEO			(t_v2i){300, 670}

enum						e_inter_flag
{
	INTER_SELECTED = 1,
	INTER_ENABLED = 1 << 1,
	INTER_INITIALIZED = 1 << 2
};

typedef	struct s_rt			t_rt;
typedef struct s_obj		t_obj;

typedef struct				s_interface_font
{
	const char				*path;
	const int				size;
	const unsigned int		color;
	TTF_Font				*font;
}							t_interface_font;

typedef struct				s_interface_cfg
{
	const char				*name;
	char					*value;
	t_v2i					offset;
	int						flags;
	SDL_Surface				*title;
}							t_interface_cfg;

typedef struct				s_interface
{
	int						flags;
	SDL_Surface				*screen;
	t_interface_font		fonts[INTERF_FONTS];
	t_interface_cfg			cfg[INTERF_ITEMS];
	t_obj					*obj_selected;
}							t_interf;

static const t_interface_cfg	g_interface[INTERF_ITEMS] = {
	(t_interface_cfg){"Id ......... :", NULL, (t_v2i){0, 0}, 0, NULL},
	(t_interface_cfg){"Type ....... :", NULL, (t_v2i){0, 56}, 0, NULL},
	(t_interface_cfg){"Name ....... :", NULL, (t_v2i){0, 84}, 0, NULL},
	(t_interface_cfg){"Texture .... :", NULL, (t_v2i){0, 112}, 0, NULL},
	(t_interface_cfg){"pos.X ...... :", NULL, (t_v2i){0, 168}, 0, NULL},
	(t_interface_cfg){"pos.Y ...... :", NULL, (t_v2i){0, 196}, 0, NULL},
	(t_interface_cfg){"pos.Z ...... :", NULL, (t_v2i){0, 224}, 0, NULL},
	(t_interface_cfg){"dir.X ...... :", NULL, (t_v2i){0, 280}, 0, NULL},
	(t_interface_cfg){"dir.Y ...... :", NULL, (t_v2i){0, 308}, 0, NULL},
	(t_interface_cfg){"dir.Z ...... :", NULL, (t_v2i){0, 336}, 0, NULL},
	(t_interface_cfg){"color.R ... :", NULL, (t_v2i){0, 392}, 0, NULL},
	(t_interface_cfg){"color.G ... :", NULL, (t_v2i){0, 420}, 0, NULL},
	(t_interface_cfg){"color.B ... :", NULL, (t_v2i){0, 448}, 0, NULL},
	(t_interface_cfg){"Transparence :", NULL, (t_v2i){0, 504}, 0, NULL},
	(t_interface_cfg){"Reflection . :", NULL, (t_v2i){0, 532}, 0, NULL},
	(t_interface_cfg){"Refraction . :", NULL, (t_v2i){0, 560}, 0, NULL},
	(t_interface_cfg){"Size ....... :", NULL, (t_v2i){0, 588}, 0, NULL},
	(t_interface_cfg){"----------- ENTER ----------", NULL, (t_v2i){0, 644}, 0,
		NULL}
};

int							interface_init(t_rt *rt);
void						interface_event(const t_v2i *mouse_pos, t_rt *rt);
void						interface_display(t_rt *rt);
void						interface_clean(t_interf *interf);

#endif
