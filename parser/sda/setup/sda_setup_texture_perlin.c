/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_setup_texture_perlin.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/29 14:33:16 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/09 04:01:40 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "texture.h"
#include "libft.h"
#include "rt.h"

int		sda_setup_texture_perlin(t_sda *e, t_obj *obj, char **av)
{
	rt_obj_set_texture(obj, texture_perlin(e->rt->textures,
		(t_v2i){ft_atoi(av[0]), ft_atoi(av[1])},
		ft_strunsplit((const char **)(unsigned long)av, ' ')));
	return (1);
}
