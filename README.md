# Autonomous-Submarine

### [YouTube Demonstration](https://youtube.com/shorts/z_gIspJPBr0?feature=share) 

<h2>Description</h2>
The goal of this project was to create a submarine that would submerge a few feet underwater (around 4-6 feet), and be able to move, steer, navigate to avoid obstacles, and control depth. I chose to use 4" PVC pipe for the hull because I had lots of it lying around, with 3D printed endcaps that held the motors and sensors. The 3D printed endcaps were coated with a rubberized sealant spray and sealed to the main hull with mechanical rubber I designed a system to magnetically drive the propellers through the hull wall using neodymium magnets, ceramic bearings, and custom 3D printed parts. The sub detected its depth and surroundings using 3 sonar sensors mounted on the front in a custom 3D-printed nose cone. I integrated the bottom sonar sensor with C/C++ programming on an Arduino to control a linear actuator driven piston ballast system (syringe). This allowed the sub to dynamically let in water or push water out to sink or float depending on its distance from the bottom of my pool. I used 2 more sonar sensors pointing straight out mounted at 45 degree angles from the center-line to detect obstacles. I used a 5-sample median filter for all sensor values so the sub wouldn't make decisions based on bad values. For the navigation, I programmed the sub to detect distance from the wall of my circular pool, and then differentially steer to avoid it based on the angle of attack of the sub. All motors, actuators, and sensors were powered by a 3S LiPo battery. The Arduino 2560, which controlled everything with C/C++ programming, was powered by a separate 9V battery pack.
<br><br>
<h2>Sensors and Electronics Used</h2>

- <b>Arduino Mega 2560</b>
- <b>3S LiPo battery </b>
- <b>9 Volt battery</b>
- <b>2 L298N motor controllers</b>
- <b>2 300rpm geared DC motors</b>
- <b>linear actuator</b>
- <b>3 SE0599 Underwater Ultrasonic Sensors from DFRobotics</b>
- <b>30 Amp 48V Power distribution module</b>


<h2>Challenges and Solutions</h2>

One of the biggest challenges in this project was the design of the back endcap that houses the motors and the coupling for the magnetic drive. My first iteration had the magnets touching the wall of the 3D print. This caused a lot of power loss, and after only a few short tests, there was a noticeably groove being worn into the print. Obviously, if it eventually wore a hole in the wall underwater that would be very bad. So to fix this, I changed the design of the coupling to include a ceramic bearing with a ≈1mm spacer on the outside. I also narrowed the diameter of the tube inside of the endcap so the motor would sit ≈1mm away from the inside wall. This would work temporarily, but since the inside motor assembly pieces were mostly friction held, the magnets were so strong that they would eventually pull themselves to the wall. I tried to make the friction hold of the magnet holder on the motor shaft stronger with tape, but eventually last-resorted to super-glueing it to the motor shaft. Then the magnets started pulling the motor out of its holder. I tried lots of tape, but I did not want to superglue the motor to its holder. So I decided to print a 1mm spacer to slightly increase the distance between the magnets, and therefore slightly weaken their connection. This solved the problem, and the cost of slightly decreased max torque was not an issue in the water. Check out
**[this short video](https://youtube.com/shorts/z_gIspJPBr0?feature=share)**
demonstrating the different stages:



<p align="center">
  Here is a demonstration of the final assembly:<br/>
<img width="600" height="359" alt="explode1" src="https://github.com/user-attachments/assets/14c8bd97-386f-46fd-b1bc-e9a25371622d" />





