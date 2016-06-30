/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 12:54:20 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/30 15:34:53 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "rt.h"
#include "libft.h"
#include "parser.h"
#include <fcntl.h>
#include <unistd.h>

static t_obj	*sda_parse_fd(const int fd, t_rt *rt, t_obj *root,
	int lvl_offset)
{
	char		*line;
	int			count;
	t_sda		eval;

	eval = (t_sda){rt, root, root, 0, lvl_offset};
	count = 0;
	while ((ft_get_next_line(fd, &line) > 0) && (line))
	{
		count++;
		if (sda_eval(line, &eval, sda_lvl(line)) < 0)
			ft_printf("warning: eval failed on line: %d : %s\n", count,
				line + sda_lvl(line));
		free(line);
	}
	return (root);
}

t_obj			*sda_parse_rawtree(const char *filepath, t_rt *rt, t_obj *root,
	int lvl_offset)
{
	int		fd;

	if ((fd = open(filepath, O_RDONLY)) < 0)
		return (NULL);
	root = sda_parse_fd(fd, rt, root, lvl_offset);
	close(fd);
	return (root);
}

t_obj			*sda_parse(const char *filepath, t_rt *rt)
{
	t_obj *root;

	if (!(root = rt_factory_alloc(ROOT, NULL)))
		return (NULL);
	sda_parse_rawtree(filepath, rt, root, 0);
	yolo_parse_finalize(root);
	sda_set_defaults(root);
	camera_save(rt);
	rt_debug(root, 0);
	if (root->content)
		geo_putm4(((t_obj*)root->content)->trans, 6);
	return (root);
}
