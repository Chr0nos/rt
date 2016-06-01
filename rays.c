/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/29 01:06:28 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/01 20:52:08 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"
#include <unistd.h>

static void		rt_debug_ray(t_ray *ray)
{
	static int		limit = 42;

	ft_putstr("start: ");
	draw_putvector(ray->start, 3);
	ft_putstr(" dir: ");
	draw_putvector(ray->dir, 5);
	ft_putchar('\n');
	if (!limit--)
		exit(0);
}

static void		rt_rays_pixels(t_rt *rt, t_ray *ray, t_camera *camp)
{
	t_v2i			px;
	t_m4			m;

	//rt_debug_ray(ray);
	px.x = rt->sys.geometry.x;
	while (px.x--)
	{
		m = draw_make_matrix_m4_x((double)camp->steppx.y);
		px.y = rt->sys.geometry.y;
		while (px.y--)
		{
			ray->dir = draw_vector_transform(ray->dir, &m);
			//rt_debug_ray(ray);
			(void)rt_raycast;
			if (raybox_check(ray, &rt->root->childs->next->hitbox))
				draw_pxi(rt->sys.screen->pixels, px, (unsigned int)rt->sys.geometry.x, COLOR_WHITE);
			else
				draw_pxi(rt->sys.screen->pixels, px, (unsigned int)rt->sys.geometry.x, COLOR_RED);
			//rt_raycast(rt, ray);
		}
		m = draw_make_matrix_m4_y((double)camp->steppx.x);
		ray->dir = draw_vector_transform(ray->dir, &m);
	}
}

t_uint			rt_raycast(t_rt *rt, t_ray *ray)
{
	rt_debug_ray(ray);
	(void)rt;
	(void)ray;
	return (COLOR_BLACK);
}

void			rt_rays(t_rt *rt)
{
	t_obj		*cam;
	t_camera	*camp;
	t_ray		ray;
	t_mattf		m;

	cam = (t_obj*)rt->root->content;
	camp = cam->content;
	rt_update_camera(rt->sys.geometry, cam->content);
	ray.start = cam->trans.offset;
	ray.limit = 0.0;
	m = draw_matrix_multiply_axes(camp->rayreset, (t_v3f){1.0, 1.0, 1.0},
		(t_v3f){0.0, 0.0, 0.0});
	ray.dir = draw_matrix_multiply(cam->trans.z, &m);
	rt_rays_pixels(rt, &ray, camp);
}
