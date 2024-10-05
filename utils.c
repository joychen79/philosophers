/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 11:34:05 by jingchen          #+#    #+#             */
/*   Updated: 2024/01/21 11:46:15 by jingchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	ft_number(const char *str, int index)
{
	long int	num;

	num = 0;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
		{
			num = (num * 10) + (*str - 48);
			if (num > 2147483648 && index == -1)
				(printf("Error\nThe number must be an int\n"), exit(-1));
			if (num > 2147483647 && index == 1)
				(printf("Error\nThe number must be an int\n"), exit(-1));
		}
		else
			(printf("Error\nNot a number\n"), exit(-1));
		str++;
	}
	return (num);
}

int	ft_atoi(const char *str)
{
	int	num;
	int	index;

	index = 1;
	if (*str == '\0')
		(printf("Error\nNot a number\n"), exit(-1));
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			index *= -1;
		str++;
	}
	if (*str >= '0' && *str <= '9')
		num = ft_number(str, index);
	else
		(printf("Error\nNot a number\n"), exit(-1));
	return ((int)num * index);
}

void	ft_free_all(t_table	*table)
{
	pthread_mutex_destroy(&table->mutex_dead);
	free(table->philo_dt);
	free(table);
}

void	ft_print_dead(t_table *table)
{
	printf("philosopher %d is dead in time %lld\n",
		table->philo_dt[table->i].id, time_stamp()
		- table->philo_dt[table->i].st_time);
}

void	ft_print_philo(t_philo	*philo_dt, int routine)
{
	if (routine == 0)
	{
		printf("%lldms philosopher %d has taken a fork\n",
			time_stamp() - philo_dt->st_time, philo_dt->id);
	}
	if (routine == 1)
	{
		printf("%dms philosopher %d is eating\n",
			philo_dt->last_eat, philo_dt->id);
	}
	if (routine == 2)
	{
		printf("%lldms philosopher %d is sleep\n",
			time_stamp() - philo_dt->st_time, philo_dt->id);
	}
	if (routine == 3)
	{
		printf("%lldms philosopher %d is thinking\n",
			time_stamp() - philo_dt->st_time, philo_dt->id);
	}
}
