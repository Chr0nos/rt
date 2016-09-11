/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_bits.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/03 21:39:15 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/11 19:30:46 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SDA_BITS_H
# define SDA_BITS_H
# include "forms.h"

# define SDB_COLOR			1u
# define SDB_POS			(1u << 1)
# define SDB_ROT			(1u << 2)
# define SDB_FOV			(1u << 3)
# define SDB_SIZE			(1u << 4)
# define SDB_AL				(1u << 5)
# define SDB_INTEN			(1u << 6)
# define SDB_REFRACT		(1u << 7)
# define SDB_INCLUDE		(1u << 8)
# define SDB_ANGLE			(1u << 9)
# define SDB_COPY			(1u << 10)
# define SDB_NAME			(1u << 11)
# define SDB_TEXTURE		(1u << 12)
# define SDB_REFLECT		(1u << 13)
# define SDB_BACKGROUND		(1u << 14)
# define SDB_NORMAL			(1u << 15)
# define SDB_SKYBOX			(1u << 16)
# define SDB_SDISABLE		(1u << 17)
# define SDB_HEIGHTMAP		(1u << 18)
# define SDB_TEX_PERLIN		((1u << 19) | SDB_TEXTURE)
# define SDB_VERTEX0		(1u << 20)
# define SDB_VERTEX1		(1u << 21)
# define SDB_VERTEX2		(1u << 22)
# define SDB_VERTEX0_UV		(1u << 23)
# define SDB_VERTEX1_UV		(1u << 24)
# define SDB_VERTEX2_UV		(1u << 25)
# define SDB_OBJ			(1u << 26)
# define SDB_NOEXPORT		(1u << 27)
# define SDB_LIMIT			(1u << 28)
# define SDB_CSG			(1u << 29)
# define SDB_SENABLE		(1u << 30)
# define SDB_INTERFACE_EDIT	(1u << 31)

enum					e_sda_setting
{
	SDA_COLOR = VISIBLE | LIGHTTYPE | SETTING,
	SDA_POS = ~0,
	SDA_ROT = ~(CONE),
	SDA_AL = SETTING | CAMERA,
	SDA_FOV = CAMERA,
	SDA_SIZE = (SPHERE | CUBE | CONE | CYL | CONE_INF | SETTING),
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
