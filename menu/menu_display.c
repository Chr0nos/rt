/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/21 15:47:21 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/21 16:10:46 by snicolet         ###   ########.fr       */
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

void			menu_display(const size_t size, t_rt *rts, t_rt *rt)
{
	size_t	p;

	(void)menu_blitsurface;
	(void)rts;
	p = 0;
	draw_reset_surface(rt->sys.screen, 0xb189ab);
	while (p < size)
	{

		p++;
	}
	SDL_LockSurface(rt->sys.screen);
	SDL_UpdateWindowSurface(rt->sys.win);
	SDL_UnlockSurface(rt->sys.screen);
}
