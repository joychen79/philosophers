/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 11:49:02 by jingchen          #+#    #+#             */
/*   Updated: 2024/01/21 13:04:03 by jingchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_check_dead(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	while (table->bdead == 0)
	{
		table->i = 0;
		while (table->i < table->philo && table->bdead == 0)
		{
			pthread_mutex_lock(&(table->mutex_dead));
			if (table->philo_dt[table->i].eat == table->must_eat)
			{
				pthread_mutex_unlock(&(table->mutex_dead));
				return (NULL);
			}
			if (time_stamp() - table->philo_dt[table->i].st_time
				- table->philo_dt[table->i].last_eat > table->die_time)
			{
				ft_print_dead(table);
				table->bdead = 1;
			}
			pthread_mutex_unlock(&(table->mutex_dead));
			table->i++;
		}
	}
	return (NULL);
}

void	ft_init_threads(t_table	*table)
{
	int	i;

	i = 0;
	while (i < table->philo)
	{
		table->philo_dt[i].id = i + 1;
		table->philo_dt[i].table = table;
		table->philo_dt[i].state = 0;
		table->philo_dt[i].eat = 0;
		table->philo_dt[i].last_eat = 0;
		if (table->philo_dt[i].id % 2 != 0)
			table->philo_dt[i].state = 1;
		table->philo_dt[i].st_time = time_stamp();
		if (pthread_create(&table->philo_dt[i].thread, NULL,
				&ft_threads, &(table->philo_dt[i])) != 0)
			exit(1);
		i++;
	}
	if (pthread_create(&table->dead_thread, NULL, &ft_check_dead, table) != 0)
		exit(1);
}

void	*ft_threads(void *arg)
{
	t_philo	*philo_dt;

	philo_dt = (t_philo *)arg;
	pthread_mutex_init(&philo_dt->fork, NULL);
	philo_dt->bphilo = 0;
	if (philo_dt->state == 0)
		ft_usleep(philo_dt->table->eat_time / 2);
	while ((philo_dt->eat < philo_dt->table->must_eat
			|| philo_dt->table->must_eat < 0))
	{
		pthread_mutex_lock(&(philo_dt->table->mutex_dead));
		if (philo_dt->table->bdead == 0)
		{
			pthread_mutex_unlock(&(philo_dt->table->mutex_dead));
			ft_left_fork(philo_dt);
			ft_right_forks(philo_dt);
		}
		else
		{
			pthread_mutex_unlock(&(philo_dt->table->mutex_dead));
			return (NULL);
		}
	}
	return (NULL);
}

void	ft_join_threads(t_table	*table)
{
	int	i;

	i = 0;
	while (i < table->philo)
	{
		if (pthread_join(table->philo_dt[i].thread, NULL) != 0)
			exit(1);
		pthread_mutex_destroy(&table->philo_dt->fork);
		i++;
	}
	if (pthread_join(table->dead_thread, NULL) != 0)
		exit(1);
}
