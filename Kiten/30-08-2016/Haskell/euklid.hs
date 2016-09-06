-- vim: et

evklid a b  | a == 0 = b
            | b == 0 = a
            | a < b  = evklid a (b `mod` a)
            | a > b  = evklid b (a `mod` b)
