/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousbaa <mbousbaa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:09:18 by mbousbaa          #+#    #+#             */
/*   Updated: 2023/09/25 18:54:44 by mbousbaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_top_border(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->map_s[i] && ft_isalpha(map->map_s[i][0]))
		i++;
	if (!map->map_s[i])
		return (0);
	j = 0;
	while (map->map_s[i][j]
		&& (map->map_s[i][j] == '\t' || map->map_s[i][j] == ' '))
		j++;
	while (map->map_s[i][j]
		&& (map->map_s[i][j] == '\t' || map->map_s[i][j] == ' '
			|| map->map_s[i][j] == '1'))
		j++;
	if (j != (int) ft_strlen(map->map_s[i]))
		return (0);
	return (1);
}

int	check_bottom_border(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->map_s[i])
		i++;
	i = i - 1;
	if (!map->map_s[i])
		return (0);
	j = 0;
	while (map->map_s[i][j]
		&& (map->map_s[i][j] == '\t' || map->map_s[i][j] == ' '))
		j++;
	while (map->map_s[i][j]
		&& (map->map_s[i][j] == '\t' || map->map_s[i][j] == ' '
			|| map->map_s[i][j] == '1'))
		j++;
	if (j != (int) ft_strlen(map->map_s[i]))
		return (0);
	return (1);
}

int check_side_borders (t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->map_s[i] && ft_isalpha(map->map_s[i][0]))
		i++;
	while (map->map_s[i])
	{
		j = 0;
		while (map->map_s[i][j]
			&& (map->map_s[i][j] == '\t' || map->map_s[i][j] == ' '))
			j++;
		if (map->map_s[i][j] != '1')
			return (0);
		int len = ft_strlen(map->map_s[i]) - 1;
		if (map->map_s[i][len] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	check_player_exist(t_map *map, char **str)
{
	int	i;
	int	j;
	// int	map_start;

	i = -1;
	while (str[++i])
		if (!ft_isalpha(str[i][0]))
			break ;
	// map_start = i;
	while (str[i])
	{
		j = -1;
		while (str[i][++j])
		{
			if (ft_strchr("NSEW", str[i][j]))
			{
				if (map->init_player_x != -1 && map->init_player_y != -1)
					return (printf("Missing/duplicated map element\n"));
				map->init_player_x = j;
				map->init_player_y = i;
			}
		}
		i++;
	}
	if (map->init_player_x == -1)
		return (printf("Missing/duplicated map element\n"));
	return (1);
}

int	check_map_elements(t_map *map, char **str, char *valid_elements)
{
	int	i;
	int	j;
	int	ret;

	ret = 0;
	i = -1;
	while (str[++i])
		if (!ft_isalpha(str[i][0]))
			break ;
	while (str[i])
	{
		j = -1;
		while (str[i][++j])
			if (!ft_strchr(valid_elements, str[i][j]))
				return (0);
		i++;
	}
	ret = check_player_exist(map, map->map_s);
	return (ret);
}
