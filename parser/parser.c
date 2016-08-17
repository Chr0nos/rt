/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/30 01:14:45 by snicolet          #+#    #+#             */
/*   Updated: 2016/08/17 19:20:00 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "sda.h"
#include "parser.h"
#include "libft.h"

static t_obj	*rt_parser_obj(const char *filepath, t_rt *rt)
{
	t_obj	*root;

	IFRET__(!(root = rt_factory_alloc(ROOT, NULL)), NULL);
	root->content = rt_factory_alloc(CAMERA, root);
	rt_factory_alloc(POINTLIGHT, root->content);
	add_mesh_from_obj(root, filepath);
	sda_set_defaults(root, rt);
	yolo_parse_finalize(root);
	camera_save(rt);
	rt_debug(root, 0);
	return (root);
}

t_obj	*rt_parser(const char *filepath, t_rt *rt)
{
	const char	*end = ft_strrchr((char*)(unsigned long)filepath, '.');

	ft_printf("trying to open %s\n", filepath);
	if (!end)
		return (NULL);
	else if (!ft_strcmp(end, ".yolo"))
	{
		rt->settings.default_reflect = (unsigned char)0xff;
		return (yolo_parse(filepath, &rt->settings));
	}
	IFRET__(!ft_strcmp(end, ".sda"), sda_parse(filepath, rt));
	IFRET__(!ft_strcmp(end, ".obj"), rt_parser_obj(filepath, rt));
	ft_putstr_fd("unknow file type: ", 2);
	ft_putendl_fd(end, 2);
	return (NULL);
}
