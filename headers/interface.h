/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/16 11:40:18 by dboudy            #+#    #+#             */
/*   Updated: 2016/08/16 11:40:21 by dboudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERFACE_H
# define INTERFACE_H

# include "rt.h"
# include "libft.h"
# include <SDL2/SDL_ttf.h>
# include <SDL2/SDL.h>

# define NB_CHAMPS 		28
# define LARGER_SIZE	30

# define I_SCALE		0
# define I_VIDE1		1
# define I_ID			2
# define I_VIDE2		3
# define I_TYPE			4
# define I_NAME			5
# define I_TEXT			6
# define I_VIDE3		7
# define I_POSX			8
# define I_POSY			9
# define I_POSZ			10
# define I_VIDE4		11
# define I_DIRX			12
# define I_DIRY			13
# define I_DIRZ			14
# define I_VIDE5		15
# define I_COL_R		16
# define I_COL_G		17
# define I_COL_B		18
# define I_VIDE6		19
# define I_ALPHA		20
# define I_REFL			21
# define I_REFR			22
# define I_VIDE7		23
# define I_SIZE			24
# define I_VIDE8		25
# define I_ENTER		26
# define I_END			27

typedef struct s_rt t_rt;

typedef struct  s_interface
{
//	t_draw			win;
	int         mode_activated;
  char        *champs_obj[NB_CHAMPS][LARGER_SIZE];
  char			  *champs_txt[NB_CHAMPS][LARGER_SIZE];
  SDL_Surface	*surface_txt[NB_CHAMPS];
  SDL_Surface	*surface_obj[NB_CHAMPS];
  TTF_Font    *police_classic;
  TTF_Font    *police_selected;
  SDL_Color   color_classic;
  SDL_Color   color_selected;
  SDL_Rect    pos;
  int         font_size;
  int         scale;
  t_obj       *obj_selected;
}               t_interf;

void init_interface(t_rt *rt);
void interface_display(t_rt *rt);
void init_champs_obj(char *interface[NB_CHAMPS][LARGER_SIZE]);
void fill_champs_obj(t_obj *obj, char *champs_obj[NB_CHAMPS][LARGER_SIZE]);
void fill_surfaces(char *champs[NB_CHAMPS][LARGER_SIZE],
	SDL_Surface *surface[NB_CHAMPS], TTF_Font *police, SDL_Color *color);

int			interf_event(t_v2i *mouse_pos, t_rt *rt);
void	change_all_data_obj(t_rt *rt, char *champs_obj[NB_CHAMPS][LARGER_SIZE]);

SDL_Color	*define_color(SDL_Color *color, Uint8 r, Uint8 g, Uint8 b);
SDL_Rect	*define_position(SDL_Rect *pos, Uint8 x, Uint8 y);
TTF_Font	*define_police(TTF_Font *police, char *name, int size, int selected);
SDL_Surface	*define_texte(TTF_Font *police, char *txt, SDL_Color *color);

void clean_interface(t_rt *rt);
void free_champs(char *champs[NB_CHAMPS][LARGER_SIZE]);
void free_surfaces(SDL_Surface *surfaces[NB_CHAMPS]);

#endif
