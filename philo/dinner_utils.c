/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiochi- <bfiochi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 18:06:09 by bfiochi-          #+#    #+#             */
/*   Updated: 2025/08/10 15:22:59 by bfiochi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_fork_is_taken(t_philo *philo, bool status)
{
	philo->left_fork->is_taken = status;
	philo->right_fork->is_taken = status;
}

static void	acess_forks(t_philo *philo)
{
	set_fork_is_taken(philo, true);
	handle_mutex(&philo->table->waiter_mutex, UNLOCK);
	handle_mutex(&philo->left_fork->fork, LOCK);
	write_philo_status(TAKE_LEFT_FORK, philo);
	handle_mutex(&philo->right_fork->fork, LOCK);
	write_philo_status(TAKE_RIGTH_FORK, philo);
}

static bool	neighbor_has_priority(t_philo *philo, t_philo *philo_neighbor)
{
	long	philo_last_meal_time;
	long	philo_neighbor_last_meal_time;

	philo_last_meal_time = philo->last_meal_time;
	philo_neighbor_last_meal_time = philo_neighbor->last_meal_time;
	if (philo_neighbor_last_meal_time < philo_last_meal_time)
		return (true);
	return (false);
}

void	ask_waiter(t_philo *philo, t_table *table)
{
	t_philo	*left_neighbor;
	t_philo	*right_neighbor;
	bool	left_available;
	bool	right_available;

	left_neighbor = &table->philos[((philo->id
				+ table->number_of_philosophers) - 1)
		% table->number_of_philosophers];
	right_neighbor = &table->philos[(philo->id + 1)
		% table->number_of_philosophers];
	while (1)
	{
		handle_mutex(&table->waiter_mutex, LOCK);
		left_available = !philo->left_fork->is_taken;
		right_available = !philo->right_fork->is_taken;
		if ((left_available && right_available)
			&& (!neighbor_has_priority(philo, left_neighbor)
				&& !neighbor_has_priority(philo, right_neighbor)))
		{
			acess_forks(philo);
			return ;
		}
		handle_mutex(&table->waiter_mutex, UNLOCK);
		usleep(100);
	}
}
