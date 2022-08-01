This code starts with 5 and 7 in cells #1 and #2 and then multiplies
and prints the result (35 which is ascii code for '#')
+++++>+++++++< input numbers at cell #1 #2
[
 > go to cell #2
 [
   ->+>+<< move data to cell #3 #4
 ]
 >> go to cell #4
 [
  -<<+>> move data to cell #2
 ]
 <<< go to cell #1
 - decrement cell #1
]
>>. print the result in cell 3