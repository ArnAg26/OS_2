#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <sched.h>

int main(int argc,char **argv){
    printf("WELCOME");
    FILE *ptr;
    ptr=fopen("ques2output.txt","w");
    fclose(ptr);
    struct sched_param param;
    int pid_num=0;
    for(int i=0;i<1;i++){
    struct timespec start1,end1,start2,end2,start3,end3;
    pid_t pid1,wpid1,pid2,wpid2,pid3,wpid3;
    system("bash starting.sh");
    clock_gettime(CLOCK_REALTIME,&start1);
    pid1=fork();
    if(pid1==0){
        param.sched_priority=0;
        if(sched_setscheduler(pid_num,SCHED_OTHER,&param)!=0){
            perror("error scheduling");
        }
        if(execl("/home/sandy/assignment2/A.sh",NULL)==-1){
            perror("Incorrect command");
        }
        exit(EXIT_FAILURE);
    }
    else if(pid1<0){
        perror("Error forking");
    }
    else if(pid1>0) {
        clock_gettime(CLOCK_REALTIME,&start2);
        pid2=fork();
        if(pid2==0){
            param.sched_priority=50;
            if(sched_setscheduler(pid_num,SCHED_RR,&param)!=0){
                perror("error scheduling");
            }
            if(execl("/home/sandy/assignment2/B.sh",NULL)==-1){
                perror("Incorrect Command");
            }
            exit(EXIT_FAILURE);
        }
        else if(pid2<0){
            perror("Error forking");
        }
        else if(pid2>0){
            clock_gettime(CLOCK_REALTIME,&start3);
            pid3=fork();
            if(pid3==0){
                param.sched_priority=50;
                if(sched_setscheduler(pid_num,SCHED_FIFO,&param)!=0){
                    perror("error scheduling");
                }
                if(execl("/home/sandy/assignment2/C.sh",NULL)==-1){
                    perror("Incorrect Command");
                }
                exit(EXIT_FAILURE);
            }
            else if(pid3<0){
                perror("Error forking");
            }
            else if(pid3>0){
                
            }
            
        }
        
        int wpid1=waitpid(-1,NULL,0);
        while(wpid1!=-1){
            if(wpid1==pid1){
                clock_gettime(CLOCK_REALTIME,&end1);
            }
            else if(wpid1==pid2){
                clock_gettime(CLOCK_REALTIME,&end2);
            }
            else if(wpid1==pid3){
                clock_gettime(CLOCK_REALTIME,&end3);
            }
            wpid1=waitpid(-1,NULL,0);
        }
        
    }

    struct timespec *td1=(struct timespec *)malloc(sizeof(struct timespec*));
    struct timespec *td2=(struct timespec *)malloc(sizeof(struct timespec*));
    struct timespec *td3=(struct timespec *)malloc(sizeof(struct timespec*));
    ptr=fopen("ques2output.txt","a");
    td1->tv_nsec=end1.tv_nsec-start1.tv_nsec;
    td1->tv_sec=end1.tv_sec-start1.tv_sec;
    if(td1->tv_nsec<0){
        td1->tv_sec--;
        td1->tv_nsec+=1000000000;
    }
    double nsec=(double)(td1->tv_nsec)/(double)(1000000000);
    double sec=(double)(td1->tv_sec);
    sec=nsec+sec;
    fprintf(ptr,"P1 :%f\n",sec);
    td2->tv_nsec=end2.tv_nsec-start2.tv_nsec;
    td2->tv_sec=end2.tv_sec-start2.tv_sec;
    if(td2->tv_nsec<0){
        td2->tv_sec--;
        td2->tv_nsec+=1000000000;
    }
    nsec=(double)(td2->tv_nsec)/(double)(1000000000);
    sec=(double)(td2->tv_sec);
    sec=nsec+sec;
    fprintf(ptr,"P2 :%f\n",sec);
    td3->tv_nsec=end3.tv_nsec-start3.tv_nsec;
    td3->tv_sec=end3.tv_sec-start3.tv_sec;
    if(td3->tv_nsec<0){
        td3->tv_sec--;
        td3->tv_nsec+=1000000000;
    }
    nsec=(double)(td3->tv_nsec)/(double)(1000000000);
    sec=(double)(td3->tv_sec);
    sec=nsec+sec;
    fprintf(ptr,"P3 :%f\n",sec);
    fclose(ptr);
    system("bash ending.sh");
    }
    return 1;


}