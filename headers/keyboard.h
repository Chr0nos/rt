/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/04 22:26:25 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/05 03:41:03 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYBOARD_H
# define KEYBOARD_H

enum	e_keyboard
{
	LEFT = 1,
	RIGHT = 1 << 1,
	UP = 1 << 2,
	DOWN = 1 << 3,
	ZOOMIN = 1 << 4,
	ZOOMOUT = 1 << 5,
	QUIT = 1 << 6,
	ROTATE_LEFT = 1 << 7,
	ROTATE_RIGHT = 1 << 8,
	ROTATE_UP = 1 << 9,
	ROTATE_DOWN = 1 << 10,
	FORCE_DISPLAY = 1 << 11
};

typedef struct	s_kb_cmp
{
	int			key;
	int			bit;
}				t_kbcmp;

#endif
