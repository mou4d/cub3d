/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousbaa <mbousbaa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 04:09:56 by wzakkabi          #+#    #+#             */
/*   Updated: 2023/12/05 01:31:23 by mbousbaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	info_player_helper(t_map *m)
{
	char	postion;

	postion = m->map_s[(int)m->plr->y
		/ m->size_wall_y_x][(int)m->plr->x / m->size_wall_y_x];
	m->plr->direction = 0;
	m->plr->move_up_down = 0;
	m->plr->move_right_or_left = 0;
	m->plr->radius = m->size_wall_y_x * 0.3;
	m->plr->speedmv = 10;
	m->plr->retactionsspeed = 5 * (M_PI / 180);
	m->plr->fovue_angle = 60 * (M_PI / 180);
	m->plr->num_arys = m->xwindows_width;
	if (postion == 'E')
		m->plr->retactionangle = 0;
	else if (postion == 'W')
		m->plr->retactionangle = M_PI;
	else if (postion == 'N')
		m->plr->retactionangle = (M_PI * 3) / 2;
	else if (postion == 'S')
		m->plr->retactionangle = M_PI / 2;
}

void	info_player(t_plr *p, t_map *m)
{
	int	x;
	int	y;

	y = -1;
	while (m->map_s[++y])
	{
		x = -1;
		while (m->map_s[y][++x])
		{
			if (m->map_s[y][x] == 'E' || m->map_s[y][x] == 'W'
					|| m->map_s[y][x] == 'N' || m->map_s[y][x] == 'S')
			{
				p->x = (x * m->size_wall_y_x) + m->size_wall_y_x / 2;
				p->y = (y * m->size_wall_y_x) + m->size_wall_y_x / 2;
			}
		}
	}
	info_player_helper(m);
}
