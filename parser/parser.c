/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/30 01:14:45 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/11 18:42:23 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "sda.h"
#include "parser.h"
#include "mesh.h"
#include "libft.h"

static int		rt_parser_obj_setting(t_rt *rt, t_obj *root)
{
	t_obj	*setting;

	IFRET__(!(setting = rt_factory_alloc(SETTING, root)), -1);
	((t_setting*)setting->content)->bgcolor = rt->settings.bgcolor;
	((t_setting*)setting->content)->al = 0.1;
	((t_setting*)setting->content)->color = 0xff0000;
	setting->cfgbits |= (SDB_BACKGROUND | SDB_AL | SDB_COLOR);
	return (0);
}

static t_obj	*rt_parser_obj(const char *filepath, t_rt *rt)
{
	t_obj	*root;
	t_obj	*mesh;

	IFRET__(!(root = rt_factory_alloc(ROOT, NULL)), NULL);
	IFRET__(!(root->content = rt_factory_alloc(CAMERA, root)), NULL);
	((t_obj*)root->content)->trans.w = (t_v4d){0.0, 0.0, -10.0, 1.0};
	((t_obj*)root->content)->cfgbits |= SDB_POS;
	rt->settings.bgcolor = 0x505050;
	rt->settings.ambiant_light = 0x101010;
	IFRET__(rt_parser_obj_setting(rt, root) < 0, NULL);
	IFRET__(!(rt_factory_alloc(POINTLIGHT, root->content)), NULL);
	IFRET__(!(mesh = rt_factory_alloc(MESH, root)), NULL);
	mesh->cfgbits |= SDB_OBJ;
	((t_mesh*)mesh->content)->filepath = ft_strdup(filepath);
	((t_mesh*)mesh->content)->color = 0xFF0000;
	if (parse_obj(mesh, filepath) < 0)
	{
		rt_node_free(root);
		return (NULL);
	}
	sda_set_defaults(root, rt);
	yolo_parse_finalize(root);
	camera_save(rt);
	return (root);
}

t_obj			*rt_parser(const char *filepath, t_rt *rt)
{
	const char	*end = ft_strrchr((char*)(unsigned long)filepath, '.');

	ft_printf("#trying to open %s\n", filepath);
	if (!end)
		return (NULL);
	else if (!ft_strcmp(end, ".yolo"))
	{
		rt->settings.default_reflect = (unsigned char)0xff;
		return (yolo_parse(filepath, &rt->settings));
	}
	IFRET__(!ft_strcmp(end, ".sda"), sda_parse(filepath, rt));
	IFRET__(!ft_strcmp(end, ".sdi"), sda_parse(filepath, rt));
	IFRET__(!ft_strcmp(end, ".obj"), rt_parser_obj(filepath, rt));
	ft_putstr_fd("#unknow file type: ", 2);
	ft_putendl_fd(end, 2);
	return (NULL);
}
