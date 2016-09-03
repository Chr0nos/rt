/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_defaults.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 21:24:11 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/03 12:05:12 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "sda.h"
#include "libft.h"
#include "unistd.h"
#include "mesh.h"

static int	sda_defaults(t_obj *obj, int mode, void *userdata)
{
	int						p;

	(void)mode;
	p = SDA_COUNT_DEFAULTS;
	while (p--)
		if (obj->type & g_sda_default[p].type_mask)
			g_sda_default[p].exec(userdata, obj);
	return (OK);
}

void		sda_set_defaults(t_obj *root, t_rt *rt)
{
	rt->tree.lnum = rt_obj_count(root, LIGHTTYPE);
	rt_node_foreach(root, PREFIX, &sda_defaults, rt);
}
