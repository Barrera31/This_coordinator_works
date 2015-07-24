// Coordinator!
#include <Servo.h> 
#define rightMotor1 8
#define rightMotor2 7
#define leftMotor1 9
#define leftMotor2 10
int claw_ang=0;
int tilt_ang=15;
Servo claw;
Servo tilt;
Servo right;
Servo left;

void setup()
{
  claw.attach(5);
  tilt.attach(6);
  pinMode(rightMotor1, OUTPUT);
  pinMode(rightMotor2, OUTPUT);
  pinMode(leftMotor1, OUTPUT);
  pinMode(leftMotor2, OUTPUT);
  Serial.begin(9600);
  Serial1.begin(9600);
  right.attach (11);
  left.attach (10); 
}

void loop()
{

if (Serial1.available() >=5 ) {
   char incomingByte1 = Serial1.read();
   char incomingByte2 = Serial1.read(); 
   char incomingByte3 = Serial1.read();
   char incomingByte4 = Serial1.read();
   char incomingByte5 = Serial1.read();
   
   if(incomingByte1=='e'){  // if the first byte is an 'e' then we going to control the motors
   int val_1 = incomingByte2-'0';
   int val_2 = incomingByte3-'0';
   int val_3 = incomingByte4-'0';
   int val_4 = incomingByte5-'0';
    
    // For debugging
    Serial.println("Motor mode");
      Serial.println(val_1); 
      Serial.println(val_2); 
      Serial.println(val_3); 
      Serial.println(val_4); 
      Serial.println();
    
     
   //Drive forwards 
   if(val_1>0 && val_2==0 && val_3>0 && val_4>0 ){
    right.writeMicroseconds(1200);
    left.writeMicroseconds(1800);
    
   }
   //Drive backwards
   else if(val_1==0 && val_2>0 && val_3>0 && val_4>0){
    right.writeMicroseconds(1800);
    left.writeMicroseconds(1200); //1500 is for no movement //1700 is for forward
   }
   //Drive left
     else if(val_1>0 && val_2>0 && val_3>0 && val_4==0){
    right.writeMicroseconds(1200);  
    left.writeMicroseconds(1500);
     
   }
   //Drive right
      else if(val_1>0 && val_2>0 && val_3==0 && val_4>0){
    right.writeMicroseconds(1500);
    left.writeMicroseconds(1700);
   
   }
     
   else if (val_1>0 && val_2>0 && val_3>0 && val_4>0){
    right.writeMicroseconds(1500);
    left.writeMicroseconds(1500);
   }

  }
  
  else if (incomingByte1=='s'){ // if the first byte is 's' then we will control the robot arm
   int val_1 = incomingByte2-'0';  // val_1 corresponds to the thumb
   int val_2 = incomingByte3-'0';  // val_2 corresponds to index finger
   int val_3 = incomingByte4-'0';  // val_3 corresponds to the middle finger
   int val_4 = incomingByte5-'0';  // val_4 corresponds to the pinky
     
     //For debugging
     Serial.println("Robot arm mode");
      Serial.println(val_1); 
      Serial.println(val_2); 
      Serial.println(val_3); 
      Serial.println(val_4); 
      Serial.println();
     
    
    // Close claw
    if(val_1==0 && val_2==0 && val_3==0 && val_4==0){
     claw_ang-=5;  
     }
     // Open claw
     else if (val_1==0 && val_2>0 && val_3>0 && val_4>0){
     claw_ang+=5;  
     }
     // Tilt forward
     else if (val_1==0 && val_2>0 && val_3>0 && val_4==0){
     tilt_ang+=10;  
     }
     //Tilt backward
     else if (val_1==0 && val_2>0 && val_3==0 && val_4==0){
     tilt_ang-=10;  
     }
     
    if(claw_ang<0){
       claw_ang=0;
     }
    if (claw_ang>145){ 
       claw_ang=145;
     }
    if (tilt_ang<15){
      tilt_ang=15;
    }
    if(tilt_ang>180){
      tilt_ang=180;
    }
    
    // For debugging
    /* Serial.println("Claw angle:");   
    Serial.println(claw_ang);
    Serial.println();
    Serial.println("Tilt angle:");
    Serial.println(tilt_ang);
    Serial.println();
   */
   
    claw.write(claw_ang);
    delay(10);
    tilt.write(tilt_ang);
    delay(10);    
    
  }
  
  }

  
  else if (Serial.available() >=5) {
   char incomingByte1 = Serial.read();
   char incomingByte2 = Serial.read(); 
   char incomingByte3 = Serial.read();
   char incomingByte4 = Serial.read();
   char incomingByte5 = Serial.read();
   
   if(incomingByte1=='e'){  // if the first byte is an 'e' then we going to control the motors
   int val_1 = incomingByte2-'0';
   int val_2 = incomingByte3-'0';
   int val_3 = incomingByte4-'0';
   int val_4 = incomingByte5-'0';
    
    // For debugging
    Serial.println("Motor mode");
      Serial.println(val_1); 
      Serial.println(val_2); 
      Serial.println(val_3); 
      Serial.println(val_4); 
      Serial.println();
    
     
   //Drive forwards 
   if(val_1==0 && val_2==0 && val_3==0 && val_4==0 ){
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, HIGH);
    digitalWrite(leftMotor2, HIGH);
    digitalWrite(leftMotor1, LOW);
   }
   //Drive backwards
   else if(val_1==0 && val_2>0 && val_3>0 && val_4>0){
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(leftMotor1, HIGH); 
   }
   //Drive right
     else if(val_1==0 && val_2>0 && val_3>0 && val_4==0){
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(leftMotor1, LOW); 
   }
   //Drive left
      else if(val_1==0 && val_2>0 && val_3==0 && val_4==0){
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
    digitalWrite(leftMotor2, HIGH);
    digitalWrite(leftMotor1, LOW); 
   }
     
   else if (val_1>0 && val_2>0 && val_3>0 && val_4>0){
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(leftMotor1, LOW);
   }

  }
  
  else if (incomingByte1=='s'){ // if the first byte is 's' then we will control the robot arm
   int val_1 = incomingByte2-'0';  // val_1 corresponds to the thumb
   int val_2 = incomingByte3-'0';  // val_2 corresponds to index finger
   int val_3 = incomingByte4-'0';  // val_3 corresponds to the middle finger
   int val_4 = incomingByte5-'0';  // val_4 corresponds to the pinky
     
     //For debugging
     Serial.println("Robot arm mode");
      Serial.println(val_1); 
      Serial.println(val_2); 
      Serial.println(val_3); 
      Serial.println(val_4); 
      Serial.println();
     
    
    // Close claw
    if(val_1==0 && val_2==0 && val_3==0 && val_4==0){
     claw_ang-=5;  
     }
     // Open claw
     else if (val_1==0 && val_2>0 && val_3>0 && val_4>0){
     claw_ang+=5;  
     }
     // Tilt forward
     else if (val_1==0 && val_2>0 && val_3>0 && val_4==0){
     tilt_ang+=10;  
     }
     //Tilt backward
     else if (val_1==0 && val_2>0 && val_3==0 && val_4==0){
     tilt_ang-=10;  
     }
     
    if(claw_ang<0){
       claw_ang=0;
     }
    if (claw_ang>145){ 
       claw_ang=145;
     }
    if (tilt_ang<15){
      tilt_ang=15;
    }
    if(tilt_ang>180){
      tilt_ang=180;
    }
    
    // For debugging
    /* Serial.println("Claw angle:");   
    Serial.println(claw_ang);
    Serial.println();
    Serial.println("Tilt angle:");
    Serial.println(tilt_ang);
    Serial.println();
   */
   
    claw.write(claw_ang);
    delay(10);
    tilt.write(tilt_ang);
    delay(10);    
    
  }
  
  }
  delay(10);
}
