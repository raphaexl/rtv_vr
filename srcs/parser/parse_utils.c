/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 19:34:56 by ebatchas          #+#    #+#             */
/*   Updated: 2019/09/21 21:20:40 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

char		*ft_parse_process_str(char *str, char c1, char c2)
{
	size_t		i;
	size_t		start;

	start = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c1)
			start = i;
		else if (str[i] == c2)
			return (ft_strsub(str, start + 1, i - start - 1));
		i++;
	}
	return (NULL);
}

t_rtsplit	ft_parse_process_split(char *str, char c1, char c2, char car)
{
	size_t		i;
	size_t		start;
	char		*tmp;
	t_rtsplit	split;

	split = (t_rtsplit){0, 0, NULL};
	start = 0;
	i = -1;
	tmp = NULL;
	while (str[++i])
	{
		if (str[i] == c1)
			start = i;
		else if (str[i] == c2)
		{
			split.max = i;
			tmp = ft_strsub(str, start + 1, i - start - 1);
			break ;
		}
	}
	split.min = start;
	split.tab = ft_strsplit(tmp, car);
	free(tmp);
	return (split);
}

int			ft_rtstrequal(char *s1, char *s2)
{
	if (ft_strstr(s2, s1))
		return (1);
	return (0);
}
