/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/21 13:54:03 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/21 14:43:32 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"
#include "menu.h"
#include "parser.h"

static int		menu_configure_rts(t_rt *rt, t_rt *rts, t_list *files)
{
	size_t		p;

	p = 0;
	while (files)
	{
		ft_memcpy(&rts[p], rt, sizeof(t_rt));
		rts[p].root = yolo_parse((const char*)files->content, &rts[p].settings);
		if (rts[p].root)
			p++;
		files = files->next;
	}
	return (0);
}

int		menu_init(t_rt *rt)
{
	t_list		*files;
	size_t		size;
	t_rt		*rts;
	int			ret;

	if (!(files = ls_dir("./scenes/", "*.yolo")))
		return (-2);
	size = ft_lstsize(files);
	if ((rts = malloc(sizeof(t_rt) * size)) != NULL)
	{
		ret = menu_configure_rts(rt, rts, files);
		//code utile ici
		while (size--)
			rt_node_free(rts[size].root);
		free(rts);
	}
	else
		ret = -1;
	ft_lstdel(&files, &ft_lstpulverisator);
	return (ret);
}
