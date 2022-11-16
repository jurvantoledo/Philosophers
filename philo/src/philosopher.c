/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-tol <jvan-tol@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/06 15:56:10 by jvan-tol      #+#    #+#                 */
/*   Updated: 2022/10/21 17:41:24 by jvan-tol      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	p_eating(t_table *table, t_philosophers *philosophers)
{
	if (table->active == 0)
		return ;
	if (philosophers->id % 2)
	{
		p_mutex_lock(table, (pthread_mutex_t *)philosophers->right_fork);
		print_action(table, philosophers, "has taken a fork", 0);
		if (table->args->number_of_philosphers == 1)
			return ;
		p_mutex_lock(table, (pthread_mutex_t *)philosophers->left_fork);
		print_action(table, philosophers, "has taken a fork", 0);
	}
	else
	{
		p_mutex_lock(table, (pthread_mutex_t *)philosophers->left_fork);
		print_action(table, philosophers, "has taken a fork", 0);
		p_mutex_lock(table, (pthread_mutex_t *)philosophers->right_fork);
		print_action(table, philosophers, "has taken a fork", 0);
	}
	print_action(table, philosophers, "is eating", 0);
	philosophers->last_meal = ft_current_time();
	ft_sleep(table->args->time_to_eat / 1000);
	philosophers->servings += 1;
	p_mutex_unlock(table, (pthread_mutex_t *)philosophers->right_fork);
	p_mutex_unlock(table, (pthread_mutex_t *)philosophers->left_fork);
}

static void	p_thinking(t_table	*table, t_philosophers *philosophers)
{
	if (table->active == 0)
		return ;
	print_action(table, philosophers, "is thinking", 0);
}

static void	p_sleeping(t_table *table, t_philosophers *philosophers)
{
	if (table->active == 0)
		return ;
	print_action(table, philosophers, "is sleeping", 0);
	ft_sleep(table->args->time_to_sleep / 1000);
}

void	*ft_philosopher(void *arg)
{
	t_table			*table;
	t_philosophers	*philosopher;

	table = ((t_structs *)arg)->table;
	philosopher = ((t_structs *)arg)->philosophers;
	free((t_structs *)arg);
	while (table->active == 1)
	{
		p_eating(table, philosopher);
		if (table->args->number_of_philosphers == 1)
			return (NULL);
		p_thinking(table, philosopher);
		p_sleeping(table, philosopher);
	}
	return (NULL);
}
