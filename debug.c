/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 22:11:40 by snicolet          #+#    #+#             */
/*   Updated: 2016/08/29 12:54:00 by dboudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"
#include <unistd.h>
#include "sda.h"
#include "objects.h"
#include <limits.h>

static void		rt_debug_childs(t_obj *item, unsigned int level)
{
	t_obj	*x;

	x = item->childs;
	while (x)
	{
		rt_debug(x, level + 1);
		x = x->next;
	}
}

static void		rt_printf_ntab(struct s_printf *pf)
{
	const unsigned int		n = (unsigned int)pf->raw_value * 2;

	if (n > INT_MAX)
		return ;
	ft_printf_padding(pf, ' ', (int)n);
	pf->slen += n;
}

static void		rt_debug_rot(const t_v4d rad, unsigned int lvl)
{
	t_v4d		deg;

	deg = (t_v4d){
		.x = rad2deg(rad.x),
		.y = rad2deg(rad.y),
		.z = rad2deg(rad.z),
		.w = 0.0
	};
	ft_printf("%k %s {%.6f, %.6f, %.6f}\n%k %s {%.6f, %.6f, %.6f}\n",
		&rt_printf_ntab, lvl, "rotation rad:", rad.x, rad.y, rad.z,
		&rt_printf_ntab, lvl, "rotation deg:", deg.x, deg.y, deg.z);
}

static void		rt_debug_elems(t_obj *obj, unsigned int lvl)
{
	if (obj->type != ROOT)
	{
		ft_printf("%k pos: (%s%.2f%s%.2f%s%.2f)\n",
			&rt_printf_ntab, lvl + 1,
			"x: ", obj->trans.w.x,
			", y: ", obj->trans.w.y,
			", z: ", obj->trans.w.z);
	}
	if ((obj->cfgbits & SDB_COLOR) && (obj->type != SETTING))
	{
		ft_printf("%k color: #%010x\n",
			&rt_printf_ntab, lvl + 1, *(unsigned int *)obj->content);
	}
	ft_printf("%k %s [%f:%f] [%f:%f] [%f:%f]\n",
		&rt_printf_ntab, lvl + 1,
		"bounds:",
		(double)obj->bounds.xmin, (double)obj->bounds.xmax,
		(double)obj->bounds.ymin, (double)obj->bounds.ymax,
		(double)obj->bounds.zmin, (double)obj->bounds.zmax);
	if (obj->cfgbits & SDB_ROT)
		rt_debug_rot(obj->rotation, lvl + 1);
	ft_printf("%k %s %064lb",
		&rt_printf_ntab, lvl + 1, "config:", obj->cfgbits);
}

void			rt_debug(t_obj *item, unsigned int level)
{
	if (!item)
		return ;
	ft_printf("\n%k %s %s [%u]\n",
		&rt_printf_ntab, level, "- type:", get_strtype((int)item->type),
		item->id);
	rt_debug_elems(item, level + 2);
	write(1, "\n", 1);
	if (item->childs)
	{
		write(1, "\n", 1);
		rt_debug_childs(item, level);
	}
}
