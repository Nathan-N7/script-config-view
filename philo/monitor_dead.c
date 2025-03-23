#include "philo.h"

int has_dead(t_table    *table)
{
    int status;

    pthread_mutex_lock(&table->dead);
    status = table->has_dead;
    pthread_mutex_unlock(&table->dead);
    return (status);
}

void    check_dead(t_philo *philo)
{
    long    time;

    pthread_mutex_lock(&philo->table->wait);
    pthread_mutex_lock(&philo->lock);
    time = now() - philo->last_meal;
    pthread_mutex_unlock(&philo->table->wait);
    pthread_mutex_unlock(&philo->lock);
    if (time >= philo->table->time_die)
    {
        pthread_mutex_lock(&philo->table->dead);
        printf("%ld %d is dead\n", now() - philo->table->tm_start, philo->id);
        philo->table->has_dead = 1;
        pthread_mutex_unlock(&philo->table->dead);
    }
}

int get_meal(t_philo *philo)
{
    int meal;

    meal = 0;
    pthread_mutex_lock(&philo->meal);
    meal = philo->meals;
    pthread_mutex_unlock(&philo->meal);
    return (meal);
}

void    *monitor(void *arg)
{
    int i;
    t_philo *philo;

    i = 0;
    philo = (t_philo *)arg;
    while (!has_dead(philo->table) && get_meal(&philo->table->philos[i]) != philo->table->num_eats)
    {
        check_dead(&philo->table->philos[i]);
        i = (i + 1) % philo->table->philo_nbr;
        usleep(600);
    }
    return (NULL);
}