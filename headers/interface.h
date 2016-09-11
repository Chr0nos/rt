/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <dboudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/16 11:40:18 by dboudy            #+#    #+#             */
/*   Updated: 2016/09/11 16:25:58 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERFACE_H
# define INTERFACE_H

# include "draw.h"
# include "forms_bits.h"
# include "sda.h"
# include <SDL2/SDL_ttf.h>
# include <SDL2/SDL.h>

# define INTERF_ITEMS		17
# define INTERF_FONTS		3
# define INTERF_VALOFFSET	130
# define INTERF_OFFSETX		15
# define INTERF_OFFSETY		15
# define INTERF_OFFSET		(t_v2i){INTERF_OFFSETX, INTERF_OFFSETY}
# define INTERF_GEO			(t_v2i){400, 650}
# define INTERF_LINELEN		1024

enum						e_inter_flag
{
	INTER_SELECTED = 1,
	INTER_ENABLED = 1 << 1,
	INTER_INITIALIZED = 1 << 2,
	INTER_UPCASE = 1 << 3
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
	SDL_Surface				*title_selected;
	int						flags;
	int						mask;
	int						(*set_value)(t_sda *, t_obj *, char **);
	size_t					bit;
}							t_interface_cfg;

typedef struct				s_interface
{
	int						flags;
	int						line_pos;
	SDL_Surface				*screen;
	t_interface_font		fonts[INTERF_FONTS];
	t_interface_cfg			cfg[INTERF_ITEMS];
	t_obj					*obj_selected;
	char					line[INTERF_LINELEN];
}							t_interf;

int							interface_init(t_rt *rt);
int							interface_event(const t_v2i *mouse_pos, t_rt *rt);
void						interface_display(t_rt *rt);
void						interface_clean(t_interf *interf);
SDL_Color					interface_color(unsigned int color);
unsigned int				blend_menu(unsigned int a, unsigned b);
t_interface_cfg				*interf_getflag(t_interf *me, int mask, int n);
int							interf_setvalue(t_rt *rt, t_obj *obj,
	const char *line);
void						interf_resetline(t_interf *me);
void						interf_removeflag(t_interf *me, int mask);
int							interface_font_init(t_interf *me);
int							keydown_interface(int keycode, t_rt *rt);

/*
** sub getter
*/

char						*interf_getid(t_obj *obj, t_sda_export *e);
char						*interf_getname(t_obj *obj, t_sda_export *e);
char						*interf_gettype(t_obj *obj, t_sda_export *e);
char						*interf_getalpha(t_obj *obj, t_sda_export *e);
char						*interf_getpos_x(t_obj *obj, t_sda_export *e);
char						*interf_getpos_y(t_obj *obj, t_sda_export *e);
char						*interf_getpos_z(t_obj *obj, t_sda_export *e);
char						*interf_getdir_x(t_obj *obj, t_sda_export *e);
char						*interf_getdir_y(t_obj *obj, t_sda_export *e);
char						*interf_getdir_z(t_obj *obj, t_sda_export *e);

/*
** setter
*/

int							interf_setid(t_sda *e, t_obj *obj, char **av);

# define ICFG t_interface_cfg

static const t_interface_cfg	g_interface[INTERF_ITEMS] = {
	(ICFG){"Id ......... :",
		(t_v2i){0, 0}, &interf_getid, NULL, NULL, 0, ~0, &interf_setid, 0},
	(ICFG){"Type ....... :",
		(t_v2i){0, 56}, &interf_gettype, NULL, NULL, 0, ~0, NULL, 0},
	(ICFG){"Name ....... :",
		(t_v2i){0, 84}, &sda_export_name, NULL, NULL, 0, SDA_NAME,
		&sda_setup_name, SDB_NAME},
	(ICFG){"Texture .... :",
		(t_v2i){0, 112}, &sda_export_texture, NULL, NULL, 0, SDA_TEXTURE,
		&sda_setup_texture, SDB_TEXTURE},
	(ICFG){"pos.X ...... :",
		(t_v2i){0, 168}, &interf_getpos_x, NULL, NULL, 0, SDA_POS,
		&sda_setup_pos_x, SDB_POS},
	(ICFG){"pos.Y ...... :",
		(t_v2i){0, 196}, &interf_getpos_y, NULL, NULL, 0, SDA_POS,
		&sda_setup_pos_y, SDB_POS},
	(ICFG){"pos.Z ...... :",
		(t_v2i){0, 224}, &interf_getpos_z, NULL, NULL, 0, SDA_POS,
		&sda_setup_pos_z, SDB_POS},
	(ICFG){"dir.X ...... :",
		(t_v2i){0, 280}, &interf_getdir_x, NULL, NULL, 0, SDA_POS,
		&sda_setup_rot_x, SDB_ROT},
	(ICFG){"dir.Y ...... :",
		(t_v2i){0, 308}, &interf_getdir_y, NULL, NULL, 0, SDA_POS,
		&sda_setup_rot_y, SDB_ROT},
	(ICFG){"dir.Z ...... :",
		(t_v2i){0, 336}, &interf_getdir_z, NULL, NULL, 0, SDA_POS,
		&sda_setup_rot_z, SDB_ROT},
	(ICFG){"color.R ... :",
		(t_v2i){0, 392}, &sda_export_color_r, NULL, NULL, 0, SDA_COLOR,
		&sda_setup_color_r, SDB_COLOR},
	(ICFG){"color.G ... :",
		(t_v2i){0, 420}, &sda_export_color_g, NULL, NULL, 0, SDA_COLOR,
		&sda_setup_color_g, SDB_COLOR},
	(ICFG){"color.B ... :",
		(t_v2i){0, 448}, &sda_export_color_b, NULL, NULL, 0, SDA_COLOR,
		&sda_setup_color_b, SDB_COLOR},
	(ICFG){"Transparence :",
		(t_v2i){0, 504}, &interf_getalpha, NULL, NULL, 0, SDA_COLOR,
		&sda_setup_alpha, SDB_COLOR},
	(ICFG){"Reflection . :",
		(t_v2i){0, 532}, &sda_export_reflect, NULL, NULL, 0, SDA_REFLECT,
		&sda_setup_reflect, SDB_REFLECT},
	(ICFG){"Refraction . :",
		(t_v2i){0, 560}, &sda_export_refract, NULL, NULL, 0, SDA_REFRACT,
		&sda_setup_refract, SDB_REFRACT},
	(ICFG){"Size ....... :",
		(t_v2i){0, 588}, &sda_export_size, NULL, NULL, 0, SDA_SIZE,
		&sda_setup_size, SDB_SIZE}
};

#endif
