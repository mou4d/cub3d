/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousbaa <mbousbaa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 20:57:09 by mbousbaa          #+#    #+#             */
/*   Updated: 2023/09/10 21:42:00 by mbousbaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_type_id(char	*type_id, int *count)
{
	int		ret;
	char	**tmp;

	ret = *count;
	tmp = ft_split(type_id, ' ');
	if (ft_strncmp(tmp[0], "NO", 2) == 0
		|| ft_strncmp(tmp[0], "SO", 2) == 0
		||ft_strncmp(tmp[0], "WE", 2) == 0
		|| ft_strncmp(tmp[0], "EA", 2) == 0)
	{
		if (tmp[0][2] == '\0')
			ret += 1;
		else
			ret = 0;
	}
	else if ((tmp[0][0] == 'F' && tmp[0][1] == '\0')
			|| (tmp[0][0] == 'C' && tmp[0][1] == '\0'))
		ret += 1;
	else
		ret = 0;
	free(tmp);
	return(ret);
}

void	init_type_ids(t_map *map, char *type)
{
	char	**tmp;

	tmp = ft_split(type, ' ');
	if (tmp == NULL)
		return ;
	if (tmp[0][0] == 'F' && tmp[0][1] == '\0')
		map->F = ft_strdup(tmp[1]);
	else if (tmp[0][0] == 'C' && tmp[0][1] == '\0')
		map->C = ft_strdup(tmp[1]);
	else if (ft_strncmp(tmp[0], "NO", 2) == 0)
		map->NO = ft_strdup(tmp[1]);
	else if (ft_strncmp(tmp[0], "SO", 2) == 0)
		map->SO = ft_strdup(tmp[1]);
	else if (ft_strncmp(tmp[0], "WE", 2) == 0)
		map->WE = ft_strdup(tmp[1]);
	else if (ft_strncmp(tmp[0], "EA", 2) == 0)
		map->EA = ft_strdup(tmp[1]);
	free(tmp);
}

int	process_type_ids(t_map *map)
{
	int	i;
	int	count;
	int	ret;

	i = 0;
	count = 0;
	while (map->map_s[i] && i <= 6)
	{
		if (!ft_isalpha(map->map_s[i][0]) && count <= 6)
			break ;
		// printf("processing : \"%s\"\n", map->map_s[i]);
		count = parse_type_id(map->map_s[i], &count);
		if (count == 0)
			break ;
		init_type_ids(map, map->map_s[i]);
		i++;
	}
	printf("count=%d\n", count);
	if (count != 6)
		return(printf("Error\n"));
	return (1);
}
