/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_setup_name.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 16:19:26 by snicolet          #+#    #+#             */
/*   Updated: 2016/07/13 17:02:59 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "libft.h"
#include <stdlib.h>

int			sda_setup_name(t_sda *e, t_obj *obj, char **av)
{
	(void)e;
	if (obj->name)
		free(obj->name);
	obj->name = ft_strunsplit((const char **)(unsigned long)av, ' ');
	return (1);
}
