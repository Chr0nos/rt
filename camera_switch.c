/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_switch.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/24 18:54:59 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/01 15:05:38 by dboudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "objects.h"
#include "keyboard.h"

int		camera_switch(t_rt *rt)
{
	t_obj	*cam;
	t_obj	*newcam;

	rt->keyboard |= FORCE_DISPLAY;
	cam = rt->root->content;
	if (!(newcam = rt_obj_nexttype(rt->root, cam, CAMERA)))
		newcam = rt_obj_nexttype(rt->root, NULL, CAMERA);
	if ((newcam == cam) || (!newcam))
	{
		ft_putendl("no more camera");
		return (0);
	}
	rt->root->content = newcam;
	return (1);
}
