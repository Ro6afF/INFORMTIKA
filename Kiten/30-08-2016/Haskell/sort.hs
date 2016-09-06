-- vim: et

quicksort [] = []
quicksort (x:xs) = (quicksort (filter (<x) xs)) ++ [x] ++ (quicksort(filter (>=x) xs))
