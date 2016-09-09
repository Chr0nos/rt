/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_export_background.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/09 03:25:21 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/09 03:28:19 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "objects.h"

char	*sda_export_background(t_obj *obj, t_sda_export *e)
{
	char	*str;

	(void)e;
	if (!(obj->cfgbits & SDB_BACKGROUND))
		return (NULL);
	if (!(str = malloc(14)))
		return (NULL);
	sda_export_color_raw(((t_setting*)obj->content)->bgcolor, str);
	return (str);
}
