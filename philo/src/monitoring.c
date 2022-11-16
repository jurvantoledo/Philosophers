/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitoring.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-tol <jvan-tol@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 13:45:02 by jvan-tol      #+#    #+#                 */
/*   Updated: 2022/10/21 16:30:04 by jvan-tol      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	check_if_served(t_table *table)
{
	t_int32	i;

	if (table->args->amount_of_servings < 0)
		return (0);
	i = 0;
	while (i < table->args->number_of_philosphers)
	{
		if (table->philosophers[i].servings < table->args->amount_of_servings)
			return (0);
		i++;
	}
	table->active = 0;
	return (1);
}

static int	check_death(t_table *table)
{
	t_int32	i;
	t_int64	diff;
	t_int64	current;

	i = 0;
	current = ft_current_time();
	while (i < table->args->number_of_philosphers)
	{
		diff = current - table->philosophers[i].last_meal;
		if (diff > table->args->time_to_die / 1000)
		{
			table->active = 0;
			print_action(table, &table->philosophers[i], "died", 1);
			return (1);
		}
		i++;
	}
	return (0);
}

void	monitoring_threads(t_table *table)
{
	while (1)
	{
		if (check_if_served(table) == 1)
			break ;
		if (check_death(table) == 1)
			break ;
		usleep(10);
	}
}
