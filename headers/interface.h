/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <dboudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/16 11:40:18 by dboudy            #+#    #+#             */
/*   Updated: 2016/09/03 21:52:35 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERFACE_H
# define INTERFACE_H

# include "draw.h"
# include "forms_bits.h"
# include "sda.h"
# include <SDL2/SDL_ttf.h>
# include <SDL2/SDL.h>

# define INTERF_ITEMS		18
# define INTERF_FONTS		2
# define INTERF_VALOFFSET	100
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
	t_v2i					offset;
	char					*(*get_value)(t_obj *, t_sda_export *);
	SDL_Surface				*title;
	int						flags;
	int						mask;
}							t_interface_cfg;

typedef struct				s_interface
{
	int						flags;
	SDL_Surface				*screen;
	t_interface_font		fonts[INTERF_FONTS];
	t_interface_cfg			cfg[INTERF_ITEMS];
	t_obj					*obj_selected;
}							t_interf;

# define ICFG t_interface_cfg

static const t_interface_cfg	g_interface[INTERF_ITEMS] = {
	(ICFG){"Id ......... :", (t_v2i){0, 0}, NULL, NULL, 0, ~0},
	(ICFG){"Type ....... :", (t_v2i){0, 56}, NULL, NULL, 0, ~0},
	(ICFG){"Name ....... :", (t_v2i){0, 84}, &sda_export_name, NULL, 0, SDA_NAME},
	(ICFG){"Texture .... :", (t_v2i){0, 112}, &sda_export_texture, NULL, 0, SDA_TEXTURE},
	(ICFG){"pos.X ...... :", (t_v2i){0, 168}, NULL, NULL, 0, SDA_POS},
	(ICFG){"pos.Y ...... :", (t_v2i){0, 196}, NULL, NULL, 0, SDA_POS},
	(ICFG){"pos.Z ...... :", (t_v2i){0, 224}, NULL, NULL, 0, SDA_POS},
	(ICFG){"dir.X ...... :", (t_v2i){0, 280}, NULL, NULL, 0, SDA_POS},
	(ICFG){"dir.Y ...... :", (t_v2i){0, 308}, NULL, NULL, 0, SDA_POS},
	(ICFG){"dir.Z ...... :", (t_v2i){0, 336}, NULL, NULL, 0, SDA_POS},
	(ICFG){"color.R ... :", (t_v2i){0, 392}, NULL, NULL, 0, SDA_COLOR},
	(ICFG){"color.G ... :", (t_v2i){0, 420}, NULL, NULL, 0, SDA_COLOR},
	(ICFG){"color.B ... :", (t_v2i){0, 448}, NULL, NULL, 0, SDA_COLOR},
	(ICFG){"Transparence :", (t_v2i){0, 504}, NULL, NULL, 0, SDA_COLOR},
	(ICFG){"Reflection . :", (t_v2i){0, 532}, NULL, NULL, 0, SDA_REFLECT},
	(ICFG){"Refraction . :", (t_v2i){0, 560}, NULL, NULL, 0, SDA_REFLECT},
	(ICFG){"Size ....... :", (t_v2i){0, 588}, &sda_export_size, NULL, 0, SDA_SIZE},
	(ICFG){"----------- ENTER ----------", (t_v2i){0, 644}, NULL, NULL, 0, 0}
};

int							interface_init(t_rt *rt);
void						interface_event(const t_v2i *mouse_pos, t_rt *rt);
void						interface_display(t_rt *rt);
void						interface_clean(t_interf *interf);
SDL_Color					interface_color(unsigned int color);

#endif
