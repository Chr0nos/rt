/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/21 15:47:21 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/21 19:23:07 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "menu.h"
#include "libft.h"

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
				src_pixels[px.y * src->w + px.x];
		}
	}
}

void			menu_display(t_rt *rt)
{
	const size_t	size = rt->rts_size;
	t_point			px;
	size_t			p;

	(void)size;
	(void)menu_blitsurface;
	p = 0;
	draw_reset_surface(rt->sys.screen, 0xb189ab);

	px = (t_point){10, 10};
	while (p < 6)
	{
		rt_rays(&rt->rts[p]);
		menu_blitsurface(rt->sys.screen, rt->rts[p].sys.screen, px);
		if (((p + 1) % 3 == 0) && (p))
		{
			px.y += 12 + rt->rts[p].sys.geometry.y;
			px.x = 10;
		}
		else
			px.x += 12 + rt->rts[p].sys.geometry.x;
		p++;
	}
}
