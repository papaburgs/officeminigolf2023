# Office Mini golf ball dispenser
For the hole design, we want to try to have an automated system to deploy balls.
Plan to have a keycode system, where if a good pin is entered, the ball gets released somewhere
which makes the hole easy to complete (Happy place). If a bad pin is entered, or no pin, 
the ball gets dropped somewhere which makes the hole harder to complete.

## Logical layout

## Components to be built
1. Ball storage and release mechanism
    * store balls and release one when instructed (ie, push the '#' button on the keypad)
    * was going to try a plunger/electromagnet method, but think a servo/stepper motor method is more consistent
    * the Arduino will watch for a signal from the keypad and spin a stepper motor which will push out a ball
    * the ball will continue down a ramp to a decision point.
2. Decision Point
    * similar to a train switch, or pinball bumper gate
    * If the code is entered correctly, the 'happy' path is opened for a set amount of time.
    * Any balls dispatched at that time will go to the happy place
    * after the set amount of time, the gate closes again so balls go to the normal position.
3. Keypad
    * used to enter a pin and dispatch balls
4. Display
    * a 4 digit display
    * can show a number to be used to determine the pin
    * can show status (like show 4 dashes to denote happy path is open)


## What's next
See issues for what needs to be done
    







