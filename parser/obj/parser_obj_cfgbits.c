/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_obj_cfgbits.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/25 21:30:30 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/03 22:00:25 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "objects.h"
#include "mesh.h"

void				parse_obj_setcfgbits(t_obj *t, const t_sda_obj *s,
	t_triangle *c)
{
	t->cfgbits |= (SDB_COLOR | SDB_VERTEX0 | SDB_VERTEX1 | SDB_VERTEX2 |
		SDB_REFLECT);
	if ((c->texture = s->mesh->texture))
		t->cfgbits |= SDB_TEXTURE;
	if ((c->normal = s->mesh->normal))
		t->cfgbits |= SDB_NORMAL;
	c->color = s->mesh->color;
	c->reflect = s->mesh->reflect;
}
