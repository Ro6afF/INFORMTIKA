suma 0 = 0
suma a = a + suma (a-1)

main = do
    putStrLn (show (suma (1000000-1)))
