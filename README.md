#SysiphysSort
- Sysiphus Sort is an homage to the ancient myth of Sysiphus
- This code is a bubble sort, excpet every swap the number has a chance to fall back down
- the chance to fall grows with respect to where the current number is in the array
- Written by Jake Spaulding 2024 for the cs50 create task
- takes 4 args or can be run without any to use a defualt template:
# # the args are:
  1: the type of array (user, rev, rand, rand_inc)
  2: a positve int to define the size of the array
  3: a positve int to define the maximum probability of the fall (out of 100)
  4: the type of probability growth (lin, log, const)

### ex: 
"./SysiphysSort rand 10 15 log"
- this would have it generate an array of 10 numbers randomly,
- the chance to fall will grow logarithmicly with respect to the position of the current number in the array, 
- the chance to fall would reach a maximum of 15/100
