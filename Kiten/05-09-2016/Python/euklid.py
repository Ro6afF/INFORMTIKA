a=int(input())
b=int(input())

if a<b:
	b,a=a,b

while b!=0:
	a,b=b,a%b

print(a)
