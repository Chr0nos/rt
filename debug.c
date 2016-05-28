/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 22:11:40 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/28 03:02:33 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"
#include <unistd.h>

static void		rt_puttype(int type)
{
	if (type == CUBE)
		ft_putstr("CUBE");
	else if (type == PLAN)
		ft_putstr("PLAN");
	else if (type == SPHERE)
		ft_putstr("SPHERE");
	else if (type == ROOT)
		ft_putstr("ROOT");
	else if (type == CAMERA)
		ft_putstr("CAMERA");
	else if (type == SPOT)
		ft_putstr("SPOT");
	else if (type == POINTLIGHT)
		ft_putstr("POINTLIGHT");
	else
		ft_putstr("UNKNOW");
}

static void		rt_putnchar(char c, unsigned int n)
{
	while (n--)
		write(1, &c, 1);
}

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

static void		rt_debug_pos(t_obj *obj)
{
	const unsigned int	precision = 4;
	char				*tab[3];

	tab[0] = ft_dtoa((double)obj->trans.offset.x, precision);
	tab[1] = ft_dtoa((double)obj->trans.offset.y, precision);
	tab[2] = ft_dtoa((double)obj->trans.offset.z, precision);
	ft_printf(" --- pos: (x: %s, y: %s, z: %s)", tab[0], tab[1], tab[2]);
	ft_free_tab(tab, 3);
}

void			rt_debug(t_obj *item, unsigned int level)
{
	unsigned int	color;

	rt_putnchar('\t', level);
	ft_putstr("type: ");
	rt_puttype(item->type);
	if (item->type != ROOT)
		rt_debug_pos(item);
	if (item->type & (CUBE | SPHERE | PLAN))
	{
		color = *(unsigned int*)item->content;
		ft_printf(" color: [%d:%d:%d]", (color >> 16) & 0xff,
			(color >> 8) & 0xff, color & 0xff);
	}
	write(1, "\n", 1);
	rt_debug_childs(item, level);
}
