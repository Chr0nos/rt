/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_setup_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 20:06:20 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/10 00:01:45 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "libft.h"
#include "rt.h"
#include "objects.h"

t_uint					sda_setup_color_text(const char *str, unsigned int mask,
	unsigned int color, int deca)
{
	int		value;

	value = ft_atoi(str);
	if (value > 0xff)
		value = 0xff;
	else if (value < 0)
		value = 0;
	color = ((color & mask) | ((unsigned int)value << deca));
	return (color);
}

int						sda_setup_color_r(t_sda *e, t_obj *obj, char **av)
{
	(void)e;
	if (!(obj->type & SDA_COLOR))
		return (0);
	((t_cube*)obj->content)->color = (sda_setup_color_text(av[0], 0xff00ffff,
		((t_cube*)obj->content)->color, 16));
	return (1);
}

int						sda_setup_color_g(t_sda *e, t_obj *obj, char **av)
{
	(void)e;
	if (!(obj->type & SDA_COLOR))
		return (0);
	((t_cube*)obj->content)->color = (sda_setup_color_text(av[0], 0xffff00ff,
		((t_cube*)obj->content)->color, 8));
	return (1);
}

int						sda_setup_color_b(t_sda *e, t_obj *obj, char **av)
{
	(void)e;
	if (!(obj->type & SDA_COLOR))
		return (0);
	((t_cube*)obj->content)->color = (sda_setup_color_text(av[0], 0xffffff00,
		((t_cube*)obj->content)->color, 0));
	return (1);
}

int						sda_setup_color(t_sda *e, t_obj *obj, char **av)
{
	unsigned long	raw_color;
	unsigned int	color;

	if (av[0][0] != '#')
		return (0);
	ft_strtoupper(av[0]);
	raw_color = ft_basetoul((const char*)&av[0][1],
		"0123456789ABCDEF");
	if (raw_color > 0xffffffff)
		color = 0xffffffff;
	else
		color = (unsigned int)raw_color;
	if (obj->type == SETTING)
	{
		e->rt->settings.default_color = color;
		((t_setting*)obj->content)->color = color;
	}
	else
		((t_cube*)obj->content)->color = color;
	return (1);
}
