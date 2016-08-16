/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_setup_obj.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/14 18:37:06 by alhote            #+#    #+#             */
/*   Updated: 2016/08/16 12:38:34 by alhote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "mesh.h"
#include "libft.h"
#include <stdlib.h>

int			sda_setup_obj(t_sda *e, t_obj *obj, char **av)
{
	(void)e;
	add_mesh_from_obj(obj, av[0]);
	return (1);
}
