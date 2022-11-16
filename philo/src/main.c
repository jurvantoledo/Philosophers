/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-tol <jvan-tol@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/06 15:38:14 by jvan-tol      #+#    #+#                 */
/*   Updated: 2022/10/21 17:51:11 by jvan-tol      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	create_arguments(t_table *table, char *argv[], int argc)
{
	table->args = malloc(sizeof(t_args));
	if (!table->args)
		return (0);
	table->args->number_of_philosphers = ft_atoi(argv[1]);
	table->args->time_to_die = ft_atoi(argv[2]) * 1000;
	table->args->time_to_eat = ft_atoi(argv[3]) * 1000;
	table->args->time_to_sleep = ft_atoi(argv[4]) * 1000;
	table->args->amount_of_servings = -1;
	if (argc > 5)
		table->args->amount_of_servings = ft_atoi(argv[5]);
	if (table->args->number_of_philosphers > 0 && table->args->time_to_die > 0 \
		&& table->args->time_to_eat > 0 && table->args->time_to_sleep > 0 && \
		(argc < 6 || table->args->amount_of_servings > 0))
		return (1);
	return (0);
}

static void	create_philosopher(t_table *table)
{
	t_int32			i;

	i = 0;
	table->philosophers = malloc(sizeof(t_philosophers) * \
				table->args->number_of_philosphers);
	if (!table->philosophers)
		return ;
	table->mutex = malloc(sizeof(pthread_mutex_t) \
						* (table->args->number_of_philosphers + 1));
	if (!table->mutex)
	{
		free(table->philosophers);
		table->philosophers = NULL;
		return ;
	}
	while (i < table->args->number_of_philosphers)
	{
		table->philosophers[i].id = i + 1;
		table->philosophers[i].last_meal = ft_current_time();
		p_mutex_init(table, &table->mutex[i]);
		i++;
	}
	table->philosophers->servings = 0;
	p_mutex_init(table, &table->mutex[i]);
}

int	main(int argc, char *argv[])
{
	t_table	table;

	if (argc < 5 || argc > 6)
		return (0);
	table.active = 1;
	table.philosophers = NULL;
	if (create_arguments(&table, argv, argc) == 0)
		return (0);
	create_philosopher(&table);
	seat_philosopher(&table);
	create_thread(&table);
	monitoring_threads(&table);
	wait_threads(&table);
	cleanup(&table);
}
