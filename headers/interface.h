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

# define NB_CHAMPS  16
# define LARGER_SIZE 30

typedef struct s_rt t_rt;

typedef struct  s_interface
{
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
  t_uint         id_selected;
}               t_interf;

void  init_interface(t_rt *rt);
void interface_display(t_rt *rt);
void init_selected_obj(t_obj *obj, char *champs_obj[NB_CHAMPS][LARGER_SIZE]);
void init_surface_data(char *champs[NB_CHAMPS][LARGER_SIZE],
	SDL_Surface *surface[NB_CHAMPS], TTF_Font *police, SDL_Color *color);
SDL_Color	*define_color(SDL_Color *color, Uint8 r, Uint8 g, Uint8 b);
TTF_Font	*define_police(TTF_Font *police, char *name, int size, int selected);
SDL_Surface	*define_texte(TTF_Font *police, char *txt, SDL_Color *color);
void free_champs(char *champs[NB_CHAMPS][LARGER_SIZE]);
void free_surfaces(SDL_Surface *surfaces[NB_CHAMPS]);

#endif
