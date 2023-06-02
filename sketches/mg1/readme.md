# Algorithm design

## Setup
- reset seed timer

## Loop
- rotate seed if needed
- close gate if expire time is done
- wait for keypress
    - if '#' -> dispatch ball
    - if '*' -> reset-input
    - if a number -> call addDigit
        - updateDisplay
- if Pin matches -> open gate, set expire time for it


## Reset
- rotate seed
- empty buffer  

## addDigit
- multiply by 10 and add next digit
- if over 9999, subtract 10000

## updateDisplay
- separate each digit with integer division
- send each one to the display

## openGate
- move from closedGate to openGate position in steps

## closeGate
- move from openSate to closedGate position in steps

