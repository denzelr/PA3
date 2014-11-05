#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <sched.h>
#include <unistd.h>
#include <sys/wait.h>

#define DEFAULT_ITERATIONS 1000000
#define RADIUS (RAND_MAX / 2)

inline double dist(double x0, double y0, double x1, double y1){
    return sqrt(pow((x1-x0),2) + pow((y1-y0),2));
}

inline double zeroDist(double x, double y){
    return dist(0, 0, x, y);
}

int main(int argc, char* argv[]){
    int pid;

    int forks = atol(argv[argc-1]);
    printf("%i\n", forks);
    int pid_megatron[forks];
    int i;


    int policy;
    struct sched_param param;
if(argc < 3){
           policy = SCHED_OTHER;
        }
        /* Set iterations if supplied */
        
        /* Set policy if supplied */
        if(argc > 2){
           if(!strcmp(argv[2], "SCHED_OTHER")){
               policy = SCHED_OTHER;
           }
           else if(!strcmp(argv[2], "SCHED_FIFO")){
               policy = SCHED_FIFO;
           }
           else if(!strcmp(argv[2], "SCHED_RR")){
               policy = SCHED_RR;
           }
           else{
               fprintf(stderr, "Unhandeled scheduling policy\n");
               exit(EXIT_FAILURE);
           }
        }
        
        /* Set process to max prioty for given scheduler */
        param.sched_priority = sched_get_priority_max(policy);
        
        /* Set new scheduler policy */
        fprintf(stdout, "Current Scheduling Policy: %d\n", sched_getscheduler(0));
        fprintf(stdout, "Setting Scheduling Policy to: %d\n", policy);
        if(sched_setscheduler(0, policy, &param)){
           perror("Error setting scheduler policy");
           exit(EXIT_FAILURE);
        }
        fprintf(stdout, "New Scheduling Policy: %d\n", sched_getscheduler(0));





    for(i = 0; i < forks; i++){
        pid = fork();
        if(pid == 0){
            break;
        }
        else{
            pid_megatron[i] = pid;
        }
    }

    if (pid == 0){

        //printf("Hello from pid 0");

        //fprintf(stdout, "Scheduling Policy in pid 0 is: %d\n", sched_getscheduler(0));

        long i;
        long iterations;
        
        
        double x, y;
        double inCircle = 0.0;
        double inSquare = 0.0;
        double pCircle = 0.0;
        double piCalc = 0.0;

        /* Process program arguments to select iterations and policy */
        /* Set default iterations if not supplied */
        if(argc < 2){
    	   iterations = DEFAULT_ITERATIONS;
        }

        if(argc > 1){
           iterations = atol(argv[1]);
           if(iterations < 1){
               fprintf(stderr, "Bad iterations value\n");
               exit(EXIT_FAILURE);
           }
        }
        /* Set default policy if not supplied */
        
        /* Calculate pi using statistical methode across all iterations*/
        for(i=0; i<iterations; i++){
    	   x = (random() % (RADIUS * 2)) - RADIUS;
    	   y = (random() % (RADIUS * 2)) - RADIUS;
    	   if(zeroDist(x,y) < RADIUS){
    	       inCircle++;
    	   }
    	   inSquare++;
        }

        /* Finish calculation */
        pCircle = inCircle/inSquare;
        piCalc = pCircle * 4.0;

        /* Print result */
        fprintf(stdout, "pi = %f\n", piCalc);
    }
    else{
        int status;
        //int i = 0;
        for(i = 0; i < forks ; i++)
        {
            pid = pid_megatron[i];
            while(1){
                pid = waitpid(pid, &status, WNOHANG);
                if(pid != 0){
                    break;
                }
            }
        }
    }
    //printf("%s\n", argv[2]);
    printf("%i\n", argc);
    return 0;
}
