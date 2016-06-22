/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yolo_setting_ambiant.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qloubier <qloubier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/21 15:54:59 by qloubier          #+#    #+#             */
/*   Updated: 2016/06/21 16:36:35 by qloubier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "parser.h"
#include "render.h"
#include "libft.h"

int			yolo_setting_ambiant(char **parms, size_t size, t_rtcfg *rset)
{
	char	*line;

	if (size < 2)
		return (0);
	rset->ambiant_light = fmin(1.0, ft_atod(parms[1]) / MID_LIGHT_POWER);
	ft_putendl("PASSAGE AZAZ");
	line = ft_dtoa(rset->ambiant_light, 3);
	ft_printf("%s\n", line);
	free(line);
	return (1);
}
