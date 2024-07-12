# SysiphusSort
- Sysiphus Sort is an homage to the ancient myth of Sysiphus<br>
- This code is a bubble sort, excpet every swap the number has a chance to fall back down<br>
- the chance to fall grows with respect to where the current number is in the array
- Written by Jake Spaulding 2024 for the cs50 create task
- takes 4 args or can be run without any to use a defualt template:
## the args are:
  1: the type of array (user, rev, rand, rand_inc)<br>
  2: a positve int to define the size of the array <br>
  3: a positve int to define the maximum probability of the fall (out of 100)<br>
  4: the type of probability growth (lin, log, const)<br>

### ex: 
"./SysiphysSort rand 10 15 log"
- this would have it generate an array of 10 numbers randomly,
- the chance to fall will grow logarithmicly with respect to the position of the current number in the array, 
- the chance to fall would reach a maximum of 15/100

## purpose
I designed this code as a project for class, but also as an expression of what it means to attempt an intractable task.
I designed it, with my limited understanding of programming, to be modifiable and modular.
That is to say -have at it! 
My goal was to make Sysiphus Sort something anybody could mold into their own vision, to make it something anybody can adapt in hopes that some day it might become bigger than just my litle project, rather become a product of the programming community
