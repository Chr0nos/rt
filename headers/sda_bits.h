/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_bits.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/03 21:39:15 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/06 16:58:27 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SDA_BITS_H
# define SDA_BITS_H
# include "forms.h"

enum					e_sda_cfgbit
{
	SDB_COLOR = 1,
	SDB_POS = 1 << 1,
	SDB_ROT = 1 << 2,
	SDB_FOV = 1 << 3,
	SDB_SIZE = 1 << 4,
	SDB_AL = 1 << 5,
	SDB_INTEN = 1 << 6,
	SDB_REFRACT = 1 << 7,
	SDB_INCLUDE = 1 << 8,
	SDB_ANGLE = 1 << 9,
	SDB_COPY = 1 << 10,
	SDB_NAME = 1 << 11,
	SDB_TEXTURE = 1 << 12,
	SDB_REFLECT = 1 << 13,
	SDB_BACKGROUND = 1 << 14,
	SDB_NORMAL = 1 << 15,
	SDB_SKYBOX = 1 << 16,
	SDB_SDISABLE = 1 << 17,
	SDB_HEIGHTMAP = 1 << 18,
	SDB_TEX_PERLIN = 1 << 19 | SDB_TEXTURE,
	SDB_VERTEX0 = 1 << 20,
	SDB_VERTEX1 = 1 << 21,
	SDB_VERTEX2 = 1 << 22,
	SDB_VERTEX0_UV = 1 << 23,
	SDB_VERTEX1_UV = 1 << 24,
	SDB_VERTEX2_UV = 1 << 25,
	SDB_OBJ = 1 << 26,
	SDB_NOEXPORT = 1 << 27,
	SDB_LIMIT = 1 << 28,
	SDB_CSG = 1 << 29,
	SDB_SENABLE = 1 << 30
};

enum					e_sda_setting
{
	SDA_COLOR = VISIBLE | LIGHTTYPE | SETTING,
	SDA_POS = ~0,
	SDA_ROT = ~(CONE),
	SDA_AL = SETTING | CAMERA,
	SDA_FOV = CAMERA,
	SDA_SIZE = (SPHERE | CUBE | CONE | CYL | LIGHTTYPE | CONE_INF | SETTING),
	SDA_INTEN = LIGHTTYPE,
	SDA_REFRACT = VISIBLE,
	SDA_INCLUDE = EMPTY,
	SDA_ANGLE = CONE,
	SDA_COPY = EMPTY,
	SDA_NAME = ~0,
	SDA_TEXTURE = SPHERE | CUBE | PLAN | CONE | TRIANGLE | MESH,
	SDA_REFLECT = VISIBLE | SETTING,
	SDA_BACKGROUND = SETTING,
	SDA_SKYBOX = SETTING,
	SDA_SDISABLE = VISIBLE,
	SDA_HEIGHTMAP = PLAN,
	SDA_TEX_PERLIN = SDA_TEXTURE,
	SDA_VERTEX = TRIANGLE,
	SDA_OBJ = MESH,
	SDA_CSG = VISIBLE,
	SDA_SENABLE = VISIBLE
};

#endif
