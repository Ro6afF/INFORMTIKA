-- vim: et

numbers = [1,2,3,4,5]

numbers0 = 0:numbers

doReverse [] others = others
doReverse (x:xs) others= doReverse xs (x:others)

myReverse items = doReverse items []
