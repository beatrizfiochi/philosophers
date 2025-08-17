/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiochi- <bfiochi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:31:03 by bfiochi-          #+#    #+#             */
/*   Updated: 2025/08/17 17:01:17 by bfiochi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	ft_isdigit(char c)
{
	return ((c >= '0') && (c <= '9'));
}

static bool	ft_isspace(char c)
{
	return (((c >= 9) && (c <= 13)) || (c == 32));
}

static const char	*valid_input(const char *input)
{
	int			len;
	const char	*tmp;
	const char	*number;

	len = 0;
	tmp = NULL;
	while (ft_isspace(*input))
		++input;
	if (*input == '+')
		++input;
	else if (*input == '-')
		return (str_error_return("Invalid argument: Negative number!\n"));
	tmp = input;
	while (*tmp != '\0')
	{
		if (!ft_isdigit(*tmp))
			return (str_error_return("Invalid argument: Incorrect digit!\n"));
		tmp++;
	}
	number = input;
	while (ft_isdigit(*input++))
		++len;
	if (len > 10)
		return (str_error_return("Invalid argument: Number too long!\n"));
	return (number);
}

static long	ft_atol(const char *str)
{
	long	num;

	num = 0;
	str = valid_input(str);
	if (str == NULL)
		return (0);
	while (ft_isdigit(*str))
	{
		num = (num * 10) + (*str - '0');
		str++;
	}
	if (num > INT_MAX)
	{
		print_error("Invalid argument: Number too long!"
			" INT_MAX is the limit!\n");
		return (0);
	}
	if (num == 0)
	{
		print_error("Invalid argument: Zeros are not allowed!\n");
		return (0);
	}
	return (num);
}

int	parse_input(t_table *table, char **argv)
{
	table->number_of_philosophers = ft_atol(argv[1]);
	table->time_to_die = (ft_atol(argv[2]));
	table->time_to_eat = (ft_atol(argv[3]));
	table->time_to_sleep = (ft_atol(argv[4]));
	if ((table->number_of_philosophers == 0) || (table->time_to_die == 0)
		|| (table->time_to_eat == 0) || (table->time_to_sleep == 0))
		return (1);
	if ((table->time_to_die < 60) || (table->time_to_eat < 60)
		|| (table->time_to_sleep < 60))
		printf("Warning: using time < 60ms\n");
	if (argv[5] != NULL)
	{
		table->number_of_times_each_philosopher_must_eat = ft_atol(argv[5]);
		if (table->number_of_times_each_philosopher_must_eat == 0)
			return (1);
	}
	else
		table->number_of_times_each_philosopher_must_eat = -1;
	return (0);
}
