#include <stdio.h>
#include <unistd.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <stdlib.h>

int j=1;

void countA(){
    unsigned long long int i;
    for(i=1;i<4294967296;i++){
        //nothing
    }
}

void countB(){
    unsigned long long int i;
    for(i=1;i<4294967296;i++){
        //nothing
    }
}

void countC(){
    unsigned long long int i;
    for(i=1;i<4294967296;i++){
        //nothing
    }
}

void *ThrA(void *arg){
    struct sched_param param;
    param.sched_priority=0;
    if(pthread_setschedparam(pthread_self(),SCHED_OTHER,&param)!=0){
        perror("Error1");
    }
    struct timespec start,finish;
    struct timespec *td=(struct timespec *)malloc(sizeof(struct timespec*));
    clock_gettime(CLOCK_REALTIME,&start);
    countA();
    clock_gettime(CLOCK_REALTIME,&finish);
    td->tv_nsec=finish.tv_nsec-start.tv_nsec;
    td->tv_sec=finish.tv_sec-start.tv_sec;
    if(td->tv_nsec<0){
        td->tv_sec--;
        td->tv_nsec+=1000000000;
    }
    double nsec=(double)(td->tv_nsec)/(double)(1000000000);
    double sec=(double)(td->tv_sec);
    sec=nsec+sec;
    FILE *ptr;
    ptr=fopen("output.txt","a");
    fprintf(ptr,"%c:%f\n",'o',sec);
    fclose(ptr);
    printf("other: %f\n",sec);
    //pthread_exit(NULL);
    return NULL;
}

void *ThrB(void *arg){
    struct sched_param param;
    param.sched_priority=j;
    if(pthread_setschedparam(pthread_self(),SCHED_RR,&param)!=0){
        perror("Error2");
    }
    struct timespec start,finish;
    struct timespec *td=(struct timespec *)malloc(sizeof(struct timespec*));
    clock_gettime(CLOCK_REALTIME,&start);
    countB();
    clock_gettime(CLOCK_REALTIME,&finish);
    td->tv_nsec=finish.tv_nsec-start.tv_nsec;
    td->tv_sec=finish.tv_sec-start.tv_sec;
    if(td->tv_nsec<0){
        td->tv_sec--;
        td->tv_nsec+=1000000000;
    }
    double nsec=(double)(td->tv_nsec)/(double)(1000000000);
    double sec=(double)(td->tv_sec);
    sec=nsec+sec;
    FILE *ptr;
    ptr=fopen("output.txt","a");
    fprintf(ptr,"%c:%f\n",'r',sec);
    fclose(ptr);
    printf("rr: %f\n",sec);
    //pthread_exit(NULL);
    return NULL;

}

void *ThrC(void *arg){
    struct sched_param param;
    param.sched_priority=j;
    printf("%d",j);
    if(pthread_setschedparam(pthread_self(),SCHED_FIFO,&param)!=0){
        perror("Error3");
    }
    struct timespec start,finish;
    struct timespec *td=(struct timespec *)malloc(sizeof(struct timespec*));
    clock_gettime(CLOCK_REALTIME,&start);
    countC();
    clock_gettime(CLOCK_REALTIME,&finish);
    td->tv_nsec=finish.tv_nsec-start.tv_nsec;
    td->tv_sec=finish.tv_sec-start.tv_sec;
    if(td->tv_nsec<0){
        td->tv_sec--;
        td->tv_nsec+=1000000000;
    }
    double nsec=(double)(td->tv_nsec)/(double)(1000000000);
    double sec=(double)(td->tv_sec);
    sec=nsec+sec;
    FILE *ptr;
    ptr=fopen("output.txt","a");
    fprintf(ptr,"%c:%f\n",'f',sec);
    fclose(ptr);
    printf("fifo: %f\n",sec);
    //pthread_exit(NULL);
    return NULL;
  
}
    

int main(int argc,char **argv){
    FILE *ptr;
    ptr=fopen("output.txt","w");
    fclose(ptr);
    int d=getpid();
    char t[100];
    char str[20];
    sprintf(str,"%d",d);
    strcat(t,"cpulimit -p ");
    strcat(t,str);
    strcat(t," --limit 25");
    printf("%s\n",&t);
    //system(t);
    char a[1]="0";
    
    for(int i=0;i<10;i++){                
        pthread_t threadA;
        pthread_t threadB;
        pthread_t threadC;
        pthread_attr_t attr;
        if(pthread_create(&threadA,NULL,&ThrA,NULL)!=0){
            perror("Error creating thread");
            return 0;
        }
        if(pthread_create(&threadB,NULL,&ThrB,NULL)!=0){
            perror("Error creating thread");
            return 0;
        }
        if(pthread_create(&threadC,NULL,&ThrC,NULL)!=0){
            perror("Error creating thread");
            return 0;
        }
        pthread_join(threadA,NULL);
        pthread_join(threadB,NULL);
        pthread_join(threadC,NULL);
        //a[0]=a[0]+1;
        //printf("%s\n",&a);
        j+=5;
        
    }
}


