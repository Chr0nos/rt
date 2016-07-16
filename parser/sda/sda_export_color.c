/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_export_color.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/15 14:23:22 by snicolet          #+#    #+#             */
/*   Updated: 2016/07/15 23:40:31 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "libft.h"
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

char	*sda_export_color(t_obj *obj)
{
	char	*color_str;

	color_str = malloc(12);
	if (!color_str)
		return (NULL);
	sda_export_color_raw(((t_cube*)obj->content)->color, color_str);
	return (color_str);
}
