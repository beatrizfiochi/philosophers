/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiochi- <bfiochi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 17:32:05 by bfiochi-          #+#    #+#             */
/*   Updated: 2025/08/10 13:04:15 by bfiochi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_philo_status(t_philo_status status, t_philo *philo)
{
	long	elapsed;

	if (philo->full)
		return ;
	elapsed = (get_time(MILLESECOND) - philo->table->start_of_dinner);
	handle_mutex(&philo->table->write_mutex, LOCK);
	if ((status == TAKE_RIGTH_FORK || status == TAKE_LEFT_FORK)
		&& (!simulation_finished(philo->table)))
		printf("%-6ld %d has taken a fork\n", elapsed, philo->id);
	else if (status == EATING && !simulation_finished(philo->table))
		printf("%-6ld %d is eating\n", elapsed, philo->id);
	else if (status == SLEEPING && !simulation_finished(philo->table))
		printf("%-6ld %d is sleeping\n", elapsed, philo->id);
	else if (status == THINKING && !simulation_finished(philo->table))
		printf("%-6ld %d is thinking\n", elapsed, philo->id);
	else if (status == DIED)
		printf("%-6ld %d died\n", elapsed, philo->id);
	handle_mutex(&philo->table->write_mutex, UNLOCK);
}
