/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 12:54:20 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/29 21:48:43 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "rt.h"
#include "libft.h"
#include "parser.h"
#include <fcntl.h>
#include <unistd.h>

static t_obj	*sda_parse_fd(const int fd, t_rt *rt, t_obj *root)
{
	char	*line;
	int		count;

	count = 0;
	while ((ft_get_next_line(fd, &line) > 0) && (line))
	{
		count++;
		if (sda_eval(line, rt, root, sda_lvl(line)) < 0)
			ft_printf("warning: eval failed on line: %d : %s\n", count,
				line + sda_lvl(line));
		free(line);
	}
	return (root);
}

t_obj			*sda_parse(const char *filepath, t_rt *rt)
{
	int		fd;
	t_obj	*root;

	if ((fd = open(filepath, O_RDONLY)) < 0)
		return (NULL);
	root = sda_parse_fd(fd, rt, rt_factory_alloc(ROOT, NULL));
	close(fd);
	yolo_parse_finalize(root);
	sda_set_defaults(root);
	camera_save(rt);
	rt_debug(root, 0);
	geo_putm4(((t_obj*)root->content)->trans, 6);
	return (root);
}
