/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_export_refract.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/16 00:04:03 by snicolet          #+#    #+#             */
/*   Updated: 2016/07/17 18:44:20 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "libft.h"

char	*sda_export_refract(t_obj *obj, t_sda_export *e)
{
	(void)e;
	if (!(obj->cfgbits & SDB_REFRACT))
		return (NULL);
	return (ft_dtoa(obj->refractive_index, 6));
}
