/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qloubier <qloubier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/29 01:06:28 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/05 00:35:15 by qloubier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"
#include <unistd.h>

static void		rt_rayplan_fix(t_ray *ray, t_camera *camp, t_v2d *pfix, t_m4 *m)
{
	t_v2d		tmp;

	tmp = (t_v2d){fabs(pfix->x), fabs(pfix->y)};
	ray->dir = draw_vector_transform_m4(ray->dir, m);
	ray->start = (t_v4d){
		camp->raypos.x + (camp->mdirx.x * tmp.x) + (camp->mdiry.x * tmp.y),
		camp->raypos.y + (camp->mdirx.y * tmp.x) + (camp->mdiry.y * tmp.y),
		camp->raypos.z + (camp->mdirx.z * tmp.x) + (camp->mdiry.z * tmp.y),
		1.0};
	pfix->y -= camp->rayfix.w;
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

static void		rt_rays_pixels(t_rt *rt, t_ray *ray, t_camera *camp)
{
	t_v2i			px;
	t_v2d			pfix;
	t_m4			m;

	px.x = rt->sys.geometry.x;
	pfix.x = camp->rayfix.x;
	while (px.x--)
	{
		m = draw_make_matrix_m4_x((t_v4d){0.0, 0.0, 0.0, 0.0},
			-camp->steppx.x, (t_v4d){1.0, 1.0, 1.0, 1.0});
		px.y = rt->sys.geometry.y;
		pfix.y = camp->rayfix.y;
		while (px.y--)
		{
			// ray->dir = draw_vector_transform_m4(ray->dir, &m);
			rt_rayplan_fix(ray, camp, &pfix, &m);
			draw_pxi(rt->sys.screen->pixels, px,
				(unsigned int)rt->sys.geometry.x, rt_render(rt, ray));
		}
		m = draw_make_matrix_m4_y((t_v4d){0.0, 0.0, 0.0, 0.0},
			-camp->steppx.x, (t_v4d){1.0, 1.0, 1.0, 1.0});
		ray->dir = draw_vector_transform_m4(ray->dir, &m);
		m = draw_make_matrix_m4_x((t_v4d){0.0, 0.0, 0.0, 0.0},
			camp->rayreset.x * 2.0, (t_v4d){1.0, 1.0, 1.0, 1.0});
		ray->dir = draw_vector_transform_m4(ray->dir, &m);
		pfix.x -= camp->rayfix.z;
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
	camp->raypos = cam->trans.w;
	ray.limit = 0.0;
	m = draw_matrix_multiply_axes_m4(camp->rayreset,
		(t_v4d){1.0, 1.0, 1.0, 1.0},
		(t_v4d){0.0, 0.0, 0.0, 0.0});
	ray.dir = draw_matrix_multiply_m4(cam->trans.z, &m);
	m = draw_make_matrix_m4_x((t_v4d){0.0, 0.0, 0.0, 0.0},
		camp->rayreset.x, (t_v4d){1.0, 1.0, 1.0, 1.0});
	camp->mdiry = draw_matrix_multiply_m4(cam->trans.z, &m);
	m = draw_make_matrix_m4_y((t_v4d){0.0, 0.0, 0.0, 0.0},
		camp->rayreset.y, (t_v4d){1.0, 1.0, 1.0, 1.0});
	camp->mdirx = draw_matrix_multiply_m4(cam->trans.z, &m);
	// rt_debug_ray(&ray);
	// ft_putstr("camera matrix: ");
	// draw_putm4(cam->trans, 6);
	// ft_putchar('\n');
	rt_rays_pixels(rt, &ray, camp);
	(void)rt_rays_pixels;
	//rt_raycast(rt, &ray);
}
