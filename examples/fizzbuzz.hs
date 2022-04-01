{-

	FIZZBUZZ in Haskell

-}


fizzes = cycle ["", "", "Fizz"]
buzzes = cycle ["", "", "", "", "Buzz"]
words = zipWith (++) fizzes buzzes
numbers = map show [1...]
choice = max
fizzbuzz = zipWith choice words numbers

take 100 fizzbuzz

