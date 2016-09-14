/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yolo_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 17:18:25 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/14 17:25:05 by dboudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"
#include "parser.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

static t_obj	*yolo_parse_obj(const char *opts, t_obj *obj)
{
	char			**split;
	size_t			size;
	unsigned int	ofs;

	split = ft_strsplitstr(opts, " \t");
	size = ft_tabcount((void**)split);
	ofs = (obj->type & RADIUS) ? 1 : 0;
	if (size >= 3 + ofs)
	{
		obj->trans.w = (t_v4d){
			ft_atod(split[0 + ofs]),
			ft_atod(split[1 + ofs]),
			ft_atod(split[2 + ofs]),
			1.0
		};
		if (yolo_setup(obj, size - 1, split) != 0)
			ft_printf("warning: failed to setup object %s\n", split[0]);
	}
	ft_free_tab(split, (unsigned int)size);
	free(split);
	rt_obj_set_reflect(obj, 0);
	rt_obj_set_texture(obj, NULL);
	return (obj);
}

static int		yolo_parse_lvl(char *line)
{
	int		len;

	len = 0;
	while ((line[len]) && (line[len] == '\t'))
		len++;
	return (len);
}

static int		yolo_parse_line(char *line, int *lastlvl, t_obj **lastobj,
	t_rtcfg *rset)
{
	const int	lvl = yolo_parse_lvl(line);
	t_obj		*parent;
	t_type		type;
	char		*name_type;

	line += lvl;
	if ((!*line) || yolo_parse_settings(line, rset))
		return (0);
	name_type = ft_strndup(line, ft_strsublenstr(line, " \t"));
	type = rt_gettype(name_type);
	if (type == ROOT)
		type = EMPTY;
	free(name_type);
	if (type == INVALID)
		return (-1);
	if ((*lastlvl < lvl) || ((*lastobj)->type == ROOT))
		parent = *lastobj;
	else
		parent = rt_obj_nparent(*lastobj, (unsigned int)(*lastlvl - lvl + 1));
	line += ft_strsublenstr(line, " \t");
	*lastobj = yolo_parse_obj(line, rt_factory_alloc(type, parent));
	*lastlvl = lvl;
	return (0);
}

t_obj			*yolo_parse_finalize(t_obj *root)
{
	root->content = rt_obj_getcamera(root);
	rt_node_foreach(root, PREFIX, &yolo_setup_realpos, NULL);
	rt_node_foreach(root, PREFIX, &yolo_setup_type, NULL);
	rt_bounds_update(root);
	return (root);
}

t_obj			*yolo_parse(const char *filepath, t_rtcfg *rset)
{
	int		fd;
	int		lastlvl;
	char	*line;
	t_obj	*obj;
	t_obj	*lastobj;

	if ((fd = open(filepath, O_RDONLY)) < 0)
		return (NULL);
	if (!(obj = rt_factory_alloc(ROOT, NULL)))
	{
		close(fd);
		return (NULL);
	}
	lastlvl = 0;
	lastobj = obj;
	while ((ft_get_next_line(fd, &line) > 0) && (line))
	{
		if ((line[0] != '#') && (!ft_stronlystr(line, " \t")) &&
			(yolo_parse_line(line, &lastlvl, &lastobj, rset) < 0))
			break ;
		free(line);
	}
	free(line);
	close(fd);
	return (yolo_parse_finalize(obj));
}
