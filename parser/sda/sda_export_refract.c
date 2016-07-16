/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_export_refract.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/16 00:04:03 by snicolet          #+#    #+#             */
/*   Updated: 2016/07/16 00:07:07 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "libft.h"

char	*sda_export_refract(t_obj *obj)
{
	if (!(obj->cfgbits & SDB_REFRACT))
		return (NULL);
	return (ft_dtoa(obj->refractive_index, 6));
}
