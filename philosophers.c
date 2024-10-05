/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 11:41:38 by jingchen          #+#    #+#             */
/*   Updated: 2024/01/21 14:03:13 by jingchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_check_arguments(int argc, char **argv, int bmode)
{
	if (bmode == 0)
	{
		if (argc < 5 || argc > 6 || (ft_atoi(argv[1])) <= 0)
		{
			if (argc < 5 || argc > 6)
				printf("invalid number of arguments\n");
			else if ((ft_atoi(argv[1])) <= 0)
				printf("number of philosophers incorrect\n");
			exit (1);
		}
	}
	else
	{
		printf("invalid arguments\n");
		exit(1);
	}
}

void	ft_init_table(t_table	*table, char **argv)
{
	table->bdead = 0;
	table->i = 0;
	table->philo = ft_atoi(argv[1]);
	table->die_time = (ft_atoi(argv[2]));
	table->eat_time = (ft_atoi(argv[3]));
	table->sleep_time = (ft_atoi(argv[4]));
	if (table->die_time < 0 || table->eat_time < 0
		|| table->sleep_time < 0)
		ft_check_arguments(0, argv, 1);
	if (argv[5] != NULL)
	{
		table->must_eat = ft_atoi(argv[5]);
		if (table->must_eat <= 0)
			ft_check_arguments(0, argv, 1);
	}
	else
		table->must_eat = -1;
	pthread_mutex_init(&table->mutex_dead, NULL);
}

int	main(int argc, char **argv)
{
	t_table	*table;

	ft_check_arguments(argc, argv, 0);
	table = malloc(sizeof(t_table));
	if (table == NULL)
		exit(1);
	table->philo_dt = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	if (table->philo_dt == NULL)
	{
		free(table);
		exit(1);
	}
	ft_init_table(table, argv);
	ft_init_threads(table);
	ft_join_threads(table);
	ft_free_all(table);
	return (0);
}
