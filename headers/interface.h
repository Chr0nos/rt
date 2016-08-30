/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <dboudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/16 11:40:18 by dboudy            #+#    #+#             */
/*   Updated: 2016/08/30 19:31:16 by dboudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERFACE_H
# define INTERFACE_H

# include "rt.h"
# include "libft.h"
# include <SDL2/SDL_ttf.h>
# include <SDL2/SDL.h>

# define NB_CHAMPS 		26
# define LARGER_SIZE	30

# define I_ID			0
# define I_VIDE2		1
# define I_TYPE			2
# define I_NAME			3
# define I_TEXT			4
# define I_VIDE3		5
# define I_POSX			6
# define I_POSY			7
# define I_POSZ			8
# define I_VIDE4		9
# define I_DIRX			10
# define I_DIRY			11
# define I_DIRZ			12
# define I_VIDE5		13
# define I_COL_R		14
# define I_COL_G		15
# define I_COL_B		16
# define I_VIDE6		17
# define I_ALPHA		18
# define I_REFL			19
# define I_REFR			20
# define I_VIDE7		21
# define I_SIZE			22
# define I_VIDE8		23
# define I_ENTER		24
# define I_END			25

typedef struct	s_rt t_rt;

typedef struct	s_interface
{
	SDL_Surface	*interf_screen;
	int			mode_activated;
	char		**champs_scale;
	char		*champs_obj[NB_CHAMPS][LARGER_SIZE];
	char		*champs_txt[NB_CHAMPS][LARGER_SIZE];
	SDL_Surface	*surface_txt[NB_CHAMPS];
	SDL_Surface	*surface_obj[NB_CHAMPS];
	SDL_Surface	*surface_scale[7];
	TTF_Font	*police_classic;
	TTF_Font	*police_selected;
	SDL_Color	color_classic;
	SDL_Color	color_selected;
	SDL_Rect	pos;
	int			font_size;
	int			scale;
	t_obj		*obj_selected;
}				t_interf;

void		init_interface(t_rt *rt);
void 		interface_display(t_rt *rt);
//void 		init_champs_obj(char *interface[NB_CHAMPS][LARGER_SIZE]);
void 		fill_champs_obj(t_obj *obj, char *champs[NB_CHAMPS][LARGER_SIZE]);
void 		fill_surfaces(char *champs[NB_CHAMPS][LARGER_SIZE],
				SDL_Surface *surf[NB_CHAMPS], TTF_Font *pol, SDL_Color *col);
void		fill_surface_scale(t_interf *in, int i_scale);

void		interf_event(t_v2i *mouse_pos, t_rt *rt);
void		change_color(int scale, int y, char *champs[NB_CHAMPS][LARGER_SIZE]);
void		change_one(int scale, int y, char *champs[NB_CHAMPS][LARGER_SIZE]);
void		change_selected_obj(t_rt *rt);
void		change_all_data_obj(t_rt *rt, char *champs[NB_CHAMPS][LARGER_SIZE]);

SDL_Color	*define_color(SDL_Color *color, Uint8 r, Uint8 g, Uint8 b);
SDL_Rect	*define_position(SDL_Rect *pos, Uint8 x, Uint8 y);
TTF_Font	*define_police(TTF_Font *police, char *name, int size, int selec);
SDL_Surface	*define_texte(TTF_Font *police, char *txt, SDL_Color *color);

void 		clean_interface(t_rt *rt);
void 		free_surfaces(SDL_Surface *surfaces[NB_CHAMPS]);

#endif
