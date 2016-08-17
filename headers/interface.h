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
# define LARGER_SIZE 18

typedef struct s_rt t_rt;

typedef struct  s_interface
{
  char			  *champs_str[NB_CHAMPS][LARGER_SIZE];
  SDL_Surface	*champs_txt[NB_CHAMPS];
  TTF_Font    *police_classic;
  TTF_Font    *police_selected;
  SDL_Color   color_classic;
  SDL_Color   color_selected;
  SDL_Rect    pos;
  int         font_size;
}               t_interf;

void  init_interface(t_rt *rt);
void draw_interface(t_rt *rt);
SDL_Color	*define_color(SDL_Color *color, Uint8 r, Uint8 g, Uint8 b);
TTF_Font	*define_police(TTF_Font *police, char *name, int size);
SDL_Surface	*define_texte(TTF_Font *police, char *txt, SDL_Color *color);

#endif
