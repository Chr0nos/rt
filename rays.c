/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/29 01:06:28 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/04 18:26:54 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"
#include <unistd.h>

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

static void		rt_rays_pixels(t_rt *rt, t_ray *ray, t_camera *camp)
{
	t_v2i			px;
	t_m4			m;

	//rt_debug_ray(ray);
	px.x = rt->sys.geometry.x;
	while (px.x--)
	{
		m = draw_make_matrix_m4_x((t_v4d){0.0, 0.0, 0.0, 0.0},
			-camp->steppx.x, (t_v4d){1.0, 1.0, 1.0, 1.0});
		px.y = rt->sys.geometry.y;
		while (px.y--)
		{
			ray->dir = draw_vector_transform_m4(ray->dir, &m);
			(void)rt_raycast;
			draw_pxi(rt->sys.screen->pixels, px,
				(unsigned int)rt->sys.geometry.x,
				(raybox_check(ray, &rt->root->childs->next->hitbox)) ?
				((t_cube*)(rt->root->childs->next->content))->color : COLOR_RED);
		}
		m = draw_make_matrix_m4_y((t_v4d){0.0, 0.0, 0.0, 0.0},
			-camp->steppx.x, (t_v4d){1.0, 1.0, 1.0, 1.0});
		ray->dir = draw_vector_transform_m4(ray->dir, &m);
		m = draw_make_matrix_m4_x((t_v4d){0.0, 0.0, 0.0, 0.0},
			camp->rayreset.x * 2.0, (t_v4d){1.0, 1.0, 1.0, 1.0});
		ray->dir = draw_vector_transform_m4(ray->dir, &m);
	}
}

t_uint			rt_raycast(t_rt *rt, t_ray *ray)
{
	t_box	box;

	box = (t_box){-10.0, 10.0, -10.0, 10.0, 10.0, 20.0};
	ray->dir = (t_v4d){0.0, 0.0, 1.0, 0.0};
	ray->limit = 0.0;
	ray->start = (t_v4d){0.0, 0.0, 0.0, 0.0};
	rt_debug_ray(ray);
	ft_printf("retour: %d\n", raybox_check(ray, &box));
	ray->dir = (t_v4d){0.0, 0.0, -1.0, 0.0};
	// ft_printf("retour: %d\n", raybox_check(ray, &box));
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
	ray.start = cam->trans.w;
	ray.limit = 0.0;
	m = draw_matrix_multiply_axes_m4(camp->rayreset,
		(t_v4d){1.0, 1.0, 1.0, 1.0},
		(t_v4d){0.0, 0.0, 0.0, 0.0});
	ray.dir = draw_matrix_multiply_m4(cam->trans.z, &m);
	// rt_debug_ray(&ray);
	// ft_putstr("camera matrix: ");
	// draw_putm4(cam->trans, 6);
	// ft_putchar('\n');
	rt_rays_pixels(rt, &ray, camp);
	(void)rt_rays_pixels;
	//rt_raycast(rt, &ray);
}
