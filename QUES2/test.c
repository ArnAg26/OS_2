#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <errno.h>
#include <linux/kernel.h>

#define KERNEL_TWOD_COPY 451
int check2(float *a,float *b,int len){
	for(int i=0;i<len;i++){
		printf("%f %f\n",a[i],b[i]);
		if(a[i]!=b[i]){
			return -1;
		}
	}
	return 0;
}
void check(int size1,int size2,float src[size1][size2],float dest[size1][size2]){
	for(int i=0;i<size1;i++){
		if(check2(src[i],dest[i],size2)==-1){
			printf("Error system call does not work\n");
			return;
		}
	}
	printf("syscall workd!! Congrats\n");
}
int main(){
	float src[5][5]={{1,1,1,1,1},{2,2,2,2,2},{3,3,3,3,3},{4,4,4,4,4},{5,5,5,5,5}};
	float dest[5][5];
	long sys_call_status;
	sys_call_status=syscall(KERNEL_TWOD_COPY,src,dest,5,5);
	if(sys_call_status!=EFAULT){
		printf("Message: System call invoked congratulations\n");
		check(5,5,src,dest);
	}
	return 0;
}