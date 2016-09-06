def merge(a, b):
	i1 = 0
	i2 = 0
	res = []
	while i1<len(a) and i2<len(b):
		if a[i1] < b[i2]:
			res.append(a[i1])
			i1+=1
		else:
			res.append(b[i2])
			i2+=1
	while i1 < len(a):
		res.append(a[i1])
		i1+=1
	while i2 < len(b):
		res.append(b[i2])
		i2+=1
	return res

def mergesort(a):
	if len(a)==1:
		return a
	h = len(a)//2
	return merge(mergesort(a[:h]), mergesort(a[h:]))

print(mergesort([1,2,3,9,4,7,5,6,100]))
