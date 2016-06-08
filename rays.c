/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qloubier <qloubier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/29 01:06:28 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/08 23:35:50 by qloubier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"
#include <unistd.h>

static void		rt_rayplan_fix(t_ray *ray, t_m4 *m)
{
	ray->dir = draw_vector_transform_m4(ray->dir, m);
}

static void		rt_debug_ray(t_ray *ray)
{
	static int		limit = 42;

	ft_putstr("start: ");
	draw_putv4d(ray->start, 3);
	ft_putstr(" dir: ");
	draw_putv4d(ray->dir, 5);
	ft_putchar('\n');
	if (!limit--)
		exit(0);
}

static void		rt_rays_pixels(t_rt *rt, t_ray *ray, t_camera *camp, t_m4 m)
{
	t_v2i			px;
	t_v4d			rad;

	(void)rt_debug_ray;
	px.x = rt->sys.geometry.x;
	rad = (t_v4d){camp->rayreset.x, 0.0, camp->steppx.x, camp->steppx.y};
	while (px.x--)
	{
		px.y = rt->sys.geometry.y;
		rad.y = camp->rayreset.y;
		while (px.y--)
		{
			ray->dir = (t_v4d){sin(rad.x), -sin(rad.y),
				cos(rad.y) * cos(rad.x), 0.0};
			rt_rayplan_fix(ray, &m);
			draw_pxi(rt->sys.screen->pixels, px,
				(unsigned int)rt->sys.geometry.x, rt_render(rt, ray));
			rad.y -= rad.w;
		}
		rad.x -= rad.z;
	}
}

void			rt_rays(t_rt *rt)
{
	t_obj		*cam;
	t_camera	*camp;
	t_ray		ray;

	cam = (t_obj*)rt->root->content;
	camp = cam->content;
	rt_update_camera(rt->sys.geometry, cam->content);
	ray.start = cam->trans.w;
	camp->raypos = cam->trans.w;
	ray.limit = 0.0;
	ray.dir = (t_v4d){0.0, 0.0, 1.0, 0.0};
	rt_rays_pixels(rt, &ray, camp, cam->trans);
	(void)rt_rays_pixels;
}
