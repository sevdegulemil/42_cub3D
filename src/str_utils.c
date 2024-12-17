/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seemil <seemil@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 21:47:56 by hkizrak-          #+#    #+#             */
/*   Updated: 2024/12/15 17:58:37 by seemil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	strevery(int (*func)(int c), const char *str)
{
	int	i;

	if (!func || !str)
		return (perr(__func__, "'func' or 'str' cannot be null"), 0);
	i = 0;
	while (str[i])
	{
		if (!func(str[i]))
			return (0);
		i++;
	}
	return (1);
}

bool	is_empty_line(char *line)
{
	int	i;

	if (!line)
	{
		printf("Error\nis_empty_line: line is NULL\n");
		exit(0);
	}
	i = 0;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t' || line[i] == '\v'
			|| line[i] == '\f' || line[i] == '\r' || line[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim_a(const char *s1, const char *set)
{
	size_t	start;
	size_t	end;
	char	*trimmed_str;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	trimmed_str = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!trimmed_str)
		return (NULL);
	ft_strlcpy(trimmed_str, s1 + start, end - start + 1);
	return (trimmed_str);
}
