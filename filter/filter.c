/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <dboudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/23 11:12:46 by dboudy            #+#    #+#             */
/*   Updated: 2016/06/26 16:21:06 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filter.h"
#include "rt.h"
#include "keyboard.h"

void	*get_filter(int keyboard)
{
	int					p;
	const t_filter_cfg	cfg[] = {
		(t_filter_cfg){FILTER_RED, &filter_red},
		(t_filter_cfg){FILTER_GREEN, &filter_green},
		(t_filter_cfg){FILTER_BLUE, &filter_blue},
		(t_filter_cfg){FILTER_MAGENTA, &filter_magenta},
		(t_filter_cfg){FILTER_YELLOW, &filter_yellow},
		(t_filter_cfg){FILTER_CYAN, &filter_cyan},
		(t_filter_cfg){FILTER_SEPIA, &filter_sepia}
	};

	p = 7;
	while (p--)
		if (keyboard & cfg[p].bit)
			return ((void*)cfg[p].filter);
	return (NULL);
}

void	filter_apply(SDL_Surface *surface, int keyboard)
{
	t_uint			(*f)(t_uint);
	unsigned int	*pixels;
	size_t			p;

	if (!(f = (unsigned int(*)(t_uint))get_filter(keyboard)))
		return ;
	pixels = (unsigned int*)surface->pixels;
	p = (size_t)(surface->w * surface->h);
	while (p--)
		pixels[p] = f(pixels[p]);
}
