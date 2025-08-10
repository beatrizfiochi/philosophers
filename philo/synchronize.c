/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchronize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiochi- <bfiochi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 12:01:27 by bfiochi-          #+#    #+#             */
/*   Updated: 2025/08/10 13:25:38 by bfiochi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_threads(t_table *table)
{
	while (!get_bool(&table->table_mutex, &table->threads_ready))
		;
}

bool	threads_running(t_mutex *mutex, long *threads, long philo_nbr)
{
	bool	ret;

	ret = false;
	handle_mutex(mutex, LOCK);
	if (*threads == philo_nbr)
		ret = true;
	handle_mutex(mutex, UNLOCK);
	return (ret);
}

void	increase_long(t_mutex *mutex, long *value)
{
	handle_mutex(mutex, LOCK);
	(*value)++;
	handle_mutex(mutex, UNLOCK);
}

void	de_synchronize(t_philo *philo)
{
	if (philo->table->number_of_philosophers % 2 == 0)
	{
		if (philo->id % 2 == 0)
			my_usleep(30000, philo->table);
		else
		{
			if (philo->id % 2 == 0)
				think(philo, true);
		}
	}
}
