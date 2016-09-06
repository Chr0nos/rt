/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_setup_senable.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/06 16:41:38 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/06 16:50:10 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "objects.h"
#include "shaders.h"

int			sda_setup_senable(t_sda *e, t_obj *obj, char **av)
{
	void	*shader;

	(void)e;
	if (!ft_strcmp(av[0], "damier"))
	{
		shader = sda_setup_getshader_addr(obj->shader->shader,
			(void*)(unsigned long)&shader_damier);
		if (!shader)
		{
			ft_putstr_fd("error: unable to found shader damier\n", 2);
			return (-2);
		}
		((t_shader*)shader)->enabled = 1;
		return (1);
	}
	return (-1);
}
