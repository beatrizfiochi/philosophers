/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiochi- <bfiochi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 18:06:09 by bfiochi-          #+#    #+#             */
/*   Updated: 2025/08/15 15:36:48 by bfiochi-         ###   ########.fr       */
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
	handle_mutex(&philo->left_fork->fork, LOCK);
	write_philo_status(TAKE_LEFT_FORK, philo);
	handle_mutex(&philo->right_fork->fork, LOCK);
	write_philo_status(TAKE_RIGTH_FORK, philo);
	set_fork_is_taken(philo, true);
}

static bool	ngb_priority(t_philo *philo, t_philo *philo_ngb)
{
	long	philo_last_meal_time;
	long	philo_ngb_last_meal_time;

	philo_last_meal_time = philo->last_meal_time;
	philo_ngb_last_meal_time = philo_ngb->last_meal_time;
	if (philo_ngb_last_meal_time < philo_last_meal_time)
		return (true);
	return (false);
}

void	ask_waiter(t_philo *philo, t_table *table)
{
	t_philo	*left_ngb;
	t_philo	*right_ngb;
	bool	left_aval;
	bool	right_aval;

	left_ngb = &table->philos[((philo->id
				+ table->number_of_philosophers) - 1)
		% table->number_of_philosophers];
	right_ngb = &table->philos[(philo->id + 1)
		% table->number_of_philosophers];
	while (!simulation_finish(table))
	{
		handle_mutex(&table->waiter_mutex, LOCK);
		left_aval = !philo->left_fork->is_taken;
		right_aval = !philo->right_fork->is_taken;
		if ((left_aval && right_aval) && (!ngb_priority(philo, left_ngb)
				&& !ngb_priority(philo, right_ngb)))
		{
			acess_forks(philo);
			handle_mutex(&philo->table->waiter_mutex, UNLOCK);
			return ;
		}
		handle_mutex(&table->waiter_mutex, UNLOCK);
		usleep(100);
	}
}
