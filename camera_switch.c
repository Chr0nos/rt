/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_switch.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/24 18:54:59 by snicolet          #+#    #+#             */
/*   Updated: 2016/08/24 18:58:09 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "objects.h"

int		camera_switch(t_rt *rt)
{
	t_obj	*cam;
	t_obj	*newcam;

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
