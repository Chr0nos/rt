/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_export_refract.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/16 00:04:03 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/05 16:46:35 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "libft.h"
#include "objects.h"

char	*sda_export_refract(t_obj *obj, t_sda_export *e)
{
	char	*str;

	(void)e;
	if (!(obj->cfgbits & SDB_REFRACT))
		return (NULL);
	if (!(str = ft_dtoa(obj->refractive_index, 6)))
		return (NULL);
	return (sda_double_short(str));
}
