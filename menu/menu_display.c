/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/21 15:47:21 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/21 17:17:16 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "menu.h"

static void		menu_blitsurface(SDL_Surface *dest, SDL_Surface *src,
	t_point offset)
{
	unsigned int	*dest_pixels;
	unsigned int	*src_pixels;
	t_point			px;

	dest_pixels = dest->pixels;
	src_pixels = src->pixels;
	px.x = src->w;
	while (px.x--)
	{
		px.y = src->h;
		while (px.y--)
		{
			dest_pixels[(px.y + offset.y) * dest->w + (px.x + offset.x)] =
				src_pixels[px.y * src->w + px.y];
		}
	}
}

void			menu_display(t_rt *rt)
{
	const size_t	size = rt->rts_size;
	size_t			p;

	(void)menu_blitsurface;
	p = 0;
	draw_reset_surface(rt->sys.screen, 0xb189ab);
	while (p < size)
	{
		p++;
	}
}
