import matplotlib.pyplot as plt
import numpy

other=[]
fifo=[]
rr=[]
file=open("C:/Users/ARNAV/Documents/Python/os_assignment/QUES1.1/output.txt","r")
for i in range(30):
    s=file.readline()
    if(s[0]=='o'):
        other.append(float(s[2:])*1000)
    elif(s[0]=='r'):
        rr.append(float(s[2:])*1000)
    elif(s[0]=='f'):
        fifo.append(float(s[2:])*1000)

#print(fifo)
file.close() 
barWidth=0.2  
x=[1,6,11,16,21,26,31,36,41,46]
br1=numpy.arange(len(other))
br2=[x + barWidth for x in br1]
br3=[x + barWidth for x in br2]
plt.bar(br1,other,color='r',width=barWidth,edgecolor='black',label='other')
plt.bar(br2,rr,color='g',width=barWidth,edgecolor='black',label='rr')
plt.bar(br3,fifo,color='b',width=barWidth,edgecolor='black',label='fifo')
plt.xlabel("Priority Values")
plt.ylabel("Time in millisecond")
plt.xticks([r+barWidth for r in range(len(other))],x)
plt.legend()
plt.show()