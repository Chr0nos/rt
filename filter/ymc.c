/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jmc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/23 11:20:49 by dboudy            #+#    #+#             */
/*   Updated: 2016/06/26 16:19:25 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filter.h"
#include "libft.h"

t_uint		filter_magenta(t_uint c)
{
	int	rgb[3];

	rgb[0] = (int)(c >> 16 & 0xFF);
	rgb[1] = (int)((int)(c >> 8 & 0xFF) * 0.01);
	rgb[2] = (int)(c >> 0 & 0xFF);
	rgb[0] = (rgb[0] > 255 ? 255 : ft_abs(rgb[0]));
	rgb[1] = (rgb[1] > 255 ? 255 : ft_abs(rgb[1]));
	rgb[2] = (rgb[2] > 255 ? 255 : ft_abs(rgb[2]));
	return (((t_uint)((rgb[0] << 16) + (rgb[1] << 8) + rgb[2])));
}

t_uint		filter_yellow(t_uint c)
{
	int	rgb[3];

	rgb[0] = (int)(c >> 16 & 0xFF);
	rgb[1] = (int)(c >> 8 & 0xFF);
	rgb[2] = (int)((int)(c >> 0 & 0xFF) * 0.01);
	rgb[0] = (rgb[0] > 255 ? 255 : ft_abs(rgb[0]));
	rgb[1] = (rgb[1] > 255 ? 255 : ft_abs(rgb[1]));
	rgb[2] = (rgb[2] > 255 ? 255 : ft_abs(rgb[2]));
	return (((t_uint)((rgb[0] << 16) + (rgb[1] << 8) + rgb[2])));
}

t_uint		filter_cyan(t_uint c)
{
	int	rgb[3];

	rgb[0] = (int)((int)(c >> 16 & 0xFF) * 0.01);
	rgb[1] = (int)(c >> 8 & 0xFF);
	rgb[2] = (int)(c >> 0 & 0xFF);
	rgb[0] = (rgb[0] > 255 ? 255 : ft_abs(rgb[0]));
	rgb[1] = (rgb[1] > 255 ? 255 : ft_abs(rgb[1]));
	rgb[2] = (rgb[2] > 255 ? 255 : ft_abs(rgb[2]));
	return (((t_uint)((rgb[0] << 16) + (rgb[1] << 8) + rgb[2])));
}
