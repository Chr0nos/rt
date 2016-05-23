/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_yolo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 17:18:25 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/23 20:01:54 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

static t_obj	*parse_yolo_setupobj(const char *opts, t_obj *obj)
{
	char	**split;
	size_t	size;

	split = ft_strsplit(opts, ' ');
	size = ft_tabcount((void**)split);
	if ((obj->type == SPHERE) && (size == 6))
	{
		((t_sphere*)obj->content)->radius = ft_atoi(split[0]);
	}
	ft_free_tab(split, (unsigned int)size);
	free(split);
	return (obj);
}

static t_type	parse_yolo_gettype(const char *name)
{
	const char		*tname[] = { "CUBE", "PLAN", "SPHERE", "ROOT", "CAMERA",
		"EMPTY"};
	const t_type	types[] = { CUBE, PLAN, SPHERE, ROOT, CAMERA, EMPTY };
	int				p;

	p = 6;
	while (p--)
		if (!ft_strcmp(tname[p], name))
			return (types[p]);
	return (EMPTY);
}

static int		parse_yolo_lvl(char *line)
{
	int		len;

	len = 0;
	while ((line[len]) && (line[len] == '\t'))
		len++;
	return (len);
}

static void		parse_yolo_line(char *line, int *lastlvl, t_obj **lastobj)
{
	const int	lvl = parse_yolo_lvl(line);
	t_obj		*parent;
	t_type		type;
	char		*name_type;

	type = CUBE;
	line += lvl;
	name_type = ft_strndup(line, ft_strsublen(line, ' '));
	type = parse_yolo_gettype(name_type);
	ft_printf("lvl: %d - line: %s\n", lvl, line);
	free(name_type);
	if ((*lastlvl < lvl) || ((*lastobj)->type == ROOT))
		parent = *lastobj;
	else
		parent = (*lastobj)->parent;
	line += ft_strsublen(line, ' ');
	*lastobj = parse_yolo_setupobj(line, rt_factory_alloc(type, parent));
	*lastlvl = lvl;
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
	lastlvl = 0;
	obj = rt_obj_makeroot();
	lastobj = obj;
	while (ft_get_next_line(fd, &line) > 0)
	{
		if (!line)
			break ;
		if (line[0] != '#')
			parse_yolo_line(line, &lastlvl, &lastobj);
		free(line);
	}
	close(fd);
	rt_debug(obj, 0);
	return (obj);
}
