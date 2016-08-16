/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/16 11:40:18 by dboudy            #+#    #+#             */
/*   Updated: 2016/08/16 11:40:21 by dboudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERFACE_H
# define INTERFACE_H

# include "rt.h"
# include <SDL2/SDL_ttf.h>
# include <SDL2/SDL.h>

void  init_ttf(void);
int   test_font(t_rt *rt);

#endif
