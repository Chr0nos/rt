/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <dboudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/23 11:16:20 by dboudy            #+#    #+#             */
/*   Updated: 2016/07/21 18:18:50 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILTER_H
# define FILTER_H
# include "SDL2/SDL.h"

typedef struct			s_filter_cfg
{
	int					bit;
	unsigned int		(*filter)(unsigned int);
}						t_filter_cfg;

void					filter_apply(SDL_Surface *surface, int keyboard);
void					*get_filter(int keyboard);
unsigned int			filter_red(unsigned int color);
unsigned int			filter_green(unsigned int color);
unsigned int			filter_blue(unsigned int color);
unsigned int			filter_magenta(unsigned int color);
unsigned int			filter_yellow(unsigned int color);
unsigned int			filter_cyan(unsigned int color);
unsigned int			filter_sepia(unsigned int c);

#endif
