/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_default_shaders.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/24 17:56:26 by snicolet          #+#    #+#             */
/*   Updated: 2016/08/24 17:59:22 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"

void	sda_default_shaders(t_rt *rt, t_obj *obj)
{
	if ((!rt->tree.lnum) && (obj->shader))
	{
		sda_setup_sdisable_real(obj->shader->shader, (void*)&rt_light_pow);
		sda_setup_sdisable_real(obj->shader->shader, (void*)&shader_shadow);
		sda_setup_sdisable_real(obj->shader->shader, (void*)&rt_specular_pow);
		sda_setup_sdisable_real(obj->shader->shader, (void*)&shader_normalmap);
	}
}
