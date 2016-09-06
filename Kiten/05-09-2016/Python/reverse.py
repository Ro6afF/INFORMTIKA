curr = input()
a=[]

x=0

while curr!="":
	a.append(curr)
	curr=input()
	x+=1

x-=1

while x>=0:
	print(a[x])
	x-=1
