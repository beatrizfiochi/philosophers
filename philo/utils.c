/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiochi- <bfiochi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:11:03 by bfiochi-          #+#    #+#             */
/*   Updated: 2025/08/07 16:24:49 by bfiochi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	print_error(const char *error_message)
{
	int	len;

	len = ft_strlen(error_message);
	return (write(2, error_message, len));
}

char	*str_error_return(const char *error_message)
{
	print_error(error_message);
	return (NULL);
}
