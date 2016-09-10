/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interf_values.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/04 01:11:53 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/10 02:13:12 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "sda.h"
#include "objects.h"
#include "libft.h"

char	*interf_getid(t_obj *obj, t_sda_export *e)
{
	(void)e;
	return (ft_itoa((int)obj->id));
}

char	*interf_getname(t_obj *obj, t_sda_export *e)
{
	(void)e;
	if (!obj->name)
		return (NULL);
	return (ft_strdup(obj->name));
}

char	*interf_gettype(t_obj *obj, t_sda_export *e)
{
	(void)e;
	return (search_str_type(obj->type));
}

char	*interf_getalpha(t_obj *obj, t_sda_export *e)
{
	unsigned int		alpha;

	if (!(obj->type & SDA_COLOR))
		return (NULL);
	(void)e;
	alpha = (((t_cube*)obj->content)->color & 0xff000000) >> 24;
	return (ft_itoa((int)alpha));
}

int		interf_setid(t_sda *e, t_obj *obj, char **av)
{
	t_obj		*obj_id;

	(void)obj;
	obj_id = rt_obj_byid(e->rt->root, (unsigned int)ft_atoi(av[0]));
	if (!obj_id)
		return (-1);
	e->rt->interf.obj_selected = obj_id;
	return (1);
}
