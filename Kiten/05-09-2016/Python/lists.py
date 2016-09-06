a=[1,2,3,4,5]
a.append(42)
print(a, len(a))

a=[]
for i in range(100):
	a.append(i)

print(a[33:])
print(a[:17])
print(a[10:16])
