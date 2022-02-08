/**
* Application Purpose: Duel Motor Sun Tracker; Applications in 
					   Solar Energy Maximization
* Author: Shashank Iyer
* Date: 13 December 2021
* Time: 14:00hrs
*/

//Loading Display Library
#include <LiquidCrystal.h> 
//Loading Servo Library
#include <Servo.h>

//Adding our variable
Servo servo1;//Our horizontal servo
Servo servo2;//Our vertical servo
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);//Our screen input pins

//Our setup method
void setup() {

  lcd.begin(16,2); //Setting initial position
  
  //Printing out the name that will 
  //resemble horizontal servo position
  lcd.print("Servo1 ");
  
  //Setting the position to bottom left
  lcd.setCursor(0,1);
  //Printing out the name that will 
  //resemble vertical servo position
  lcd.print("Servo2 ");
  servo1.attach(9);//vertical servo pin is attached to UNO
  servo2.attach(10);//horizontal servo pin is attacked to UNO

  //Setting the position of both the motors
  servo1.write(90); 
  servo2.write(90); 
}

//Our main method that loops infinitely 
void loop(){

  /** 
  * Adding our photoresistor sensor variables and pins 
  * they are attached to.
  * Naming pins from left to right
  */
  int sensorOne = analogRead(A3);
  int sensorTwo = analogRead(A1);
  int sensorThree = analogRead(A4);
  int sensorFour = analogRead(A0);
  
  /**
  * Creating 4 average variables for the sensor inputs
  * this basically estimates the position of the sun in all 
  * directions
  */
  int avgTop=(sensorTwo+sensorFour)/2;
  int avgBottom=(sensorOne+sensorThree)/2;
  int avgLeft=(sensorOne+sensorTwo)/2;
  int avgRight=(sensorThree+sensorFour)/2;

  
  //If else loop that checks for the average value of the sensors
  if(avgBottom > avgTop) 
  {
    //It will run the method UpDown on the sensors
    UpDown(sensorThree, sensorFour);
  }
  if(avgBottom < avgTop) 
  {
    UpDown(sensorThree, sensorFour);
  }
  if (avgLeft > avgRight)
  {
    //It will run the method LeftRight on the sensors
    LeftRight(sensorOne, sensorTwo);
  }
  if(avgLeft < avgRight)
  {
    LeftRight(sensorOne, sensorTwo);
  }
 
  delay(10);//Add delay by 10ms
}


//These are my two methods that will help change the
//position of the two motors

//LeftRight method that changes the position of the horizontal
//motor based on the sensor inputs
void LeftRight(int avgLeft, int avgRight){
  int pos1= servo1.read();//Reads the value of servo1
  
  //if loop that determines whether the position is increased by
  //1 or reduced by 1 =  input of the sensor
  
  //if the average on left sensors is less than right ones
  //than turn the motor towards the right
  if(avgLeft < avgRight){
    pos1 = --pos1; 
  }
  else//turn it left
  {
    pos1 = ++pos1;
  }
  //Set the position of the horizontal motor
  servo1.write(pos1);
  //move the cursor
  lcd.setCursor(12,0);
  //print the postion value
  lcd.print(pos1);
}

//LeftRight method that changes the position of the vertical
//motor based on the sensor inputs
void UpDown(int avgBottom, int avgTop){
  int pos2= servo2.read();//read the motor position
  
  //if loop that determines whether the position is increased by
  //1 or reduced by 1 =  input of the sensor
  
  //if the average on the top is greater than the bottom
  if(avgBottom < avgTop)
  { 
    pos2 = --pos2;//move towards the top
  }
  else//else bottom
  {
    pos2 = pos2 + 1;
  }
  //Set the new position of the motor
  servo2.write(pos2);
  //Move the cursor
  lcd.setCursor(12,1);
  //Print the position value
  lcd.print(pos2);
}
