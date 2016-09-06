-- vim: et

fibonacci a | a <= 1    = a
            | otherwise = fibonacci (a-1) + fibonacci (a-2)

addLists [] [] = []
addLists (x:xs) (y:ys) = (x+y):(addLists xs ys)

fib = 0:1:(addLists fib (drop 1 fib))
