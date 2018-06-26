/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 14:33:40 by ydeineha          #+#    #+#             */
/*   Updated: 2018/06/26 14:33:43 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		check_if_int(char *str)
{
	char	*s;
	int		len;
	int		i;

	i = -1;
	s = "2147483647";
	len = ft_strlen(str);
	if (len < 10 || len > 10)
	{
		ft_strdel(&str);
		return (len < 10 ? 1 : 0);
	}
	else if (len == 10)
	{
		while (str[++i])
		{
			if (str[i] < s[i])
				return (1);
			if (str[i] > s[i])
				return (0);
		}
	}
	ft_strdel(&str);
	return (1);
}

int		check_room_str(char *line)
{
	int i;
	int num;
	int start;

	i = -1;
	num = 0;
	while (line[++i])
	{
		if (i == 0 && (line[i] == '#' || line[i] == 'L'))
			return (0);
		else if (line[i] == ' ' && !ft_isdigit(line[i + 1]))
			return (0);
		if (ft_isdigit(line[i]) && i > 0 && line[i - 1] == ' ')
		{
			num++;
			start = i;
			while (line[++i] && line[i] != ' ')
				if (!ft_isdigit(line[i]))
					return (0);
			if (!check_if_int(ft_strsub(line, start, i - start)))
				return (0);
			i--;
		}
	}
	return (num == 2 ? 1 : 0);
}

int		room_valid(char *line, t_lem_in *game, int *type)
{
	t_room_lst	*node;
	int			ret;

	node = NULL;
	ret = check_room_str(line);
	if (*type == LINK || !ret || !game->ants)
	{
		game->error = *type == LINK ? 12 : game->error;
		game->error = !ret ? 0 : game->error;
		game->error = !game->ants ? 5 : game->error;
		return (0);
	}
	if (!game->node)
		game->node = create_node(line, type);
	else
	{
		node = create_node(line, type);
		if (!add_node_lst(&(game->node), node, game))
		{
			ft_strdel(&(node->name));
			free(node);
			return (0);
		}
	}
	game->room_num++;
	return (1);
}
