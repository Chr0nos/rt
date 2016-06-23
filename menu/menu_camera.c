/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/23 18:52:38 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/23 19:08:35 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "menu.h"
#include "keyboard.h"

int				menu_camera_reset(t_rt *rt)
{
	size_t	p;

	p = rt->rts_size;
	while (p--)
		camera_reset(&rt->rts[p]);
	rt->keyboard |= FORCE_DISPLAY;
	return (0);
}

int				menu_camera_save(t_rt *rt)
{
	size_t		p;

	p = rt->rts_size;
	while (p--)
		camera_save(&rt->rts[p]);
	return (0);
}
