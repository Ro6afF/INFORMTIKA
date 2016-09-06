def func(a):
	if(a<100):
		return False
	else:
		return True

def binaryearch(s, e, f):
	if s + 1 == e:
		return e
	mid = (s + e) // 2
	if f(mid):
		return binaryearch(s, mid, f)
	else:
		return binaryearch(mid, e, f)

print(binaryearch(0, 1000, func))
