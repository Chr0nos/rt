/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/21 15:47:21 by snicolet          #+#    #+#             */
/*   Updated: 2016/07/13 23:54:42 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "menu.h"
#include "libft.h"
#include "keyboard.h"

static void		menu_display_flush(t_rt *rt, size_t p)
{
	const SDL_Rect	*rect = &rt->menu.positions[p];

ft_putendl("a");
	if (((!rt_checkcamera(&rt->rts[p]))) || (!rt->sys.screen))
	{
		rt->rts[p].keyboard = 0;
		return ;
	}
	if (movemyass(&rt->rts[p]))
	{
ft_putendl("displaing");
		rt_rays(&rt->rts[p]);
	}
ft_putendl("moved");
	draw_blitsurface(rt->sys.screen, rt->rts[p].sys.screen,
		(t_point){rect->x, rect->y});
}

void			menu_display(t_rt *rt)
{
	const size_t	size = (size_t)(rt->sys.geometry.x * rt->sys.geometry.y);
	size_t			p;
	size_t			max;

	max = (size_t)(rt->menu.items.x * rt->menu.items.y);
	if (rt->menu.background)
		ft_memcpy(rt->sys.screen->pixels, rt->menu.background->pixels,
			size * sizeof(unsigned int));
	if (rt->rts_size < max)
		max = rt->rts_size;
	p = 0;
	while (p < max)
		menu_display_flush(rt, p++);
	rt->keyboard &= MENU_ALLOW;
}
