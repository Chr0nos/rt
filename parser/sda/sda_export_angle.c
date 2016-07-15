/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_export_angle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/16 00:44:09 by snicolet          #+#    #+#             */
/*   Updated: 2016/07/16 00:46:54 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "libft.h"

char	*sda_export_angle(t_obj *obj)
{
	return (ft_dtoa(rad2deg(((t_cone*)obj->content)->angle.x), 6));
}
