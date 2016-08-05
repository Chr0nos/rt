/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/29 01:06:28 by snicolet          #+#    #+#             */
/*   Updated: 2016/08/05 12:19:13 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"
#include "filter.h"
#include <unistd.h>

char			rt_rays_pc(const t_v2i geometry, const t_v2i px)
{
	unsigned int		end;
	unsigned int		pos;

	end = (unsigned int)(geometry.x * geometry.y + geometry.x);
	pos = (unsigned int)(px.x * px.y + px.x);
	return ((char)((float)end / (float)pos * 100.0f));
}

static void		rt_rays_pixels(t_rt *rt, t_ray *ray, unsigned int *pixels,
	t_m4 m)
{
	t_v2i			px;
	t_v4d			rad;
	t_camera		*camp;

	px = (t_v2i){0, 0};
	if (!(rt->settings.cfgbits & RT_CFGB_INMENU))
		rt_signal_singletone((t_v2i*)&rt->sys.geometry, &px, 0);
	camp = ((t_obj*)rt->root->content)->content;
	px.x = rt->sys.geometry.x;
	rad = (t_v4d){camp->rayfix.x, 0.0, camp->rayfix.z, camp->rayfix.w};
	while (px.x--)
	{
		px.y = rt->sys.geometry.y;
		rad.y = camp->rayfix.y;
		while (px.y--)
		{
			ray->count = 2;
			ray->dir = geo_m4trans(
				geo_normv4((t_v4d){rad.x, -rad.y, 1.0, 0.0}), &m);
			pixels[px.y * rt->sys.geometry.x + px.x] = rt->rayfunc(rt, ray);
			rad.y -= rad.w;
		}
		if ((!(rt->settings.cfgbits & RT_CFGB_NOREFRESHX)) && (!(px.x % 100)) &&
			(rt->sys.screen))
			sdl_flush(rt);
		rad.x -= rad.z;
	}
	if (!(rt->settings.cfgbits & RT_CFGB_INMENU))
		rt_signal_singletone(NULL, NULL, 1);
	filter_apply(rt->sys.screen, rt->keyboard);
}

void			rt_rays(t_rt *rt)
{
	t_obj		*cam;
	t_ray		ray;

	cam = (t_obj*)rt->root->content;
	rt_update_camera(rt->sys.geometry, cam->content);
	ray.start = cam->trans.w;
	((t_camera*)cam->content)->raypos = cam->trans.w;
	ray.limit = 0.0;
	ray.dir = (t_v4d){0.0, 0.0, 1.0, 0.0};
	rt_rays_pixels(rt, &ray, rt->sys.screen->pixels, cam->trans);
}
