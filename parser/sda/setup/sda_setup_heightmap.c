/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_setup_heightmap.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/26 22:30:54 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/03 21:53:30 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "texture.h"
#include "libft.h"
#include "objects.h"

int			sda_setup_heightmap(t_sda *e, t_obj *obj, char **av)
{
	t_texture	*tex;
	char		*filepath;
	t_plan		*plan;

	plan = obj->content;
	if (!(filepath = ft_strunsplit((const char **)(unsigned long)av, ' ')))
		return (-2);
	if ((tex = texture_search(*e->rt->textures, filepath)))
		free(filepath);
	else if (e->rt->settings.fake_texture_load)
	{
		tex = sda_setup_texture_fake(filepath, e->rt->textures);
		plan->heightmap = tex;
		return (1);
	}
	else if ((tex = texture_create(e->rt->textures, filepath)))
		;
	else
	{
		ft_putendl_fd("error: failed to load texture", 2);
		free(filepath);
		return (-1);
	}
	plan->heightmap = tex;
	return (1);
}
