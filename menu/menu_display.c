/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/21 15:47:21 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/23 00:08:48 by snicolet         ###   ########.fr       */
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

/*
void			menu_display(t_rt *rt)
{
	size_t		p;
	SDL_Rect	*rect;

	menu_degrade(rt->sys.screen, 0xe97313, COLOR_YELLOW);
	p = rt->rts_size;
	while (p--)
	{
		rect = &rt->menu.positions[p];
		if (movemyass(&rt->rts[p]))
			rt_rays(&rt->rts[p]);
		draw_blitsurface(rt->sys.screen, rt->rts[p].sys.screen,
			(t_point){rect->x, rect->y});
		p++;
	}
	rt->keyboard = rt->keyboard & (MENU | FAST | MOVE);
}
*/

void			menu_display(t_rt *rt)
{
	size_t			max_size;
	size_t			size;
	size_t			p;
	t_point			px;

	max_size = (size_t)(rt->menu.items.x * rt->menu.items.y);
	size = (rt->rts_size < max_size) ? rt->rts_size : max_size;
	p = 0;
	menu_degrade(rt->sys.screen, 0xe97313, COLOR_YELLOW);
	px = (t_point){MENU_PADDING_X, MENU_PADDING_Y};
	while (p < size)
	{
		if (movemyass(&rt->rts[p]))
			rt_rays(&rt->rts[p]);
		draw_blitsurface(rt->sys.screen, rt->rts[p].sys.screen, px);
		if (((p + 1) % (size_t)rt->menu.items.x == 0) && (p))
		{
			px.y += MENU_BORDER_Y + rt->rts[p].sys.geometry.y;
			px.x = MENU_PADDING_X;
		}
		else
			px.x += MENU_BORDER_X + rt->rts[p].sys.geometry.x;
		p++;
	}
	rt->keyboard = rt->keyboard & (MENU | FAST | MOVE);
}
