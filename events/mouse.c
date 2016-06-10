/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/09 17:40:57 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/09 17:41:19 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "keyboard.h"

int				mouseclick(SDL_Event *event, t_rt *rt)
{
	if (event->motion.type == SDL_MOUSEBUTTONDOWN)
	{
		if (event->button.button == SDL_BUTTON_LEFT)
			rt->keyboard |= ZOOMIN;
		else if (event->button.button == SDL_BUTTON_RIGHT)
			rt->keyboard |= ZOOMOUT;
	}
	else
	{
		if ((event->button.button == SDL_BUTTON_LEFT) &&
			(rt->keyboard & ZOOMIN))
			rt->keyboard ^= ZOOMIN;
		else if ((event->button.button == SDL_BUTTON_RIGHT) &&
			(rt->keyboard & ZOOMOUT))
			rt->keyboard ^= ZOOMOUT;
	}
	return (0);
}
