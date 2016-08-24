/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_export_obj.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/14 18:42:03 by alhote            #+#    #+#             */
/*   Updated: 2016/08/16 17:36:51 by alhote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "libft.h"
#include "mesh.h"

char	*sda_export_obj(t_obj *obj, t_sda_export *e)
{
	(void)e;
	if (!(obj->cfgbits & SDB_OBJ))
		return (NULL);
	return (((t_mesh*)(obj->content))->filepath);
}
