/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiochi- <bfiochi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:11:03 by bfiochi-          #+#    #+#             */
/*   Updated: 2025/08/17 17:09:17 by bfiochi-         ###   ########.fr       */
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

long long get_time(void)
{
    struct timeval tv;

    if (gettimeofday(&tv, NULL))
    {
        print_error("gettimeofday failed!\n");
        return (-1);
    }
    return ((tv.tv_sec * 1000000) + tv.tv_usec) / 1000;
}

void my_usleep(long msec, t_table *table)
{
    long long start;
    long long elapsed;

    start = get_time();
    while (1)
    {
        if (simulation_finish(table))
            break;
        elapsed = get_time() - start;
        if (elapsed >= msec)
            break;
        usleep(100);
    }
}

// long long	get_time(t_timecode time_code)
// {
// 	struct timeval	tv;

// 	if (gettimeofday(&tv, NULL))
// 	{
// 		print_error("gettimeofday failed!\n");
// 		return (-1);
// 	}
// 	if (time_code == SECOND)
// 		return (tv.tv_sec + (tv.tv_usec / 1000000));
// 	else if (time_code == MILLESECOND)
// 		return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
// 	else if (time_code == MICROSECOND)
// 		return ((tv.tv_sec * 1000000) + (tv.tv_usec));
// 	else
// 	{
// 		print_error("Wrong input to get_time function\n");
// 		return (-1);
// 	}
// }

// void	my_usleep(long msec, t_table *table)
// {
// 	long long	start;
// 	long long	remmaning;

// 	start = get_time(MILLESECOND);
// 	remmaning = msec;
// 	while (remmaning > 0)
// 	{
// 		if (simulation_finish(table))
// 			break ;
// 		if (remmaning > 1)
// 			usleep(1000);
// 		else
// 			usleep(remmaning);
// 		remmaning = msec - (get_time(MILLESECOND) - start);
// 	}
// }

// void	my_usleep(long usec, t_table *table)
// {
// 	long	start;
// 	long	elapsed;
// 	long	remmaning;

// 	start = get_time(MICROSECOND);
// 	while ((get_time(MICROSECOND) - start) < usec)
// 	{
// 		if (simulation_finish(table))
// 			break ;
// 		elapsed = (get_time(MICROSECOND) - start);
// 		remmaning = usec - elapsed;
// 		if (remmaning > 1000)
// 			usleep(remmaning / 2);
// 		else
// 		{
// 			while ((get_time(MICROSECOND) - start) < usec)
// 				usleep(50);
// 		}
// 	}
// }
