/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seemil <seemil@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 21:45:56 by hkizrak-          #+#    #+#             */
/*   Updated: 2024/12/14 21:56:12 by seemil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_err	perr(const char *func, const char *msg)
{
	write(2, "Error\n", 6);
	if (msg)
	{
		write(2, "Message: ", 9);
		if (func)
		{
			write(2, func, ft_strlen(func));
			write(2, ": ", 2);
		}
		write(2, msg, ft_strlen(msg));
		write(2, "\n", 1);
	}
	return (ERR);
}
