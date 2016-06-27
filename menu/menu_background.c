/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_background.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/27 13:05:43 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/27 13:10:32 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "menu.h"

void			menu_background_init(t_rt *rt)
{
	if (!(rt->menu.background = draw_make_surface(rt->sys.geometry)))
		ft_putendl_fd("error: failed to malloc background surface", 2);
	else
		menu_degrade(rt->menu.background, 0xfb70f6, COLOR_YELLOW);
}

void			menu_background_update(t_rt *rt)
{
	SDL_FreeSurface(rt->menu.background);
	menu_background_init(rt);
}
