/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   configure.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/21 23:44:50 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/23 11:46:00 by dboudy           ###   ########.fr       */
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
	rt->settings = (t_rtcfg){0.0, RTMODE};
	rt->menu.items.x = 3;
	rt->menu.items.y = 2;
	rt->menu.thumb.x = 256;
	rt->menu.thumb.y = 256;
	rt->filtre = 0;
}
