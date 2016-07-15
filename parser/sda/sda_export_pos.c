/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_export_pos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/15 14:24:34 by snicolet          #+#    #+#             */
/*   Updated: 2016/07/15 16:52:26 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "libft.h"

void	sda_export_pos(t_obj *obj)
{
	char	*x;
	char	*y;
	char	*z;

	x = ft_dtoa(obj->trans.w.x, 6);
	y = ft_dtoa(obj->trans.w.y, 6);
	z = ft_dtoa(obj->trans.w.z, 6);
	ft_printf("%s %s %s\n", x, y, z);
	ft_mfree(3, x, y, z);
}
