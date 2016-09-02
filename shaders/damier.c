/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   damier.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/02 15:26:30 by dboudy            #+#    #+#             */
/*   Updated: 2016/09/02 16:08:30 by dboudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void		shader_damier(t_shader *s, t_render *r, t_obj *light,
		t_uint *color_render)
{
	t_uint	p[3];
	t_uint	color[2];

	(void)s;
	(void)light;
	color[0] = (t_uint)(r->ray->color - r->ray->color * 0.5);
	color[1] = (t_uint)(r->ray->color + r->ray->color * 0.5);
	p[0] = (t_uint)(r->intersection.x * 0.5);
	p[1] = (t_uint)(r->intersection.y * 0.5);
	p[2] = (t_uint)(r->intersection.z * 0.5);
	if ((p[2] % 2))
	{
		if ((p[0] % 2 && p[1] % 2) || (!(p[0] % 2) && !(p[1] % 2)))
			*color_render = color[0];
		else
			*color_render = color[1];
	}
	else
	{
		if ((p[0] % 2 && p[1] % 2) || (!(p[0] % 2) && !(p[1] % 2)))
			*color_render = color[1];
		else
			*color_render = color[0];
	}
}
