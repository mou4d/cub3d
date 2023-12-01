/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_mlx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzakkabi <wzakkabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 04:18:10 by wzakkabi          #+#    #+#             */
/*   Updated: 2023/12/01 05:48:53 by wzakkabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

bool	movestp_not_into_wall(t_map *map, double movestp , double M)
{
	char test;
	int x;
	int y;
	x = ((map->plr->x + cos(map->plr->retactionangle + M) * movestp) / map->size_wall_y_x);
	y = ((map->plr->y + sin(map->plr->retactionangle + M) * movestp) / map->size_wall_y_x);
	if(x < 0 || y < 0 || y > map->height_map || x > map->width_map[y])
		return false;
	test = map->map_s[y][x];
	if(test == '1')
		return false;
	if(test == '1')
		return false;
	return true;
}



void update_key(void *tmp)
{
    double movestp;
    t_map *map = (t_map *)tmp;

  	map->plr->move_up_down = 0; 
    map->plr->move_right_or_left = 0;
    map->plr->direction = 0;
    if (mlx_is_key_down(map->mlx, MLX_KEY_W) == true)
        map->plr->move_up_down = 1;
    else if (mlx_is_key_down(map->mlx, MLX_KEY_S) == true)
        map->plr->move_up_down = -1;
    if (mlx_is_key_down(map->mlx, MLX_KEY_D) == true)
        map->plr->move_right_or_left = 1; // Move right
    else if (mlx_is_key_down(map->mlx, MLX_KEY_A) == true)
        map->plr->move_right_or_left = -1; // Move left
    if (mlx_is_key_down(map->mlx, MLX_KEY_LEFT) == true)
        map->plr->direction = -1;
    else if (mlx_is_key_down(map->mlx, MLX_KEY_RIGHT) == true)
        map->plr->direction = 1;
    else if (mlx_is_key_down(map->mlx, MLX_KEY_ESCAPE) == true)
        mlx_close_window(map->mlx);
      
    map->plr->retactionangle += map->plr->direction * map->plr->retactionsSpeed;
    movestp = map->plr->move_up_down * map->plr->speedmv;
    if (movestp_not_into_wall(map, movestp, 0) == true)
    {
        map->plr->x += cos(map->plr->retactionangle) * movestp;
        map->plr->y += sin(map->plr->retactionangle) * movestp;
		movestp = 0;
    }
    movestp  = map->plr->move_right_or_left * map->plr->speedmv;
    if (movestp_not_into_wall(map, movestp, M_PI_2) == true)
    {
        map->plr->x += cos(map->plr->retactionangle + M_PI_2) * movestp;
        map->plr->y += sin(map->plr->retactionangle + M_PI_2) * movestp;
	}
    init_mlx(map);
}