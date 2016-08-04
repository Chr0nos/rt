/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_defaults.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 21:24:11 by snicolet          #+#    #+#             */
/*   Updated: 2016/08/04 23:46:08 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "sda.h"
#include "libft.h"
#include "unistd.h"
#include "parser.h"
#include "mesh.h"

static void	sda_set_cone_default(t_obj *obj)
{
	t_cone	*cone;

	cone = obj->content;
	if (!(obj->cfgbits & SDB_ANGLE))
	{
		cone->angle = (t_v4d){
			1.0,
			0.87758256189,
			0.4794255386,
			1.83048772173
		};
	}
}

static void	sda_set_lights_default(t_obj *obj)
{
	if (!(obj->cfgbits & SDB_COLOR))
		((t_cube*)obj->content)->color = 0xffffff;
	if (!(obj->cfgbits & SDB_INTEN))
		((t_plight*)obj->content)->intensity = 100.0;
	if (!(obj->cfgbits & SDB_SIZE))
		((t_plight*)obj->content)->radius = 100.0;
}

static void	sda_set_camera_default(t_obj *obj)
{
	t_camera	*cam;

	cam = obj->content;
	if (!(obj->cfgbits & SDB_FOV))
		cam->fov = -49.124;
	yolo_camera_save(obj);
}

static void sda_set_triangle_default(t_obj *obj)
{
	t_triangle	*tri;

	tri = obj->content;
	tri->v1.uv = (t_v2f){0.0f, 1.0f};
	tri->v2.uv = (t_v2f){0.5f, 0.0f};
	tri->v3.uv = (t_v2f){1.0f, 1.0f};
	if (!(obj->cfgbits & SDB_VERTEX0))
		tri->v1.pos = (t_v4d){0.0, 0.0, 0.0, 0.0};
	if (!(obj->cfgbits & SDB_VERTEX1))
		tri->v2.pos = (t_v4d){0.0, 0.0, 0.0, 0.0};
	if (!(obj->cfgbits & SDB_VERTEX2))
		tri->v3.pos = (t_v4d){0.0, 0.0, 0.0, 0.0};
}

static int	sda_set_obj_defaults(t_obj *obj, int mode, void *userdata)
{
	t_rt	*rt;

	rt = userdata;
	(void)mode;
	if (obj->type == CAMERA)
		sda_set_camera_default(obj);
	else if (obj->type & LIGHTTYPE)
		sda_set_lights_default(obj);
	else if (obj->type == CONE)
		sda_set_cone_default(obj);
	else if (obj->type == TRIANGLE)
		sda_set_triangle_default(obj);
	if ((obj->type & SDA_SIZE) && (!(obj->cfgbits & SDB_SIZE)))
		((t_cube*)obj->content)->size = 1.0;
	return (OK);
}

void		sda_set_defaults(t_obj *root, t_rt *rt)
{
	rt_node_foreach(root, PREFIX, &sda_set_obj_defaults, rt);
}
