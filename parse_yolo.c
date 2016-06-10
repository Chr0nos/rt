/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_yolo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 17:18:25 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/10 18:36:01 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"
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
		obj->trans.w = (t_v4d){ft_atod(split[0 + ofs]),
			ft_atod(split[1 + ofs]), ft_atod(split[2 + ofs]), 1.0};
		yolo_setup(obj, size - 1, split);
	}
	ft_free_tab(split, (unsigned int)size);
	free(split);
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

static int		parse_yolo_line(char *line, int *lastlvl, t_obj **lastobj)
{
	const int	lvl = yolo_parse_lvl(line);
	t_obj		*parent;
	t_type		type;
	char		*name_type;

	line += lvl;
	if (!*line)
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

static t_obj	*yolo_parse_finalize(t_obj *root)
{
	root->content = rt_obj_getcamera(root);
	rt_node_foreach(root, PREFIX, &yolo_setup_realpos, NULL);
	rt_node_foreach(root, PREFIX, &yolo_setup_type, NULL);
	return (root);
}

t_obj			*parse_yolo(const char *filepath)
{
	int		fd;
	int		lastlvl;
	char	*line;
	t_obj	*obj;
	t_obj	*lastobj;

	if ((fd = open(filepath, O_RDONLY)) < 0)
		return (NULL);
	if (!(obj = rt_obj_makeroot()))
	{
		close(fd);
		return (NULL);
	}
	lastlvl = 0;
	lastobj = obj;
	while ((ft_get_next_line(fd, &line) > 0) && (line))
	{
		if ((line[0] != '#') && (!ft_stronlystr(line, " \t")) &&
			(parse_yolo_line(line, &lastlvl, &lastobj) < 0) &&
			(ft_mfree(1, line)))
			break ;
		free(line);
	}
	close(fd);
	return (yolo_parse_finalize(obj));
}
