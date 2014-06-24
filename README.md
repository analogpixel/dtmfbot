dtmfbot
=======

This is my attempt to control a robot using my iphone without having to pay the $100 developer fee to apple. Instead of writing a native app, I wrote a webapp, that controls an arduino board via DTMF tones played through a javascript application on the phone.

I also got fancy and 3d printed a based that attaches to the spark fun Magician chassis which holds the iphone in place, and holds the arduino on top of that.

project page here: http://analogpixel.org/article/view/dtmfController

# Directories
## 3dmodel
contains the 3dpints of the base that attaches to the sparkfun redbot and houses
the iphone.
## arduinoCode
contains the code to decode the DTMF tones and drive the robot.
## webApp
contains the applications that talks to the iphone that drives the robot, and
contains the application that communicates to that.
