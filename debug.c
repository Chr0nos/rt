/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 22:11:40 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/09 05:35:11 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"
#include <unistd.h>

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
	const unsigned int	precision = 2;
	char				*tab[3];

	tab[0] = ft_dtoa((double)obj->trans.w.x, precision);
	tab[1] = ft_dtoa((double)obj->trans.w.y, precision);
	tab[2] = ft_dtoa((double)obj->trans.w.z, precision);
	ft_printf("pos: (x: %s, y: %s, z: %s)", tab[0], tab[1], tab[2]);
	ft_free_tab(tab, 3);
}

static void		rt_debug_color(unsigned int level, unsigned int color)
{
	rt_putnchar('\t', level + 1);
	ft_printf("color: [%d:%d:%d]\n", (color >> 16) & 0xff,
		(color >> 8) & 0xff, color & 0xff);
}

void			rt_debug(t_obj *item, unsigned int level)
{
	if (!item)
		return ;
	rt_putnchar('\t', level);
	ft_putstr("- type: ");
	rt_puttype(item->type);
	ft_printf("[%d]", (int)item->id);
	ft_putstr("\n");
	if (item->type != ROOT)
	{
		rt_putnchar('\t', level + 1);
		rt_debug_pos(item);
		write(1, "\n", 1);
	}
	if (item->type & VISIBLE)
		rt_debug_color(level, *(unsigned int*)item->content);
	rt_putnchar('\t', level + 1);
	ft_putstr("bounds: ");
	rt_putbounds(item, 3);
	if (item->childs)
	{
		write(1, "\n", 1);
		rt_debug_childs(item, level);
	}
}
