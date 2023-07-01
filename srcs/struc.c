#include "../includes/philosophers.h"

void	ft_free_all(t_phm *phm)
{
	int i;

	i = 0;
	if (phm->philo)
		free(phm->philo);
	pthread_mutex_destroy(&phm->print);
	pthread_mutex_destroy(&phm->var);
	if (phm->fork)
	{
		while (i < phm->philo_count)
			pthread_mutex_destroy(&phm->fork[i++]);
		free(phm->fork);
	}
	i = 0;
	if (phm->ph)
	{
		while (i < phm->philo_count)
			if(phm->ph[i])
				free(phm->ph[i++]);
		free(phm->ph);
	}
	free(phm);
}

t_phm	*ft_create_struct(int argc, char **argv)
{
	t_phm	*phm;
	int i;

	phm = (t_phm *)malloc(sizeof(t_phm));
	if (!phm)
		return (0);
	phm->philo_count = ft_atoi(argv[1]);
	phm->die_time = ft_atoi(argv[2]);
	phm->eat_time = ft_atoi(argv[3]);
	phm->sleep_time = ft_atoi(argv[4]);
	if (argc == 6)
		phm->eat_count = ft_atoi(argv[5]);
	else
		phm->eat_count = -42;
	phm->alive = 1;
	phm->philo = (pthread_t *)malloc(sizeof(t_ph) * phm->philo_count);
	if(!phm->philo)
		return (0);
	phm->ph = (t_ph **)malloc(sizeof(t_ph *) * phm->philo_count);
	if(!phm->ph)
		return (0);
	phm->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * phm->philo_count);
	if(!phm->fork)
		return (0);
	i = 0;
	while (i < phm->philo_count)
	{
		phm->ph[i] = (t_ph *)malloc(sizeof(t_ph));
		if(!phm->ph[i])
			return (0);
		pthread_mutex_init(&phm->fork[i++], NULL);
	}
	pthread_mutex_init(&phm->print, NULL);
	pthread_mutex_init(&phm->var, NULL);
	return (phm);
}