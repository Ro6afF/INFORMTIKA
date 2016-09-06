-- vim: et

factorial :: Integer -> Integer
factorial 0 = 1
factorial n = n * (factorial (n-1))

main = do
    putStrLn (show (factorial 10))
    putStrLn (show (factorial 5000))
