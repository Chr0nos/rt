/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interf_change_obj.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <dboudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/19 15:01:36 by dboudy            #+#    #+#             */
/*   Updated: 2016/09/01 17:08:03 by dboudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "sda.h"
#include "libft.h"

/*
** set la texture filepath sur current en utilisant le parseur de sda
** retours: -1 en cas d erreur
** 0 si la texture existe deja ( n a rien fait en dehors de set a l objet)
** 1 = ok ca a bien load et set
*/

static void	interf_settexture(char *filepath, t_rt *rt, t_obj *current)
{
	t_sda	s;
	char	**av;
	int		ret;

	s = (t_sda){0, rt, rt->root, current, 0, 0};
	if (!(av = ft_strsplit(filepath, ' ')))
		return ;
	ret = sda_setup_texture(&s, current, av);
	ft_freesplit(av);
	if (ret != 1)
	{
		current->cfgbits ^= SDB_TEXTURE;
		free(filepath);
		filepath = ft_strdup("no texture");
	}
}

static void	set_color(t_obj *obj, char *champs[NB_CHAMPS][LARGER_SIZE])
{
	unsigned char	vals[4];

	vals[3] = (unsigned char)(ft_atoi(*champs[I_ALPHA]));
	vals[2] = (unsigned char)(ft_atoi(*champs[I_COL_R]));
	vals[1] = (unsigned char)(ft_atoi(*champs[I_COL_G]));
	vals[0] = (unsigned char)(ft_atoi(*champs[I_COL_B]));
	((t_cube*)obj->content)->color = *(unsigned int*)(unsigned long long)vals;
}

void		change_all_data_obj(t_rt *rt, char *champs[NB_CHAMPS][LARGER_SIZE])
{
	t_obj	*obj;

	obj = rt->interf->obj_selected;
	obj->id = (t_uint)ft_atoi(*champs[I_ID]);
	obj->type = rt_gettype(*champs[I_TYPE]);
	if (obj->cfgbits & SDB_NAME)
	{
		free(obj->name);
		if (!(obj->name = ft_strdup(*champs[I_NAME])))
			obj->cfgbits ^= SDB_NAME;
	}
	if (obj->cfgbits & SDB_TEXTURE)
		interf_settexture(*champs[I_TEXT], rt, obj);
	obj->trans.w = (t_v4d){ ft_atod(*champs[I_POSX]),
		ft_atod(*champs[I_POSY]), ft_atod(*champs[I_POSZ]), 0.0};
	rt_obj_rotate(obj, (t_v4d){ ft_atod(*champs[I_DIRX]),
			ft_atod(*champs[I_DIRY]), ft_atod(*champs[I_DIRZ]), 0.0});
	set_color(obj, champs);
	((t_cube*)obj->content)->reflect = (unsigned char)ft_atoi(*champs[I_REFL]);
	obj->refractive_index = ft_atod(*champs[I_REFR]);
	obj->refractive_index = ft_atod(*champs[I_REFR]);
	((t_cube*)obj->content)->size = (float)ft_atod(*champs[I_SIZE]);
	fill_champs_obj(obj, champs);
}
