/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <dboudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/23 11:16:20 by dboudy            #+#    #+#             */
/*   Updated: 2016/06/26 16:24:04 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILTER_H
# define FILTER_H
# include "SDL2/SDL.h"

typedef unsigned int	t_uint;

typedef struct			s_filter_cfg
{
	int					bit;
	t_uint				(*filter)(t_uint);
}						t_filter_cfg;

void					filter_apply(SDL_Surface *surface, int keyboard);
void					*get_filter(int keyboard);
t_uint					filter_red(t_uint color);
t_uint					filter_green(t_uint color);
t_uint					filter_blue(t_uint color);
t_uint					filter_magenta(t_uint color);
t_uint					filter_yellow(t_uint color);
t_uint					filter_cyan(t_uint color);
t_uint					filter_sepia(t_uint	c);

#endif
