/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 11:42:16 by dboudy            #+#    #+#             */
/*   Updated: 2016/06/29 12:02:50 by dboudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

# define CHECKER	1
# define TILE_SIZE	3.0

typedef struct		s_text
{
	int				type;
	unsigned int	color1;
	unsigned int	color2;
}					t_text;

#endif
