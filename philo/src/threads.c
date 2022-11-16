/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-tol <jvan-tol@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/24 10:59:51 by jvan-tol      #+#    #+#                 */
/*   Updated: 2022/10/21 17:39:34 by jvan-tol      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	create_thread(t_table *table)
{
	t_int32			i;
	t_structs		*arg;

	i = 0;
	while (i < table->args->number_of_philosphers)
	{
		arg = malloc(sizeof(t_structs));
		if (!arg)
			return ;
		arg->table = table;
		arg->philosophers = &table->philosophers[i];
		pthread_create(&table->philosophers[i].thread, NULL, \
						ft_philosopher, (void *)arg);
		i++;
	}
}

void	wait_threads(t_table *table)
{
	t_int32	i;

	i = 0;
	while (i < table->args->number_of_philosphers && table->philosophers)
	{
		p_join(table->philosophers[i].thread);
		i++;
	}
}

void	cleanup(t_table *table)
{
	t_int32	i;

	i = 0;
	while (i < table->args->number_of_philosphers)
	{	
		p_mutex_destroy(&table->mutex[i]);
		i++;
	}
	p_mutex_destroy(table->mutex);
	free(table->mutex);
	free(table->philosophers);
}
