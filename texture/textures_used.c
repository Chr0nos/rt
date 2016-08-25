/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_used.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/12 11:16:11 by snicolet          #+#    #+#             */
/*   Updated: 2016/08/25 06:20:53 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "libft.h"
#include "sda.h"
#include "objects.h"

static int		textures_used_foreach(t_obj *obj, int mode, void *userdata)
{
	t_texture	*tex;

	(void)mode;
	if ((tex = rt_obj_get_texture(obj)))
		ft_lstadd((t_list**)userdata, ft_lstnewlink(tex, 0));
	if ((tex = rt_obj_get_normal(obj)))
		ft_lstadd((t_list**)userdata, ft_lstnewlink(tex, 0));
	if ((obj->type == SETTING) && (obj->cfgbits & SDB_SKYBOX))
		ft_lstadd((t_list **)userdata,
			ft_lstnewlink(((t_setting*)obj->content)->skybox, 0));
	return (OK);
}

/*
** this function return a t_list with every pointer to t_texture used by
** the node "root"
*/

t_list			*textures_used(t_obj *root)
{
	t_list	*used;

	used = NULL;
	rt_node_foreach(root, PREFIX, &textures_used_foreach, &used);
	return (used);
}

static void		textures_used_display_foreach(void *content)
{
	t_texture	*tex;

	tex = content;
	if (tex->filepath)
		ft_printf("#texture in use: %s\n", tex->filepath);
}

void			textures_used_display(t_obj *root)
{
	t_list	*lst;

	lst = textures_used(root);
	ft_lstforeach(lst, &textures_used_display_foreach);
	ft_lstdel(&lst, NULL);
}
