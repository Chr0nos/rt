/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yolo_parse_settings.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qloubier <qloubier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/19 17:04:48 by qloubier          #+#    #+#             */
/*   Updated: 2016/06/19 17:59:55 by qloubier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

int			yolo_parse_settings(char *line, t_rtcfg *rset)
{
	if (ft_strncmp(line, "SETTING", 7))
		return (0);
	rset->ambiant_light = 10.0;
	return (1);
}
