/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 23:48:00 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/27 23:16:18 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		main(void)
{
	t_obj	*root;
	t_obj	*cube;

	root = rt_obj_makeroot();
	cube = rt_factory_alloc(CUBE, root);
	rt_factory_alloc(PLAN, cube);
	rt_factory_alloc(CUBE, cube);
	rt_factory_alloc(CUBE, cube);
	rt_factory_alloc(SPHERE, root);
	rt_debug(root, 0);
	rt_obj_free(cube, 0);
	rt_debug(root, 0);
	rt_obj_free(root, 0);
	return (0);
}
