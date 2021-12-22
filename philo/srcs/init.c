/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcorenti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 06:13:10 by rcorenti          #+#    #+#             */
/*   Updated: 2021/12/22 04:10:32 by rcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_philo(t_philo *philo, int nbr, int max)
{
	philo->nbr = nbr;
	philo->fork_left = nbr;
	philo->fork_right = (nbr + 1) % max;
	philo->eat = 0;
}

static void	ft_mutex(t_data *data)
{
	int	i;

	i = 0;
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->nbr);
	while (i < data->nbr)
	{
		pthread_mutex_init(&(data->forks[i]), NULL);
		i++;
	}
	pthread_mutex_init(&(data->write), NULL);
}

void	ft_init(t_data *data, char **argv)
{
	data->nbr = ft_atoi(argv[1]);
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->eat = ft_atoi(argv[5]);
	else
		data->eat = -1;
	data->dead = -1;
	data->all_eat = -1;
	data->error = -1;
	ft_mutex(data);
}
