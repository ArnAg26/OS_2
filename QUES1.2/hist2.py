import matplotlib.pyplot as plt

lst=[]
file=open("C:/Users/ARNAV/Documents/Python/os_assignment/QUES1.2/ques2output.txt","r")
for i in range(3):
    s=file.readline()
    if(s[1]=='1'):
        lst.append(float(s[4:]))
    elif(s[1]=='2'):
        lst.append(float(s[4:]))
    elif(s[1]=='3'):
        lst.append(float(s[4:]))


file.close()
x=["other","rr","fifo"]
plt.bar(x,lst,width=0.5)
plt.xlabel("Iteration number")
plt.ylabel("time in sec")
plt.title("Kernel Compilation")
plt.show()