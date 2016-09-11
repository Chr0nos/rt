/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_export_angle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/16 00:44:09 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/03 21:57:57 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "libft.h"
#include "objects.h"

char	*sda_export_angle(t_obj *obj, t_sda_export *e)
{
	(void)e;
	return (ft_dtoa(rad2deg(((t_cone*)obj->content)->angle.x), 6));
}
