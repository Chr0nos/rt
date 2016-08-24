/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yolo_setting_ambiant.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qloubier <qloubier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/21 15:54:59 by qloubier          #+#    #+#             */
/*   Updated: 2016/08/24 18:48:20 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "parser.h"
#include "render.h"
#include "libft.h"

int			yolo_setting_ambiant(char **parms, size_t size, t_rtcfg *rset)
{
	unsigned char		c;

	if (size < 2)
		return (0);
	c = (unsigned char)((float)0xff *
		geo_clamp((float)ft_atod(parms[1]), 0.0f, 1.0f));
	rset->ambiant_light = (unsigned int)(c | (c << 8) | (c << 16));
	return (1);
}
