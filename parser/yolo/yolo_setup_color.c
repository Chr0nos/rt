/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yolo_setup_color.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/10 18:21:08 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/10 18:22:46 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"
#include "parser.h"

unsigned int		yolo_setup_color(const char *strcolor)
{
	char			**split;
	unsigned int	color;
	size_t			splitsize;

	if (strcolor[0] == '#')
		return ((unsigned int)ft_basetoul(&strcolor[1], "0123456789ABCDEF"));
	if (ft_strcount(strcolor, ':') != 2)
		return (COLOR_BLACK);
	if (!(split = ft_strsplit(strcolor, ':')))
		return (COLOR_BLACK);
	splitsize = ft_tabcount((void**)split);
	color = (splitsize == 4) ? (unsigned int)((((ft_atoi(split[0]) & 0xff) << \
		16) | (ft_atoi(split[1]) & 0xff) << 8) | (ft_atoi(split[2]) & 0xff)) : \
		COLOR_BLACK;
	ft_free_tab(split, splitsize);
	free(split);
	return (color);
}
