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

# define NB_CHAMPS  24
# define LARGER_SIZE 30

typedef struct s_rt t_rt;

typedef struct  s_interface
{
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
void fill_champs_obj(t_obj *obj, char *champs_obj[NB_CHAMPS][LARGER_SIZE]);
void fill_surfaces(char *champs[NB_CHAMPS][LARGER_SIZE],
	SDL_Surface *surface[NB_CHAMPS], TTF_Font *police, SDL_Color *color);

int			interf_event(t_v2i *mouse_pos, t_rt *rt);
//int			change_interf_scale(int x);
//void		change_one_champs_obj(int scale, int x,
//	char *interf_champs[NB_CHAMPS][LARGER_SIZE]);
void	change_all_data_obj(t_obj *obj, char *champs_obj[NB_CHAMPS][LARGER_SIZE]);
//void		change_one_champs_obj(t_obj *obj,
//	char *interf_champs[NB_CHAMPS][LARGER_SIZE]);

void		define_interf_obj(t_obj *obj, t_rt *rt);
SDL_Color	*define_color(SDL_Color *color, Uint8 r, Uint8 g, Uint8 b);
SDL_Rect	*define_position(SDL_Rect *pos, Uint8 x, Uint8 y);
TTF_Font	*define_police(TTF_Font *police, char *name, int size, int selected);
SDL_Surface	*define_texte(TTF_Font *police, char *txt, SDL_Color *color);

void clean_interface(t_rt *rt);
void free_old_data_obj(t_obj *obj);
void free_champs(char *champs[NB_CHAMPS][LARGER_SIZE]);
void free_surfaces(SDL_Surface *surfaces[NB_CHAMPS]);

#endif
