# Operation
The system is comprised of 2 parts. The control section is made of the display and the keypad. 
The motors section handles deploying of the ball and opening and closing the happy path gate.

### Keypad and Display
The keypad is a 4x4 matrix, that has a standard phone pad as well as 4 extra buttons labeled A through D.
The display is 16x2 character LCD. This will provide the seed value, which is a random number of 5-6 digits.

Use the keypad to enter the computed pin. If the pin is correct, the gate will open for 30 seconds. This allows multiple balls to 
be deployed with a single code.

Keys:  
- '*' 
    - reset entered pin, make a new seed pin and close gate
- '#' 
    - check entered pin, if it correct, the gate will open and a ball deployed.
    - if it incorrect, your ball is dispensed to the 'non-happy' path.
- 'D'
    - Dispense ball, regardless of where gate is. Can be used to try to get a few balls deployed for a group
- Numbers
    - enter pin
    
Normal operation:  
* hit the 'star' button to reset the seed
* compute the pin
* enter it with the keypad
* press D to deploy additional balls before the time runs out.

### Pin generation algorithm
* take the seed and divide it by 3
* multiply the result by 13
* swap each pair of numbers (starting from the left)
* pin will be the 4 least significant numbers.
