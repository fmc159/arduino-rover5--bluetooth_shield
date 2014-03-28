// Simple Dagu Rover 5 coontroller demo using Arduino UNO 
// + Bluetooth shield (Seeeduino) 
// Controlled through serial commands

// Author: Fergus McCorkell
// Date: 26th March 2014

// NOTE Encoders and current readings are NOT used in this demo
// (just basic motor control)

// Once the sketch is uploaded, the Seeeduino bluetooth shield leds should flash red and green
// This means it is ready to connect and be used. If it is only flashing green, press the reset button
// on the arduino and hopefully it will start blinking the correct colours (if not, press reset again!)

// Read sketch comments to get an understanding. The easiest way to send serial commands
// is to use the serial monitor built in to the Arduino IDE. Once the sketch is uploaded,
// Go to Tools > Serial Port then select your bluetooth shield (in my case this is:
// /dev/tty.SeeedBtSlave-DevB). Then go to Tools > Serial Monitor. From here you can type 
// characters to control the Rover.

// An alternative to the built in serial monitor on a mac or linux is to open Terminal and use
// the screen command. Eg. screen /dev/tty.SeeedBtSlave-DevB

// Sketch can easily be changed to use USB serial, as opposed to the bluetooth shield serial.

#include <SoftwareSerial.h>   // Software Serial Port

// Define the Arduino UNO pins for motor and direction control of that motor
// I am using all 4 motors (which my rover 5 has, some models have only 2)

#define MOTOR1 10 // Motor pins need to be PWM pins
#define DIRECTION1 12 // Direction pin should be any digital pin

#define MOTOR2 11
#define DIRECTION2 8

#define MOTOR3 3
#define DIRECTION3 2

#define MOTOR4 5
#define DIRECTION4 4

// These are Transmit and Receive pins used by the Bluetooth shield

#define RxD 6
#define TxD 7

// Define a software serial connection, with the RxD and TxD pins

SoftwareSerial blueToothSerial(RxD,TxD);

void setup ()
{
  
 // Bluetooth shield setup
  
  pinMode(RxD, INPUT); // Setup Receive pin as input
  pinMode(TxD, OUTPUT); // Setup Transmit pin as output
  setupBlueToothConnection(); // Run this method (at the bottom of sketch)
  
 // These are not strictly necessary, but are good practice to ensure pins are in right mode
  pinMode (MOTOR1, OUTPUT);
  pinMode (DIRECTION1, OUTPUT);
  pinMode (MOTOR2, OUTPUT);
  pinMode (DIRECTION2, OUTPUT);
  pinMode (MOTOR3, OUTPUT);
  pinMode (DIRECTION3, OUTPUT);
  pinMode (MOTOR4, OUTPUT);
  pinMode (DIRECTION4, OUTPUT);
  

}  // end of setup


void loop ()
{
  
   char recvChar; // Define a new char called 'recvChar'
    if(blueToothSerial.available()){//check if there's any data sent from the remote bluetooth shield
      recvChar = blueToothSerial.read(); // Read a char typed by you in a serial session and 
      blueToothSerial.print(recvChar); // Prints the char in serial just to give you visual confirmation
      
      //This simple if statement checks to see if the char was either 'W' 'A' 'S' 'D' and then sets
      // the motor direction (and speed) based on the char.
      // If the char is anything but W A S D, the motors are set to '0' (ie they stop)
      
        if(recvChar == 's'){
          digitalWrite (DIRECTION1, 0);
          digitalWrite (DIRECTION2, 0);
          digitalWrite (DIRECTION3, 1);
          digitalWrite (DIRECTION4, 1);
          
          analogWrite (MOTOR1, 240); // The motor speed value can be between 0 and 255
          analogWrite (MOTOR2, 240);
          analogWrite (MOTOR3, 240);
          analogWrite (MOTOR4, 240);
        }
        
       else if(recvChar=='a'){
         digitalWrite (DIRECTION1, 1);
         digitalWrite (DIRECTION2, 0);
         digitalWrite (DIRECTION3, 0);
         digitalWrite (DIRECTION4, 1);
          
          
         analogWrite (MOTOR1,240);
         analogWrite (MOTOR2, 240);
         analogWrite (MOTOR3,240);
         analogWrite (MOTOR4, 240);
  
       }
       
       else if(recvChar=='d'){
         digitalWrite (DIRECTION1, 0);
         digitalWrite (DIRECTION2, 1);
         digitalWrite (DIRECTION3, 1);
         digitalWrite (DIRECTION4, 0);
          
         analogWrite (MOTOR1,240);
         analogWrite (MOTOR2, 240);
         analogWrite (MOTOR3,240);
         analogWrite (MOTOR4, 240);
       }
       
        else if(recvChar=='w'){
          digitalWrite (DIRECTION1, 1);
          digitalWrite (DIRECTION2, 1);
          digitalWrite (DIRECTION3, 0);
          digitalWrite (DIRECTION4, 0);
          
         analogWrite (MOTOR1,240);
         analogWrite (MOTOR2, 240);
         analogWrite (MOTOR3,240);
         analogWrite (MOTOR4, 240);
         
        }
        
        else{
        analogWrite (MOTOR1, 0);
         analogWrite (MOTOR2, 0); 
         analogWrite (MOTOR3, 0);
         analogWrite (MOTOR4, 0); 
        }     
  }
}


// This method taken from Seeeduino bluetooth shield example sketches, it will only apply to this particular shield!
void setupBlueToothConnection()
{
  blueToothSerial.begin(38400); //Set BaudRate to default - 38400
  blueToothSerial.print("\r\n+STWMOD=0\r\n"); // Set the bluetooth work in slave mode
  blueToothSerial.print("\r\n+STNA=SeeedBTSlave\r\n"); // Set the bluetooth name as "SeeedBTSlave"
  blueToothSerial.print("\r\n+STOAUT=1\r\n"); // Permit Paired device to connect
  blueToothSerial.print("\r\n+STAUTO=0\r\n"); // Auto-connection should be forbidden here
  delay(2000); // This delay is required.
  blueToothSerial.print("\r\n+INQ=1\r\n"); // Make the slave bluetooth inquirable 
  Serial.println("The slave bluetooth is inquirable!");
  blueToothSerial.print("The slave bluetooth is inquirable!");
  delay(2000); // This delay is required.
  blueToothSerial.flush();
}
