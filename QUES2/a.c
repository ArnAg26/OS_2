#include <linux/syscalls.h>
#include <linux/kernel.h>

SYSCALL_DEFINE4(copytwodarray,float *,source,float *,destination,int,rows,int,columns){
	float buffer[40];
	if(__copy_from_user(buffer,source,rows*columns*sizeof(float)))
		return -EFAULT;
	if(__copy_to_user(destination,buffer,rows*columns*sizeof(float)))
		return -EFAULT;
	return 0;
}