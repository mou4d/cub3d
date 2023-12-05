/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_mlx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousbaa <mbousbaa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 04:18:10 by wzakkabi          #+#    #+#             */
/*   Updated: 2023/12/05 01:25:08 by mbousbaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

bool	movestp_not_into_wall(t_map *map, double movestp, double M)
{
	char	test;
	int		x;
	int		y;

	if (movestp == 0)
		return (false);
	x = ((map->plr->x + cos(map->plr->retactionangle + M) * movestp)
			/ map->size_wall_y_x);
	y = ((map->plr->y + sin(map->plr->retactionangle + M) * movestp)
			/ map->size_wall_y_x);
	if (x < 0 || y < 0 || y > map->height_map || x > map->width_map[y])
		return (false);
	test = map->map_s[y][x];
	if (test == '1')
		return (false);
	if (map->map_s[y][(int)(map->plr->x / map->size_wall_y_x)] == '1')
		return (false);
	if (map->map_s[(int)(map->plr->y / map->size_wall_y_x)][x] == '1')
		return (false);
	return (true);
}

void	helper_update_key(t_map *map)
{
	double	movestp;

	map->plr->retactionangle += map->plr->direction * map->plr->retactionsspeed;
	movestp = map->plr->move_up_down * map->plr->speedmv;
	if (movestp_not_into_wall(map, movestp, 0) == true)
	{
		map->plr->x += cos(map->plr->retactionangle) * movestp;
		map->plr->y += sin(map->plr->retactionangle) * movestp;
		movestp = 0;
	}
	movestp = map->plr->move_right_or_left * map->plr->speedmv;
	if (movestp_not_into_wall(map, movestp, M_PI_2) == true)
	{
		map->plr->x += cos(map->plr->retactionangle + M_PI_2) * movestp;
		map->plr->y += sin(map->plr->retactionangle + M_PI_2) * movestp;
		movestp = 0;
	}
}

void	mouse_handler(t_map *map, int *x, int *oldx)
{
	int	y;

	*oldx = *x;
	if (*x >= 0 && *x <= map->xwindows_width)
		mlx_get_mouse_pos(map->mlx, x, &y);
	else
	{
		mlx_set_mouse_pos(map->mlx, map->xwindows_width / 2,
			map->ywindows_height / 2);
		mlx_get_mouse_pos(map->mlx, x, &y);
		oldx = x;
	}
}

void	update_key(void *tmp)
{
	t_map		*map;
	static int	x = 0;
	int			oldx;

	map = (t_map *)tmp;
	map->plr->move_up_down = 0; 
	map->plr->move_right_or_left = 0;
	map->plr->direction = 0;
	mouse_handler(map, &x, &oldx);
	if (mlx_is_key_down(map->mlx, MLX_KEY_W) == true)
		map->plr->move_up_down = 1;
	else if (mlx_is_key_down(map->mlx, MLX_KEY_S) == true)
		map->plr->move_up_down = -1;
	if (mlx_is_key_down(map->mlx, MLX_KEY_D) == true)
		map->plr->move_right_or_left = 1;
	else if (mlx_is_key_down(map->mlx, MLX_KEY_A) == true)
		map->plr->move_right_or_left = -1;
	if (mlx_is_key_down(map->mlx, MLX_KEY_LEFT) == true || x < oldx)
		map->plr->direction = -1;
	else if (mlx_is_key_down(map->mlx, MLX_KEY_RIGHT) == true || x > oldx)
		map->plr->direction = 1;
	else if (mlx_is_key_down(map->mlx, MLX_KEY_ESCAPE) == true)
		(free_all(map), exit(0));
	helper_update_key(map);
	init_mlx(map);
}
