/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_export_obj.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/14 18:42:03 by alhote            #+#    #+#             */
/*   Updated: 2016/08/14 18:47:37 by alhote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "libft.h"

char	*sda_export_obj(t_obj *obj, t_sda_export *e)
{
	(void)e;
	if (!(obj->cfgbits & SDB_OBJ))
		return (NULL);
	return ("3D file, Wavefront OBJ");
}
