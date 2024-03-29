# Manufacturing Consciousness
## Praggya Jeyakumar and Maxin Blinov
#### Performing Robots: IM-UH2117 Interactive Media Elective

**Link to performance video:**
['Manufacturing Consciousness' Video](https://drive.google.com/file/d/1gbxmSE6PLL_eIsrFjue3BnJgBO-sdiqA/view?usp=sharing)

### Overall project concept and description

A robot building a robot. The one being built mysteriously has consiousness while the builder is following protocol.
I will be working on this project with Max. The project requires two robots: a small one that is being 'constructed' in the play and another bigger robot that is constructing the smaller one. After meeting up to discuss the robot, we decided to split the work such that I work on the robot that gets built and Max works on the robotic arm that builds.

[Inspirations, Ideas and Concepts](https://github.com/PraggyaJ/Performing-Robots/blob/master/FinalProject/Ideation/inspirations%26ideas%26concepts.md)

[Entire final building process](https://github.com/PraggyaJ/Performing-Robots/blob/master/FinalProject/Building/Building_Progress.md)

### System diagram of the hardware
![](images/diagram.jpg)

### List of important parts (don’t include wires, resistors, etc.)
 - Arduino Uno
 - Adafruit Bluefruit LE UART Friend - Bluetooth Low Energy (BLE)
 - 2 high torque servos
 - 1 Neopixel strip
 - 1 16-LED Neopixel Ring
 - 2 Neopixel jewels
 - 1 powerbank
### Pictures of the electronics and props
Bluetooth breadeboarded:
![](images/blue.jpg)
Intial neopixels on face:
![](images/face_hard.jpg)
Neopixels on face after damaging neopixel ring and making a new one:
![](images/face_new.jpg)
Servos inside body:
![](images/servo_hard.jpg)


### Code (with good comments, good variable names, proper indentation, etc.)
[Code for the small robot](https://github.com/PraggyaJ/Performing-Robots/tree/master/FinalProject/Code(robot_being_built))

### Discuss 3-5 problems you ran into and how you resolved them or worked around them
#### Attachable hands:
The initial hands that I built used one magnet and hence, while they stuck to the servo, they did move as the weight of the hands were stronger than the slippery magnets.
Intial hands:
![](images/oldhands.jpg)
Intial robot with hands:
![](images/oldhand.jpg)
Final robot with hands:
![](images/newhand.jpg)



#### Damaged eye Neopixel ring
I damaged one of the neopixel rings and had to build one from scratch

![](images/n3.JPG)

![](images/n4.JPG)

![](images/n5.jpg)

#### Coding for a Neopixel Jewel
Max discovered that the Neopixel Jewel has 4 LEDs and had to be coded with RGBW not RGB.
#### Performance details
Small details of the performace were continously being added till last minute.
