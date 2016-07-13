/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   configure.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/21 23:44:50 by snicolet          #+#    #+#             */
/*   Updated: 2016/07/13 21:25:06 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "keyboard.h"

void			rt_configure(t_rt *rt)
{
	rt->sys.win = NULL;
	rt->sys.screen = NULL;
	rt->root = NULL;
	rt->rts_size = 0;
	rt->rts = NULL;
	rt->mouse = 0;
	rt->keyboard = FORCE_DISPLAY;
	rt->settings = (t_rtcfg){0.0, RTMODE, 8};
	rt->textures = NULL;
	rt->menu.thumb.x = 240;
	rt->menu.thumb.y = 238;
	rt->menu.items.x = 0;
	rt->menu.items.y = 0;
	rt->menu.background = NULL;
	rt->menu.positions = NULL;
}
