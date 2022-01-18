/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcorenti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 04:57:31 by rcorenti          #+#    #+#             */
/*   Updated: 2022/01/18 03:30:20 by rcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_args(char **argv)
{
	int			i;
	int			j;
	long long	nbr;

	i = 0;
	while (argv[++i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] > '9' || argv[i][j] < '0')
			{
				printf("Error\nBad argument\n");
				return (1);
			}
			j++;
		}
		nbr = ft_atoi(argv[i]);
		if (nbr < -2147483648 || nbr > 2147483647)
		{
			printf("Error\nMax or min integer\n");
			return (1);
		}
	}
	return (0);
}

static void	ft_start(t_data *data)
{
	t_philo		*philo;
	pthread_t	*thread;

	data->time = set_time(data);
	thread = (pthread_t *)malloc(sizeof(pthread_t) * data->nbr);
	if (!thread)
		printf("Error\nMalloc error\n");
	philo = (t_philo *)malloc(sizeof(t_philo) * data->nbr);
	if (!philo)
		printf("Error\nMalloc error\n");
	if (!philo || !thread)
		return ;
	if (start_philos(data, philo, thread))
		return ;
	check_dead(data, philo);
	ft_exit(data, philo, thread);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
	{
		printf("Error\nBad number of arguments\n");
		return (0);
	}
	if (check_args(argv) == 1)
		return (0);
	ft_init(&data, argv);
	ft_start(&data);
	return (0);
}
