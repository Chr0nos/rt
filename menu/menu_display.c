/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/21 15:47:21 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/26 20:08:51 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "menu.h"
#include "libft.h"
#include "keyboard.h"

static void		menu_display_flush(t_rt *rt, size_t p)
{
	const SDL_Rect	*rect = &rt->menu.positions[p];

	if (movemyass(&rt->rts[p]))
		rt_rays(&rt->rts[p]);
	draw_blitsurface(rt->sys.screen, rt->rts[p].sys.screen,
		(t_point){rect->x, rect->y});
}

void			menu_display(t_rt *rt)
{
	const size_t	size = (size_t)(rt->sys.geometry.x * rt->sys.geometry.y);
	size_t			p;
	size_t			max;

	max = (size_t)(rt->menu.items.x * rt->menu.items.y);
	ft_memcpy(rt->sys.screen->pixels, rt->menu.background->pixels,
		size * sizeof(unsigned int));
	if (rt->rts_size < max)
		max = rt->rts_size;
	p = 0;
	while (p < max)
		menu_display_flush(rt, p++);
	rt->keyboard &= MENU_ALLOW;
}
