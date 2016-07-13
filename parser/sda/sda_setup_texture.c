/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_setup_texture.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 18:02:53 by snicolet          #+#    #+#             */
/*   Updated: 2016/07/13 20:48:41 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "texture.h"
#include "libft.h"
#include <stdlib.h>

int					sda_setup_texture(t_sda *e, t_obj *obj, char **av)
{
	t_texture	*tex;
	char		*filepath;
	int			ret;

	ret = 0;
	filepath = ft_strunsplit((const char **)(unsigned long)av, ' ');
	if ((tex = texture_search(e->rt->textures, filepath)))
		ret = 1;
	else if ((tex = texture_create(&e->rt->textures, filepath)))
		ret = 1;
	else
	{
		ft_putendl_fd("error: failed to load texture", 2);
		free(filepath);
		ret = -1;
	}
	((t_sphere*)obj->content)->texture = tex;
	return (ret);
}
