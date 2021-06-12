#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include<ncurses.h>


#define N 7
#define MAX_LIFE 15
#define EAT_T 2
#define REST_T 2
#define THINK_T 2
#define TIMEOUT 20
#define EATING 1
#define RESTING 0
#define THINKING 2
#define RIGHT (philo_num + (N-1)) % N
#define LEFT (philo_num + 1) % N

int Random(int,int);
void rest(int);
void test(int);


//Philosophers and their forks
int state[N] ;
pthread_t philosophers[N];
pthread_mutex_t forks[N] ;

//Health related stuff
pthread_t health_bars[N] ;
int HP[N];

//Their world's countdown to oblivion
pthread_t world ;
int life = TIMEOUT;

//Just a secondary function to get the random aspect of randomly choosing what to do next
int Random(int lower, int upper)
{
    int i;
    srand(time(0));
    int num = (rand() % (upper - lower + 1)) + lower;
    return num;
}

//This is to check if a philosopher can pick up the specified fork
bool try(int philo_num){
    if(pthread_mutex_trylock(&forks[philo_num]) == 0){
        pthread_mutex_unlock(&forks[philo_num]);
        return true;
    }
    return false;
}

//The function for the philosopher to eat
void eat(int philo_num){
    pthread_mutex_lock(&forks[philo_num]);
    pthread_mutex_lock(&forks[LEFT]);
    state[philo_num] = EATING;
    HP[philo_num] = MAX_LIFE ;
    printf("%d is eating with forks %d and %d\n",philo_num,philo_num,LEFT);
    sleep(EAT_T);
    pthread_mutex_unlock(&forks[philo_num]);
    pthread_mutex_unlock(&forks[LEFT]);
    rest(philo_num);
    return;
}

//The function for the philospher to think
void think(int philo_num){
    if(try(philo_num)){ // Checking his own fork first, the one at his right
        pthread_mutex_lock(&forks[philo_num]);
        state[philo_num] = THINKING;
        printf("%d is thinking with fork %d\n",philo_num,philo_num);
        sleep(THINK_T);
        pthread_mutex_unlock(&forks[philo_num]);
        printf("%d has put down the fork %d\n",philo_num,philo_num);
        return;
    }
    if(try(LEFT)){ // Checking the fork at his left
        pthread_mutex_lock(&forks[LEFT]);
        state[philo_num] = THINKING;
        printf("%d is thinking with fork %d\n",philo_num,LEFT);
        sleep(THINK_T);
        pthread_mutex_unlock(&forks[LEFT]);
        printf("%d has put down the fork %d\n",philo_num,LEFT);
        return;
    }
}

//The function for the philosopher to rest
void rest(int philo_num){
    if(state[philo_num] == RESTING){
        printf("%d is still resting...\n",philo_num);
        sleep(1);
        return;
    }
    else{
        state[philo_num] = RESTING;
        printf("%d is resting...\n",philo_num);
        sleep(REST_T);
        return;
    }
}

//To get the random act, we randomly choose what the philosophers will do
void test(int philo_num){
    if(Random(EATING,THINKING) == EATING){
        if(try(philo_num) && try(LEFT)){
            eat(philo_num);
        }
        return;
    }
    else{
        if(try(philo_num) || try(LEFT)){
            think(philo_num);
        }
        return;
    }
}

// Ah, a philosopher's way of life, testing whether to eat or think, a difficult choice indeed
void * way_of_life(void * philo){
    int * i = (int*)philo;
    int philo_num = *i;
    while(1){
        test(philo_num);
    }
}

//Destroying the threads of their live.. I mean, the threads of the code
void detach(){
    for(int i=0;i<N;i++){
        pthread_mutex_destroy(&forks[i]);
        pthread_detach(philosophers[i]);
        pthread_detach(health_bars[i]);
    }
    pthread_detach(world);
    return;
}

//YOU EAT YOU LIVE, YOU DON'T EAT YOU DIE, represented by the good ol' health points system
void * health_time(void * philo){
    int * i = (int*)philo;
    int philo_num = *i;
    while(HP[philo_num] > 0 ){
        sleep(2);
        printf("%d has %d hp remaining\n",philo_num,HP[philo_num]);
        HP[philo_num] -= 1 ;
    }
    sleep(1);
    printf("%d has passed away, REST IN PEACE LEGEND !!!\n",philo_num);
    detach();
    exit(EXIT_SUCCESS);
}

//Yeah, they have no idea I control their world's doom coming MWAHAHAHAHA
void * living(void * arg){
    while(life > 0){
        printf("%d seconds remaining\n",life);
        sleep(2);
        life -= 1;
    }
    detach();
    printf("EVERYONE IS ALIVE, LET'S DAAAAAAAAANCE !!!!\n");
    detach();
    exit(EXIT_SUCCESS);
}

//Meh, a function just to get the state of the philosopher
int states(int philo_num){
    return state[philo_num];
}

//Another Meh, just to get ZA WARUDO's remaining time
int countdown(){
    return life;
}

//And this is where the fun begins
int main(){

    int i ;

    for(int j=0 ; j<N ;j++){
        HP[j] = MAX_LIFE;
    }

    pthread_create(&world,NULL,living,NULL);

    for(i = 0 ; i < N ; i++ ){
        pthread_create(&philosophers[i],NULL,way_of_life,&i);
        pthread_create(&health_bars[i],NULL,health_time,&i);
    }

    for(i = 0 ; i < N ; i++){
        pthread_join(philosophers[i],NULL);
    }

    return 0;
}
