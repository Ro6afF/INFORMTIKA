x=6
y = 7

def my_function(a, b):
	x=17
	global y
	y = 18
	return a+b

print(my_function(5, 6))
print(x)
print(y)
