/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/21 15:47:21 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/23 14:54:27 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "menu.h"
#include "libft.h"
#include "keyboard.h"

static void 	menu_degrade(SDL_Surface *surface,
	const unsigned int scolor, const unsigned int ecolor)
{
	int				line;
	int				col;
	float			pc;
	unsigned int	*pixels;

	col = surface->w;
	while (col--)
	{
		pc = (float)col / (float)surface->w;
		((unsigned int *)surface->pixels)[col] = draw_color_lerp(scolor, ecolor,
			pc);
	}
	line = surface->h;
	while (line-- > 1)
	{
		pixels = &((unsigned int *)surface->pixels)[line * surface->w];
		ft_memcpy(pixels, surface->pixels,
			(size_t)surface->w * sizeof(unsigned int));
	}
}

int				menu_camera_reset(t_rt *rt)
{
	size_t	p;

	p = rt->rts_size;
	while (p--)
		camera_reset(&rt->rts[p]);
	return (0);
}

void			menu_display(t_rt *rt)
{
	size_t		p;
	size_t		max;
	SDL_Rect	*rect;

	menu_degrade(rt->sys.screen, 0xe97313, COLOR_YELLOW);
	max = (size_t)(rt->menu.items.x * rt->menu.items.y);
	if (rt->rts_size < max)
		max = rt->rts_size;
	p = 0;
	while (p < max)
	{
		rect = &rt->menu.positions[p];
		if (movemyass(&rt->rts[p]))
			rt_rays(&rt->rts[p]);
		draw_blitsurface(rt->sys.screen, rt->rts[p].sys.screen,
			(t_point){rect->x, rect->y});
		p++;
	}
	rt->keyboard = rt->keyboard & (MENU | FAST | MOVE | FILTER);
}
