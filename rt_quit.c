/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_quit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/21 15:01:01 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/05 20:01:37 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "draw.h"

int		rt_quit(t_rt *rt, int retcode)
{
	if (rt->settings.cfgbits & RT_CFGB_FREESCREEN)
	{
		SDL_FreeSurface(rt->sys.screen);
		rt->sys.screen = NULL;
	}
	if (rt->render_screen)
		SDL_FreeSurface(rt->render_screen);
	if (rt->sys.screen)
		draw_quit(&rt->sys);
	textures_free(*rt->textures);
	rt_node_free(rt->root);
	free(rt->textures);
	return (retcode);
}
