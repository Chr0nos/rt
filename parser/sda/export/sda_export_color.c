/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_export_color.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/15 14:23:22 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/09 02:49:43 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "libft.h"
#include "objects.h"
#include <stdlib.h>

void	sda_export_color_raw(unsigned int color, char *color_str)
{
	int		p;
	int		missing;

	*(color_str++) = '#';
	color_str[8] = '\0';
	p = ft_ulltobuff(color_str, color, 16, "0123456789ABCDEF");
	missing = 8 - p;
	if (missing > 0)
	{
		ft_stralign_right(color_str, 8);
		ft_strreplace(color_str, ' ', '0');
	}
	if (!ft_strncmp(color_str, "00", 2))
		ft_memmove(color_str, color_str + 2, 9);
}

char	*sda_export_color_r(t_obj *obj, t_sda_export *e)
{
	int	c;

	c = (((t_cube*)obj->content)->color & 0xff0000) >> 16;
	(void)e;
	return (ft_itoa(c));
}

char	*sda_export_color_g(t_obj *obj, t_sda_export *e)
{
	int	c;

	c = (((t_cube*)obj->content)->color & 0x00ff00) >> 8;
	(void)e;
	return (ft_itoa(c));
}

char	*sda_export_color_b(t_obj *obj, t_sda_export *e)
{
	int	c;

	c = ((t_cube*)obj->content)->color & 0x0000ff;
	(void)e;
	return (ft_itoa(c));
}

char	*sda_export_color(t_obj *obj, t_sda_export *e)
{
	char	*color_str;

	(void)e;
	if (!(obj->type & SDA_COLOR))
		return (NULL);
	color_str = malloc(12);
	if (!color_str)
		return (NULL);
	sda_export_color_raw(((t_cube*)obj->content)->color, color_str);
	return (color_str);
}
