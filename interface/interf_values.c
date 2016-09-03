/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interf_values.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/04 01:11:53 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/04 01:30:33 by snicolet         ###   ########.fr       */
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
