void    take_fork()
{

}

void    is_eating()
{

}

void    is_sleeping()
{

}

void    is_thinking()
{

}

void    eaten_all_meals()
{

}

void    is_dead()
{

}

void    *cycle(void *phi_struct)
{
    pthread_mutex_t     acting;

    if (pthread_mutex_init(&acting, NULL) != 0)
        return ;
    pthread_mutex_lock(&acting);

    pthread_mutex_unlock(&acting);
}
