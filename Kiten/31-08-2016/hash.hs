import Data.Char

a = 256

dohash [] = 1
dohash (x:xs) = (ord x) + a * dohash(xs)

hash x = hash (reverse x)

roll wat rem add size = wat - ((ord rem) * (a ^ (size - 1))) + (ord add)
