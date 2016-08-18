/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   configure.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/21 23:44:50 by snicolet          #+#    #+#             */
/*   Updated: 2016/08/13 13:59:57 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "keyboard.h"
#include "draw.h"

void			rt_configure(t_rt *rt)
{
	rt->sys.win = NULL;
	rt->sys.screen = NULL;
	rt->sys.geometry = (t_v2i){1024, 768};
	rt->root = NULL;
	rt->rts_size = 0;
	rt->rts = NULL;
	rt->mouse = 0;
	rt->keyboard = FORCE_DISPLAY;
	rt->settings = (t_rtcfg){0, 0xFF2E2E2E, RTMODE, 8, COLOR_BLACK, COLOR_BLACK,
		0x00, 1.0f, 0, NULL};
	rt->textures = malloc(8);
	*rt->textures = NULL;
	rt->menu.thumb.x = 240;
	rt->menu.thumb.y = 238;
	rt->menu.items.x = 0;
	rt->menu.items.y = 0;
	rt->menu.background = NULL;
	rt->menu.positions = NULL;
	rt->interf = (t_interf *)ft_memalloc(sizeof(t_interf));
	rt->rayfunc = &rt_render_ray;
}
