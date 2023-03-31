# tea-timer
A simple tea cooking robot implemented on Arduino Micro 

![Board schmeatics](https://github.com/rakoenig/tea-timer/raw/main/TeaTimerLoch_Steckplatine-1.png)

The wires on the left go to a 9V battery block. Then you have pin connectors for:

* On/off switch
* The servo that controls the arm of the robot
* A potentiometer that controls the time how long your tea bag should be in the tea
* A green LED for standby
* A red LED for showing that the program is running
* A push button to start the program

Once the program is started the arm goes down and the tea bag enters the tee. Then we lift it half way up for around 5 times. 
After that tea bag is in the tea and time measuring starts. When the time set on the potentiometer is over the bags are pulled 
out of the cup. Since time is calculated in every iteration you can easily cancel a running program by turning the potentimeter
knob to its left position (0 time). 

When the program is finished the timer beeps for 3 times and the LED goes back to green. 
