/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seemil <seemil@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 21:52:00 by hkizrak-          #+#    #+#             */
/*   Updated: 2024/12/14 22:02:25 by seemil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	if (!needle[0] && len == 0)
		return ((char *)haystack);
	if (!haystack[0] && !needle[0])
		return ((char *)haystack);
	if ((!haystack && !needle) || len == 0)
		return (NULL);
	i = 0;
	while (haystack[i] && i < len - ft_strlen(needle) + 1)
	{
		if (ft_strncmp(&haystack[i], needle, ft_strlen(needle)) == 0)
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}
