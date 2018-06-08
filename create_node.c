/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 11:50:08 by ydeineha          #+#    #+#             */
/*   Updated: 2018/06/08 11:50:10 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room_lst	*create_node(char *line, int *type)
{
	t_room_lst	*node;
	int			i;

	i = 0;
	node = (t_room_lst *)malloc(sizeof(t_room_lst));
	if (!node)
		return (NULL);
	while (line[i] && line[i] != ' ')
		i++;
	node->name = ft_strsub(line, 0, i);
	node->pt.i = ft_atoi(ft_strchr(line, ' '));
	node->pt.j = ft_atoi(ft_strrchr(line, ' '));
	node->type = *type;
	node->next = NULL;
	*type = ROOM;
	return (node);
}

int		add_node_lst(t_room_lst **head, t_room_lst *node)
{
	t_room_lst	*tmp;
	int			check;

	tmp = NULL;
	check = 0;
	if (head && node)
	{
		tmp = *head;
		while (tmp->next)
		{
			if (ft_strequ(tmp->name, node->name))
			{
				if (tmp->pt == node->pt)
				{
					if (node->type == START || node->type == END)
					{
						if (tmp->type != START && tmp->type != END)
						{
							tmp->type = node->type;
							check++;
						}	
					}
				}
			}
		}
	}
}