/****************************************************
*  Arduino C-code for hexapod robot with
*  capabilities of GPS tracking and XBee
*  communication for swarm logic.
*  author: Manish Kumar
*  email: gateway.manish@gmail.com
****************************************************/

#include <Servo.h>
#include <TinyGPS.h>

TinyGPS gps;
Servo b1,b2,b3,b4,b5,b6,s1,s2,s3,s4,s5,s6;
int m; long duration, inches; const int pingPin=5; int cm; char recv;
int led=13;
void setup(){
  Serial.begin(4800);
  b1.attach(12);   s1.attach(11);  b2.attach(10);   s2.attach(9);
  b3.attach(8);    s3.attach(7);   b4.attach(6);    s4.attach(5);
  b5.attach(A5);   s5.attach(A4);  b6.attach(A3);   s6.attach(A2);
  pinMode(led, OUTPUT);
}


//**************************** main body
void loop(){
 swarm();
 mscan();
 //locate();
// s1.write(170); s2.write(10); s3.write(170); s4.write(10); s5.write(10); s6.write(20);
 //echo();
 //sleep();
 //stand();
}
//******************************
void ledBlink(){
  digitalWrite(led, HIGH);
    delay(100);
    digitalWrite(led, LOW);
    delay(100);
}



//**************************** swarm function
char swarm(){
  if (Serial.available() > 0){
  recv=Serial.read();
 
  if((recv=='f')||(recv=='b')||(recv=='l')||
  (recv=='r')||(recv=='S')||(recv=='s')||
  (recv=='L')||(recv=='R')||(recv=='d')||
  (recv=='m')) 
  ledBlink();

  
  switch(recv){
  case 'f':   forward(); break;
  case 'b':   backward(); break;
  case 'l':   leftTurn(); break;
  case 'r':   rightTurn(); break;
  case 'S':   stand(); break;
  case 's':   sleep(); break;
  case 'L':   turnBackL(); break;
  case 'R':   turnBackR(); break;
  case 'd':   dance(); break;
  case 'm':   mscan(); break;
  case 'x':   randomMotion(); break;
 case 'g':   locate(); break;
  //default :   stand(); 
  }
  return(recv);
}
}

//~~~~~~~~~~~~~~~~~~~~~ metal scanning function
 void mscan(){
   //Serial.println("m");
  m = analogRead(A0);
 // delay(500);
  if(m>=800)
  {
  Serial.println("MetalDetected");
  
  stand();
  delay(500);
  locate();
  //forward(); forward();
   }
  // else 
  // forward(); 
 }
 
 //####################################
 void randomMotion(){
   forward(); mscan(); forward(); mscan(); forward(); mscan();
     leftTurn(); mscan(); forward(); mscan(); rightTurn(); mscan(); forward(); mscan(); forward(); mscan(); delay(1000);
     rightTurn(); mscan(); backward(); mscan(); rightTurn(); mscan(); forward(); mscan(); forward(); mscan(); delay(1000);
     backward(); mscan(); backward(); mscan(); backward(); mscan(); rightTurn(); mscan(); rightTurn(); mscan(); stand(); mscan(); delay(1000);
     forward(); mscan(); forward(); mscan(); forward(); mscan(); stand(); mscan(); 
 }
 
//^^^^^^^^^^^^^^^^^^^ stand function
void stand(){
  Serial.println("T");
  b1.write(90);    b2.write(90);    b3.write(90);
  b6.write(90);    b5.write(90);   b4.write(90);       
  delay(300);
  s4.write(90);    s5.write(100);    s6.write(90); 
  delay(300);
  s1.write(80);    s2.write(110);    s3.write(80); 
}

//########################## spider function
void spiderStand(){
  b1.write(120);    b2.write(120);    b3.write(120); 
  delay(1000);
  b6.write(60);    b5.write(60);   b4.write(60);       
  delay(5000);
  s4.write(90);    s5.write(90);    s6.write(90); 
  delay(1000);
  s1.write(90);    s2.write(90);    s3.write(90); 
}

//zzzzzzzzzzzzzzzzzzzzzz sleep function
void sleep(){
  //Serial.println("s");
  s1.write(170);    s2.write(10);    s3.write(170);
  s4.write(170);      s5.write(170);      s6.write(170);
  delay(300);
  b1.write(10);     b2.write(10);      b3.write(10);
  b4.write(178);    b5.write(178);    b6.write(178);
}

//>>>>>>>>>>>>>>>>>>>>>>> forward motion funtion
void forward(){               //s1=80, s2=110, s3=80, s4=90, s5=100, s6=90
  Serial.println("F");        //b1 to b6 = 90
  s1.write(50);   s3.write(50);   s5.write(130); //movement taking
    delay(100);
  b1.write(70);   b3.write(70);   b5.write(110); //movement taking
    delay(200);
  s1.write(80);   s3.write(80);   s5.write(100); //back to initial state
    delay(100);
  s2.write(140);  s4.write(120);  s6.write(120); //next positions of legs
    delay(100);
  b1.write(110);  b3.write(110);   b5.write(70);  //next positions of legs
    delay(200);
  b2.write(70);   b4.write(110);    b6.write(110);  //next positions of legs
    delay(200);
  s2.write(110);  s4.write(90);  s6.write(90);
    delay(100);
  s1.write(50);  s3.write(50);  s5.write(130);
    delay(100);
  b2.write(110);  b4.write(70);  b6.write(70);  //moving legs
  }
  
//<<<<<<<<<<<<<<<<<<<<<<<<< backward motion function
void backward(){
  Serial.println("B");
  s1.write(50);   s3.write(50);   s5.write(130);
  delay(100);
  b1.write(110); b3.write(110); b5.write(70);
  delay(100);
  s1.write(80);   s3.write(80);   s5.write(100);
  delay(100);
  s2.write(140);   s4.write(120);  s6.write(120);
  delay(100);
  b1.write(70);   b3.write(70);   b5.write(110);
  delay(100);
  b2.write(110);  b4.write(70);  b6.write(70);
  delay(100);
  s2.write(110);  s4.write(90);  s6.write(90);
  delay(100);
  s1.write(50);   s3.write(50);   s5.write(130);
  delay(100);
  b2.write(70);  b4.write(110);  b6.write(110);
  //b1.write(170);  b3.write(130);   b5.write(120);
  //delay(200);
}
//############################### turn left
void leftTurn(){
  Serial.println("L");
  s1.write(50);   s3.write(50);   s5.write(130);
    delay(100);
  b1.write(110);   b3.write(110);   b5.write(110); //moving legs
    delay(200);
  s1.write(80);   s3.write(80);   s5.write(100); 
    delay(100);
  s2.write(140);  s4.write(120);  s6.write(120);
    delay(100);
  b1.write(70);  b3.write(70);   b5.write(70);  //moving legs
    delay(200);
  b2.write(110);   b4.write(110);    b6.write(110);  //moving legs
    delay(200);
  s2.write(110);  s4.write(90);  s6.write(90);
    delay(100);
  s1.write(50);  s3.write(50);  s5.write(130);
    delay(100);
  b2.write(70);  b4.write(70);  b6.write(70);  //moving legs
  //  delay(500);  
}

//############################### right turn
void rightTurn(){
  Serial.println("R");
  s1.write(50);   s3.write(50);   s5.write(130);
    delay(100);
  b1.write(70);   b3.write(70);   b5.write(70); //moving legs
    delay(200);
  s1.write(80);   s3.write(80);   s5.write(100); 
    delay(100);
  s2.write(140);  s4.write(120);  s6.write(120);
    delay(100);
  b1.write(110);  b3.write(110);   b5.write(110);  //moving legs
    delay(200);
  b2.write(70);   b4.write(70);    b6.write(70);  //moving legs
    delay(200);
  s2.write(110);  s4.write(90);  s6.write(90);
    delay(100);
  s1.write(50);  s3.write(50);  s5.write(130);
    delay(100);
  b2.write(110);  b4.write(110);  b6.write(110);  //moving legs
  //  delay(500);
  }
  
//############################### turnback right by 180 degree
void turnBackL(){
Serial.println("K");
leftTurn();
leftTurn();
leftTurn();
leftTurn();
leftTurn();
leftTurn();
}

//################# turnback right by 180 degree
void turnBackR(){
  Serial.println("Q");
  rightTurn();
  rightTurn();
  rightTurn();
  rightTurn();
  rightTurn();
  rightTurn();
}

//******************************* lateral left shift
void lateralLeft(){
 // Serial.println("ll");
 s1.write(60);  s2.write(40);  s3.write(60);
 s4.write(130);  s5.write(60);  s6.write(130);
   delay(1000);
// s1.write(110);  s3.write(110);  s5.write(110);
// delay(500);
 
  s2.write(130);  s4.write(60);    s6.write(60);
   
   s1.write(130); s3.write(130); s5.write(120);
   delay(1000);
 //s1.write(90);
}

//******************************** dance dance dance
void dance(){
  //Serial.println("d");
  s1.write(50);  s2.write(120);  s3.write(50);
  s4.write(40);  s5.write(40);   s6.write(40);
    delay(400);
  s1.write(130);  s2.write(40);   s3.write(130);
  s4.write(140); s5.write(140);  s6.write(140);
    delay(400);
  stand();
  delay(500);
  s1.write(20); delay(250); s1.write(90); delay(250);
  s2.write(170); delay(250); s2.write(90); delay(250);
  s3.write(20); delay(250);  s3.write(90); delay(250);
  s4.write(170); delay(250); s4.write(90); delay(250);
  s5.write(170); delay(250); s5.write(90); delay(250);
  s6.write(170); delay(250); s6.write(90); delay(250);
}

//############################### echo sensor rangin
int echo(){
   // establish variables for duration of the ping, 
  // and the distance result in inches and centimeters:
   // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  // convert the time into a distance
 // inches = microsecondsToInches(duration);
 // cm = microsecondsToCentimeters(duration);
  cm= duration/29/2;
  //Serial.print(inches);
  //Serial.print("in, ");
  Serial.print(cm);
 // Serial.print("cm");
  Serial.println();
  
  if(cm<=25)
  backward();
  else
  forward();
  return(cm);
}


//######################### gps tracking
void locate(){
  bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;
  // For one second we parse GPS data and report some key values
  for (unsigned long start = millis(); millis() - start < 500;)
  {
    while (Serial.available())
    {
      char c = Serial.read();
      // Serial.write(c); // uncomment this line if you want to see the GPS data flowing
      if (gps.encode(c)) // Did a new valid sentence come in?
        newData = true;
    }
  }
  if (newData)
  {
    float flat, flon;
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);
    //Serial.print("LAT=");
    Serial.println(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
    //Serial.println(m);
    //Serial.print(" LON=");
    delay(500);
    Serial.println(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
   //Serial.println(n);
   //Serial.print(" SAT=");
    //Serial.print(gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites());
    //Serial.print(" PREC=");
    //Serial.print(gps.hdop() == TinyGPS::GPS_INVALID_HDOP ? 0 : gps.hdop());
  }
  /* gps.stats(&chars, &sentences, &failed);
  Serial.print(" CHARS=");
  Serial.print(chars);
  Serial.print(" SENTENCES=");
  Serial.print(sentences);
  Serial.print(" CSUM ERR=");
  Serial.println(failed);
}*/
}





