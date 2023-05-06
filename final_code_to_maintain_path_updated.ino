#include <AFMotor.h>   //LIBRARY USED FOR ARDUINO MOTOR SHIELD TO RUN THE MOTORS.
#include <LiquidCrystal_I2C.h> // LIBRARY FOR DISPLAY WITH I2C MODULE

LiquidCrystal_I2C lcd(0x27, 16, 2);

int buzzer = 2;                 // buzzer pin

const int trigPin = A0;         // front sensor
const int echoPin = A1;

const int trigPinR = A2;        // right sensor
const int echoPinR = A3;

const int trigPinL=9;           // left sensor using servo pins
const int echoPinL=10;

//const int trigPinL = A4;       // left sensor
//const int echoPinL = A5;


AF_DCMotor motor1(1);           // for steering
AF_DCMotor motor2(2);           // for back motor rotation
AF_DCMotor motor3(3);           // for front motor rotation

void setup()
{
  lcd.init();                 // initialize the lcd
  lcd.backlight();

  pinMode(buzzer, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(trigPinL, OUTPUT);
  pinMode(echoPinL, INPUT);

  pinMode(trigPinR, OUTPUT);
  pinMode(echoPinR, INPUT);
}


void loop() 
{ 
  
int distanceCm = getDistance();

if(distanceCm>45)                      // checking the front sensor distance
{ 
    lcd.clear();                     // CLEAR THE DISPLAY
    lcd.setCursor(0,0);              // SETTING THE CURSOR AT STARTING POSITION
    lcd.print("No ObjectInRange");   // PRINTING THE STRING
    
    
  motor2.setSpeed(85);                
  motor2.run(FORWARD);                 // move forward


  motor3.setSpeed(75);
  motor3.run(FORWARD);
  
  
}
else
{
    lcd.clear();                     // CLEAR THE DISPLAY
    lcd.setCursor(0,0);              // SETTING THE CURSOR AT STARTING POSITION
    lcd.print("There is an ObjectInRange");

    lcd.print("at ");
    lcd.setCursor(5,1);              // set cursor to 5th col 2nd row
    lcd.print(distanceCm);
    lcd.print(" cm");


                            
    
    
    motor2.run(RELEASE);              // any object within the 45cm then stop the car
    motor3.run(RELEASE);
  
    motor2.setSpeed(95);  
    motor2.run(BACKWARD);
  
  
    motor3.setSpeed(100);
    motor3.run(BACKWARD);
  
    delay(200);
  
     motor2.run(RELEASE);
    motor3.run(RELEASE);
  
    delay(1000);                                //to understand the process
  
      digitalWrite(buzzer,HIGH);
   delay(250);
   digitalWrite(buzzer,LOW);
   delay(250);
    digitalWrite(buzzer,HIGH);
   delay(250);
   digitalWrite(buzzer,LOW);
   delay(250);                                     // blow horn 

  int LeftDistance=getLeftDistance();        // calling left ultrasonic fn and storing its distance in var
  int RightDistance=getRightDistance();      // calling right ultrasonic fn and storing its distance in var

  
  if(LeftDistance>30)
  {

     lcd.clear();                     // CLEAR THE DISPLAY
    lcd.setCursor(0,0);              // SETTING THE CURSOR AT STARTING POSITION
    lcd.print("Path is clear!");
    
     motor2.setSpeed(80);                   // move backward for half sec
     motor2.run(BACKWARD);
     motor3.setSpeed(80);
     motor3.run(BACKWARD);
     delay(500);
     
     motor2.run(RELEASE);
     motor3.run(RELEASE);

     delay(1000);                          //to understand the process
     
          

     motor1.setSpeed(150);                // turn left and move for 1 sec
     motor1.run(BACKWARD);

     motor2.setSpeed(80);                
     motor2.run(FORWARD);
     motor3.setSpeed(80);
     motor3.run(FORWARD);
     delay(1000);                       

     motor2.run(RELEASE);              // stop
     motor3.run(RELEASE);
     
     motor1.setSpeed(0);               // carrying back steering to its zero/ initial position
     motor1.run(RELEASE);

     motor1.setSpeed(150);            // turn right and move for 1050 micro sec
     motor1.run(FORWARD);

     motor2.setSpeed(80);   
     motor2.run(FORWARD);
     motor3.setSpeed(80);
     motor3.run(FORWARD);   
     delay(1050);           

     motor1.setSpeed(0);             // stop
     motor1.run(RELEASE);  

     

     motor1.setSpeed(150);          // again turn left and move for 400 microsec to maintain its path
     motor1.run(BACKWARD);
     motor2.setSpeed(80);   
     motor2.run(FORWARD);
     motor3.setSpeed(80);
     motor3.run(FORWARD);

     delay(400);

   
     motor1.setSpeed(0);           // carrying back steering to its zero/ initial position 
     motor1.run(RELEASE);
      
     
     
    }




  else if(RightDistance>30)
  {
    
      lcd.clear();                     // CLEAR THE DISPLAY
      lcd.setCursor(0,0);              // SETTING THE CURSOR AT STARTING POSITION
      lcd.print("Path is clear !");
    
     motor2.setSpeed(80);                            // move backward for 500micro sec
     motor2.run(BACKWARD);
     motor3.setSpeed(80);
     motor3.run(BACKWARD);
     delay(500);
     
     motor2.run(RELEASE);
     motor3.run(RELEASE);

     delay(1000);                                   //to understand the process
     
          

     motor1.setSpeed(150);                         // turn right and move forward for 1000microsec
     motor1.run(FORWARD);

     motor2.setSpeed(80);   
     motor2.run(FORWARD);
     motor3.setSpeed(80);
     motor3.run(FORWARD);
     delay(1000);                                  

     motor2.run(RELEASE);
     motor3.run(RELEASE);
     
     motor1.setSpeed(0);                           // carrying back to steering to its zero/ initial position
     motor1.run(RELEASE);

     motor1.setSpeed(150);                        // turn left and move forward for 1050 microsec
     motor1.run(BACKWARD);

     motor2.setSpeed(80);   
     motor2.run(FORWARD);
     motor3.setSpeed(80);
     motor3.run(FORWARD);
     delay(1050);           
     
     motor1.setSpeed(0);                          // carrying back steering to its zero/ initial position
     motor1.run(RELEASE);   



     motor1.setSpeed(150);                        // again turn right and move for 400 microsec to maintain its path
     motor1.run(FORWARD);
     motor2.setSpeed(80);   
     motor2.run(FORWARD);
     motor3.setSpeed(80);
     motor3.run(FORWARD);

     delay(400);

   
     motor1.setSpeed(0);                           // carrying back to steering to its zero/ initial position
     motor1.run(RELEASE); 
     
    }
  else
    { 
     
     while(distanceCm < 45)                     //Keep checking the object distance until it is within the minimum stopping distance
      { 

       
        
        delay(1000);
        distanceCm = getDistance();

        motor2.run(RELEASE);
        motor3.run(RELEASE);

        lcd.clear();                     // CLEAR THE DISPLAY
        lcd.setCursor(0,0);              // SETTING THE CURSOR AT STARTING POSITION
        lcd.print("There is an Object");

        lcd.print("at ");
        lcd.setCursor(5,1);              // set cursor to 5th col 2nd row
        lcd.print(distanceCm);
        lcd.print(" cm");


    
     }

   }

 }
}

int getDistance()                                   //Measure the distance to an object for front sensor
{
   long duration;
   int distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);//Create a variable to store the calculated distance
  digitalWrite(trigPin, HIGH);                         //Generate a 10 microsecond pulse
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance= duration*0.034/2;    //Calculate the object distance based on the pulse time
  return distance;

  
}

int getLeftDistance()                                   //Measure the distance to left object for left sensor
{
   long duration1;
   int distance1;
  digitalWrite(trigPinL, LOW);
  delayMicroseconds(2);                                 //Create a variable to store the calculated distance
  digitalWrite(trigPinL, HIGH);                         //Generate a 10 microsecond pulse
  delayMicroseconds(10);
  digitalWrite(trigPinL, LOW);
  duration1 = pulseIn(echoPinL, HIGH);
  distance1= duration1*0.034/2;                         //Calculate the object distance based on the pulse time
  return distance1;

  
}

int getRightDistance()                                   //Measure the distance to right object for right sensor
{
   long duration2;
   int distance2;
  digitalWrite(trigPinR, LOW);
  delayMicroseconds(2);                                 //Create a variable to store the calculated distance
  digitalWrite(trigPinR, HIGH);                         //Generate a 10 microsecond pulse
  delayMicroseconds(10);
  digitalWrite(trigPinR, LOW);
  duration2 = pulseIn(echoPinR, HIGH);
  distance2= duration2*0.034/2;                        //Calculate the object distance based on the pulse time
  return distance2;

  
}
