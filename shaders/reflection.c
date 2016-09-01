/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 20:27:31 by alhote            #+#    #+#             */
/*   Updated: 2016/09/01 16:51:39 by dboudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "rt.h"
#include "shaders.h"

void			shader_reflection(t_shader *s, t_render *r, t_obj *light,
		unsigned int *color_render)
{
	t_ray			ray;
	unsigned char	reflect;
	const double	dot = 2.0 * geo_dotv4(r->ray->dir, r->normal);

	(void)s;
	(void)light;
	ray = *r->ray;
	ray.start = geo_addv4(r->intersection, geo_multv4(ray.dir,
		geo_dtov4d(-0.00001)));
	ray.dir = (t_v4d){
		r->ray->dir.x - dot * r->normal.x,
		r->ray->dir.y - dot * r->normal.y,
		r->ray->dir.z - dot * r->normal.z,
		0.0
	};
	if ((ray.count--) && ((reflect = rt_obj_get_reflect(r->obj_intersect)) > 0))
		*color_render = blend_multiply(r->rt->rayfunc(r->rt, &ray),
			to_rgb(0, reflect, reflect, reflect));
}
