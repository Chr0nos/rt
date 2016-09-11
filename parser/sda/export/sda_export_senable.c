/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_export_senable.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/09 06:45:23 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/09 06:49:17 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "objects.h"

char	*sda_export_senable(t_obj *obj, t_sda_export *e)
{
	(void)e;
	if (obj->cfgbits & SDB_SENABLE)
		return (ft_strdup("damier"));
	return (NULL);
}
