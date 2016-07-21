/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sepia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <dboudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/23 17:14:46 by dboudy            #+#    #+#             */
/*   Updated: 2016/07/21 18:18:06 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filter.h"
#include "libft.h"

unsigned int		filter_sepia(unsigned int c)
{
	int		in_rgb[3];
	int		out_rgb[3];

	in_rgb[0] = (int)(c >> 16 & 0xFF);
	in_rgb[1] = (int)(c >> 8 & 0xFF);
	in_rgb[2] = (int)(c >> 0 & 0xFF);
	out_rgb[0] = (int)(in_rgb[0] * 0.393)
		+ (int)(in_rgb[1] * 0.769) + (int)(in_rgb[2] * 0.189);
	out_rgb[1] = (int)(in_rgb[0] * 0.349)
		+ (int)(in_rgb[1] * 0.686) + (int)(in_rgb[2] * 0.168);
	out_rgb[2] = (int)(in_rgb[0] * 0.272)
		+ (int)(in_rgb[1] * 0.534) + (int)(in_rgb[2] * 0.131);
	out_rgb[0] = (out_rgb[0] > 255 ? 255 : ft_abs(out_rgb[0]));
	out_rgb[1] = (out_rgb[1] > 255 ? 255 : ft_abs(out_rgb[1]));
	out_rgb[2] = (out_rgb[2] > 255 ? 255 : ft_abs(out_rgb[2]));
	return (((unsigned int)((out_rgb[0] << 16) + (out_rgb[1] << 8) +
		out_rgb[2])));
}
