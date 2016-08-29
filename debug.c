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

static void		rt_debug_color(unsigned int level, unsigned int color)
{
	char		hex[12];
	const char	*ba = "0123456789ABCEDF";

	ft_itobase((int)color, hex, 16, ba);
	ft_stralign_right(hex, 6);
	ft_strreplace(hex, ' ', '0');
	if (hex[0] == '-')
		ft_memmove(hex, &hex[1], 11);
	ft_putnchar('\t', level + 1);
	ft_printf("color: [%d:%d:%d] (#%s)\n", (color >> 16) & 0xff,
		(color >> 8) & 0xff, color & 0xff, hex);
}

static void		rt_debug_rot(t_obj *obj, unsigned int lvl)
{
	char	*av[6];

	av[0] = ft_dtoa(obj->rotation.x, 6);
	av[1] = ft_dtoa(obj->rotation.y, 6);
	av[2] = ft_dtoa(obj->rotation.z, 6);
	av[3] = ft_dtoa(rad2deg(obj->rotation.x), 6);
	av[4] = ft_dtoa(rad2deg(obj->rotation.y), 6);
	av[5] = ft_dtoa(rad2deg(obj->rotation.z), 6);
	ft_putnchar('\t', lvl + 1);
	ft_printf("rotation rad: {%s, %s, %s}\n", av[0], av[1], av[2]);
	ft_putnchar('\t', lvl + 1);
	ft_printf("rotation deg: {%s, %s, %s}\n", av[3], av[4], av[5]);
	ft_free_tab(av, 6);
}

static void		rt_debug_elems(t_obj *obj, unsigned int lvl)
{
	const unsigned int	precision = 2;
	char				*tab[3];

	if (obj->type != ROOT)
	{
		ft_putnchar('\t', lvl + 1);
		tab[0] = ft_dtoa((double)obj->trans.w.x, precision);
		tab[1] = ft_dtoa((double)obj->trans.w.y, precision);
		tab[2] = ft_dtoa((double)obj->trans.w.z, precision);
		ft_printf("pos: (x: %s, y: %s, z: %s)\n", tab[0], tab[1], tab[2]);
		ft_free_tab(tab, 3);
	}
	if ((obj->cfgbits & SDB_COLOR) && (obj->type != SETTING))
		rt_debug_color(lvl, *(unsigned int*)obj->content);
	ft_debug_pstr("bounds: ", lvl + 1);
	rt_putbounds(obj, 3);
	if (obj->cfgbits & SDB_ROT)
		rt_debug_rot(obj, lvl);
	ft_debug_pstr("config: ", lvl + 1);
	rt_putbits((unsigned int)obj->cfgbits);
}

void			rt_debug(t_obj *item, unsigned int level)
{
	if (!item)
		return ;
	ft_debug_pstr("- type: ", level);
	rt_puttype(item->type, 1);
	ft_printf("[%d]\n", (int)item->id);
	rt_debug_elems(item, level);
	write(1, "\n", 1);
	if (item->childs)
	{
		write(1, "\n", 1);
		rt_debug_childs(item, level);
	}
}
