#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#include <alchemy/task.h>
#include <alchemy/timer.h>
#include <alchemy/sem.h>

#define ITER 100000

static RT_TASK tarea1;
static RT_TASK tarea2;
static RT_TASK tarea3;
static RT_TASK tarea4;
static RT_SEM semaforo;

int global = 0;
int global2 = 1;

void tareaUno(void *arg){
    int i;
    for(i=0; i < ITER; i++){
        rt_sem_p(&semaforo);
        printf("Tarea 1 la variable global es %d -----\n", ++global);
        rt_sem_v(&semaforo);
    }
}

void tareaDos(void *arg){
    int i;
    for(i=0; i < ITER; i++){
        rt_sem_p(&semaforo);
        printf("Tarea 2 la variable global es %d -----\n", --global);
        rt_sem_v(&semaforo);
    }
}

void tareaTres(void *arg){
    int i;
    for(i=0; i < ITER; i++){
        rt_sem_p(&semaforo);
        global2 = global2+global;
        printf("Tarea 3 la variable global2 es %d -----\n", global2);
        rt_sem_v(&semaforo);
    }
}

void tareaCuarto(void *arg){
    int i;
    for(i=0; i < ITER; i++){
        rt_sem_p(&semaforo);
        global2 = global2+global;
        printf("Tarea 4 la variable global2 es %d -----\n", global2);
        rt_sem_v(&semaforo);
    }
}

int main(int argc, char* argv[]){
    rt_sem_create(&semaforo, "semaforo", 1, S_PRIO);
    rt_task_create(&tarea1, "tarea 1", 0 , 1, 0);
    rt_task_create(&tarea2, "tarea 2", 0 , 1, 0);
    rt_task_create(&tarea3, "tarea 3", 0 , 1, 0);
    rt_task_create(&tarea4, "tarea 4", 0 , 1, 0);
    rt_task_start(&tarea1, &tareaUno,0);
    rt_task_start(&tarea2, &tareaDos,0);
    rt_task_start(&tarea3, &tareaTres,0);
    rt_task_start(&tarea4, &tareaCuarto,0);
    return 0;
}
