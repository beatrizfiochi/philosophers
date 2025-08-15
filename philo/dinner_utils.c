/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiochi- <bfiochi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 18:06:09 by bfiochi-          #+#    #+#             */
/*   Updated: 2025/08/15 17:57:39 by bfiochi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	acess_forks(t_philo *philo)
{
	handle_mutex(&philo->right_fork->fork, LOCK);
	write_philo_status(TAKE_RIGTH_FORK, philo);
	handle_mutex(&philo->left_fork->fork, LOCK);
	write_philo_status(TAKE_LEFT_FORK, philo);
}


