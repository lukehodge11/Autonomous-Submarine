int balin1 = 34, balin2 = 35, balpwm = 6; //pins for L298n that controlls actuator
int lmotorin1 = 26, lmotorin2 = 27, lmotorpwm = 4; //pins for L298n that controlls motors
int rmotorin1 = 28, rmotorin2 = 29, rmotorpwm = 5; //pins for L298n that controlls motors
float depth, left, right; // variables to store sensor data


void setup() { 
 //delay(45000); // delay 45 seconds so I can wrap and seal the end of the arduino cable and put the sub in the water
 //while(1){}; // infinite loop for disabling the sub during testing
  pinMode(balpwm, OUTPUT); // actuator controller pin settings
  pinMode(balin1, OUTPUT); // actuator controller pin settings
  pinMode(balin2, OUTPUT); // actuator controller pin settings

  pinMode(lmotorin1, OUTPUT);// motor controller pin settings
  pinMode(lmotorin2, OUTPUT);// motor controller pin settings
  pinMode(lmotorpwm, OUTPUT);// motor controller pin settings
  pinMode(rmotorin1, OUTPUT);// motor controller pin settings
  pinMode(rmotorin2, OUTPUT);// motor controller pin settings
  pinMode(rmotorpwm, OUTPUT);// motor controller pin settings

  Serial.begin(115200); // begin serial monitor for testing
  Serial3.begin(115200); // begin serial port to communicate with sensors
  Serial2.begin(115200); // begin serial port to communicate with sensors
  Serial1.begin(115200); // begin serial port to communicate with sensors

  start(); // set all motors to 0 to start
  resetbal(); // push the syringe all the way out 

}

void loop() { 
  while(1){}; //infinite loop for testing

  depth = readDepth(); // read depth sensor and store value in variable
  left = readLeft(); // read left sensor and store value
  right = readRight(); // read right sensor and store value

if (right == 0) { // if the right reads 0, its most likely because its pointed very angled at the pool wall, not because something is close 
  right = 1000; // so it actually needs to be a high value, that way 0 doesnt mess up turning logic
}
if (left == 0) { // if the left reads 0, its most likely because the its pointed very angled at the pool wall, not because something is close 
  left = 1000; // so it actually needs to be a high value, that way 0 doesnt mess up turning logic
}

 if(left < 90 && left < right){ // if the left sensor reads less than 90 cm, and the left is closer to the wall than the right
    goRight();// turn right
  }

  else if(right < 90 && right < left){ // if the right sensor reads less than 90 cm, and the right is closer to the wall than the left
    goLeft();// turn left
  }

  else if(left < 60 && right < 60){ // if both read less than 60 cm
    goReverse();//put it in reverse
  }

  else goStraight(); // otherwise, go straight
  


  if(readDepth() < 30 && readDepth() != 0){ // if the sub is higher than 30 cm off the ground, excluding 0 again
    swim(); // float up
  }

  if(readDepth() > 90 && readDepth() < 160){ // if the sub is higher than 90 cm off the bottom, but not a very high, garbage value, which sometimes happens
    sink(); // then sink
  }
   

delay(50); // delay 50 ms
}



void extend(float t){ // extend the syringe plunger (push water out)
  digitalWrite(balin1, HIGH); // set direction
  digitalWrite(balin2, LOW); // set direction
  analogWrite(balpwm, 255);// turn on actuator
  delay(t * 1000);//delay for t * 1000 seconds, so i can pass in any number and it will extend for that many seconds

  analogWrite(balpwm, 0); // turn off actuator
  delay(500); // delay for half a second
}

void retract(float t){ // retract the syringe (let water in)
  digitalWrite(balin1, LOW); // set direction
  digitalWrite(balin2, HIGH); // set direction
  analogWrite(balpwm, 255); // turn on actuator
  delay(t* 1000); //delay for t * 1000 seconds, so i can pass in any number and it will extend for that many seconds

  analogWrite(balpwm, 0); // turn off actuator
  delay(500); // delay half a second
}

void sink(){ //let water in to increase weight so the sub will sink
  retract(5); // let water in for 5 seconds to become negatively boyant
  delay(3000); //keep sinking for 3 seconds
  extend(5); // push the water back out so i dont keep sinking
}

void swim(){ // float up 
  extend(6); // push water out for 6 seconds
  delay(3000); // keep floating for 3 seconds
  retract(6); // let water back in for 6 seconds
}

void resetbal(){//set ballast back to the middle
  extend(10); // by pushing it all the way out 
  retract(6.5); // and then pulling it back to the middle
}

void start(){ // set all motors to 0 at startup
  digitalWrite(lmotorin1, HIGH); //set direction
  digitalWrite(lmotorin2, LOW); //set direction
  analogWrite(lmotorpwm, 0); // set motor speed to 0

  digitalWrite(rmotorin1, HIGH); //set direction
  digitalWrite(rmotorin2, LOW); //set direction
  analogWrite(rmotorpwm, 0); // set motor speed to 0

  delay(1500); // delay 1 and a half seconds
}

void goLeft(){ // turn left 
  digitalWrite(lmotorin2, HIGH); //set direction
  digitalWrite(lmotorin1, LOW); //set direction
  analogWrite(lmotorpwm, 255); // set left motor high

  digitalWrite(rmotorin1, HIGH); //set direction
  digitalWrite(rmotorin2, LOW); //set direction
  analogWrite(rmotorpwm, 0); // turn off right motor
  delay(5000); // turn for 5 seconds

  analogWrite(lmotorpwm, 0); // turn off left motor
}

void goRight(){
  digitalWrite(lmotorin2, HIGH); //set direction
  digitalWrite(lmotorin1, LOW); //set direction
  analogWrite(lmotorpwm, 0); // turn off left motor

  digitalWrite(rmotorin1, HIGH); //set direction
  digitalWrite(rmotorin2, LOW); //set direction
  analogWrite(rmotorpwm, 255); // set right motor high
  delay(6000); // turn for 6 seconds, it turns right slightly slower 

  analogWrite(rmotorpwm, 0); // turn right motor off
}

void goStraight(){ // go straight
  digitalWrite(lmotorin2, HIGH); //set direction
  digitalWrite(lmotorin1, LOW); //set direction
  analogWrite(lmotorpwm, 240); // set left motor slightly lower than right motor, because it turns slightly faster

  digitalWrite(rmotorin1, HIGH); //set direction
  digitalWrite(rmotorin2, LOW); //set direction
   analogWrite(rmotorpwm, 255); // set right motor high
  delay(3000); // go straight for 3 seconds

  analogWrite(lmotorpwm, 0); // turn both motors off
  analogWrite(rmotorpwm, 0); // turn both motors off
}

void goReverse(){ // go in reverse
  digitalWrite(lmotorin2, LOW); //set direction
  digitalWrite(lmotorin1, HIGH); //set direction
  analogWrite(lmotorpwm, 240); // set left motor speed

  digitalWrite(rmotorin1, LOW); //set direction
  digitalWrite(rmotorin2, HIGH); //set direction
  analogWrite(rmotorpwm, 255); // set right motor speed
  delay(5000); // go in reverse for 5 seconds

  analogWrite(lmotorpwm, 0); // turn left motor off
  analogWrite(rmotorpwm, 0); // turn right motor off
}

float readDepth(){ // read depth sensor

int header = 0; // first byte that the sensor will send
int high = 0; // second byte. Since the sensor can read up to 6m, and it sends the distance in mm, it has to break up the distance into 2 bytes. This is the high byte
int low = 0; // third byte, low byte
int checksum = 0; // last byte. The sensor sends a sum of the first 3 bytes, with the hope that I will add them up myself, and confirm that our sums are the same, therefore the data came through correctly. 
float distance = 0; // variable for distance
float temp; // temp variable for swap
int i = 0, j; // i and j for sorting loops
float median[5] = {0}; // array to store values in so i can sort them and find the median. This is supposed to filter out bad values by finding the median of 5 readings.

while(i < 5){ //read 5 distances
  while(Serial3.available() > 0) //if there are old bytes waiting in the serial register
    Serial3.read(); // read them all to get rid of them. When I ask the sensor for data, it sends 4 bytes and I check to make sure the first is the header byte. If it isn't then it skips over the rest and the loop runs again. So I have to clear out the old ones, before I ask for more.

  Serial3.write(85);// send 0x55 to the sensor, or 85 in decimal, which tells it to send values
  delay(100); // wait 100 ms

  if(Serial3.available() > 0){ // if the serial register has data in it
    delay(4); // wait 4 ms for the rest to arrive

    if(Serial3.read() == 255){ // if the first byte is the header
      header = 255; // assign 255 to header 
      while(Serial3.available() == 0) {}; // if the next byte isnt there already, wait on it
      high = Serial3.read(); // read the high byte
      while(Serial3.available() == 0) {}; // if the next byte isnt there already, wait on it
      low = Serial3.read(); // read the low byte
      while(Serial3.available() == 0) {}; // if the next byte isnt there already, wait on it
      checksum = Serial3.read(); // read the checksum
    
  
      if(checksum == ((header + high + low) % 256)){ // i do the same math the sensor did, and if our checksums are equal
        median[i] = ((high * 256) + low) / 10.0; // make the high byte high by multiplying by 256, and add the low byte, then divide by 10 to convert to centimeters. Store it in the array to be sorted
        i++; // update i, i only updates if i get a distance reading
      }
    }
  }
  }
  for(j = 0; j < 5; j++){ //bubble sort, do the next part 5 times
     for(i = 0; i < 4; i++){ // go through the array and sort
       if(median[i] > median[i + 1]){ // if the first value is greater than the second value, then swap them
        temp = median[i]; // swap by putting the first value into temp
       median[i] = median[i + 1]; // the second value into the first value
       median[i + 1] = temp; // and the first value, which is in temp, into the second value
       }
       
      }
  }
  return median[2]; // return the middle value in the array 
}

float readRight(){//read right sensor, same code as before except with Serial2

int header = 0; // first byte that the sensor will send
int high = 0; // second byte. Since the sensor can read up to 6m, and it sends the distance in mm, it has to break up the distance into 2 bytes. This is the high byte
int low = 0; // third byte, low byte
int checksum = 0; // last byte. The sensor sends a sum of the first 3 bytes, with the hope that I will add them up myself, and confirm that our sums are the same, therefore the data came through correctly. 
float distance = 0; // variable for distance
float temp; // temp variable for swap
int i = 0, j; // i and j for sorting loops
float median[5] = {0}; // array to store values in so i can sort them and find the median. This is supposed to filter out bad values by finding the median of 5 readings.

while(i < 5){ //read 5 distances
  while(Serial2.available() > 0) //if there are old bytes waiting in the serial register
    Serial2.read(); // read them all to get rid of them. When I ask the sensor for data, it sends 4 bytes and I check to make sure the first is the header byte. If it isn't then it skips over the rest and the loop runs again. So I have to clear out the old ones, before I ask for more.

  Serial2.write(85);// send 0x55 to the sensor, or 85 in decimal, which tells it to send values
  delay(100); // wait 100 ms

  if(Serial2.available() > 0){ // if the serial register has data in it
    delay(4); // wait 4 ms for the rest to arrive

    if(Serial2.read() == 255){ // if the first byte is the header
      header = 255; // assign 255 to header 
      while(Serial2.available() == 0) {}; // if the next byte isnt there already, wait on it
      high = Serial2.read(); // read the high byte
      while(Serial2.available() == 0) {}; // if the next byte isnt there already, wait on it
      low = Serial2.read(); // read the low byte
      while(Serial2.available() == 0) {}; // if the next byte isnt there already, wait on it
      checksum = Serial2.read(); // read the checksum
    
  
      if(checksum == ((header + high + low) % 256)){ // i do the same math the sensor did, and if our checksums are equal
        median[i] = ((high * 256) + low) / 10.0; // make the high byte high by multiplying by 256, and add the low byte, then divide by 10 to convert to centimeters. Store it in the array to be sorted
        i++; // update i
      }
    }
  }
  }
  for(j = 0; j < 5; j++){ //bubble sort, do the next part 5 times
     for(i = 0; i < 4; i++){ // go through the array and sort
       if(median[i] > median[i + 1]){ // if the first value is greater than the second value, then swap them
        temp = median[i]; // swap by putting the first value into temp
       median[i] = median[i + 1]; // the second value into the first value
       median[i + 1] = temp; // and the first value, which is in temp, into the second value
       }
       
      }
  }
  return median[2]; // return the middle value in the array 
}

float readLeft(){// read left sensor, same thing just with Serial1

int header = 0; // first byte that the sensor will send
int high = 0; // second byte. Since the sensor can read up to 6m, and it sends the distance in mm, it has to break up the distance into 2 bytes. This is the high byte
int low = 0; // third byte, low byte
int checksum = 0; // last byte. The sensor sends a sum of the first 3 bytes, with the hope that I will add them up myself, and confirm that our sums are the same, therefore the data came through correctly. 
float distance = 0; // variable for distance
float temp; // temp variable for swap
int i = 0, j; // i and j for sorting loops
float median[5] = {0}; // array to store values in so i can sort them and find the median. This is supposed to filter out bad values by finding the median of 5 readings.

while(i < 5){ //read 5 distances
  while(Serial1.available() > 0) //if there are old bytes waiting in the serial register
    Serial1.read(); // read them all to get rid of them. When I ask the sensor for data, it sends 4 bytes and I check to make sure the first is the header byte. If it isn't then it skips over the rest and the loop runs again. So I have to clear out the old ones, before I ask for more.

  Serial1.write(85);// send 0x55 to the sensor, or 85 in decimal, which tells it to send values
  delay(100); // wait 100 ms

  if(Serial1.available() > 0){ // if the serial register has data in it
    delay(4); // wait 4 ms for the rest to arrive

    if(Serial1.read() == 255){ // if the first byte is the header
      header = 255; // assign 255 to header 
      while(Serial1.available() == 0) {}; // if the next byte isnt there already, wait on it
      high = Serial1.read(); // read the high byte
      while(Serial1.available() == 0) {}; // if the next byte isnt there already, wait on it
      low = Serial1.read(); // read the low byte
      while(Serial1.available() == 0) {}; // if the next byte isnt there already, wait on it
      checksum = Serial1.read(); // read the checksum
    
  
      if(checksum == ((header + high + low) % 256)){ // i do the same math the sensor did, and if our checksums are equal
        median[i] = ((high * 256) + low) / 10.0; // make the high byte high by multiplying by 256, and add the low byte, then divide by 10 to convert to centimeters. Store it in the array to be sorted
        i++; // update i
      }
    }
  }
  }
  for(j = 0; j < 5; j++){ //bubble sort, do the next part 5 times
     for(i = 0; i < 4; i++){ // go through the array and sort
       if(median[i] > median[i + 1]){ // if the first value is greater than the second value, then swap them
        temp = median[i]; // swap by putting the first value into temp
       median[i] = median[i + 1]; // the second value into the first value
       median[i + 1] = temp; // and the first value, which is in temp, into the second value
       }
       
      }
  }
  return median[2]; // return the middle value in the array 
}

