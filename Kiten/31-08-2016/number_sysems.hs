-- vim: et

numChars = "0123456789abcdefghijklmnopqrstuvwyxz"

rep 0 modul y = y
rep x modul y = rep (x `div` modul) modul ((numChars !! (x `mod` modul)):y)

representate x y | (y <= 1) || (y >= 37) || (x < 0)  = undefined
                 | x == 0                            = "0"
                 | otherwise                         = rep x y ""
