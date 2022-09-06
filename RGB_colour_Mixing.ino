#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

int Sol_R= 9;
int Sol_G= 10;
int Sol_B= 11;
const int trigPinR = A0;
const int echoPinR = A1;
const int trigPinG = A2;
const int echoPinG = A3;
const int trigPinB = A4;
const int echoPinB = A5;
int duration;
float distance;
float distance2;
float change; 
float Vr;
float Vg;
float Vb;
float area= 45.36;
float K;
float exit_vol = 20.00;
const unsigned long eventInterval = 1000;
unsigned long previousTime = 0; 

int redMin = 63; // Red minimum value
int redMax = 371; // Red maximum value
int greenMin = 62; // Green minimum value
int greenMax = 367; // Green maximum value
int blueMin = 46; // Blue minimum value
int blueMax = 288; // Blue maximum value

// Variables for Color Pulse Width Measurements

int redPW = 0;
int greenPW = 0;
int bluePW = 0;

// Variables for final Color values

int redValue;
int greenValue;
int blueValue;

void setup() {

  // Setup Serial Monitor
  Serial.begin(9600);
   
   // Set S0 - S3 as outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  
  // Set Sensor output as input
  pinMode(sensorOut, INPUT);

   // Set Frequency scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);

  
  pinMode(trigPinR, OUTPUT); 
  pinMode(echoPinR, INPUT); 
  pinMode(Sol_R,OUTPUT);

  pinMode(trigPinG, OUTPUT); 
  pinMode(echoPinG, INPUT); 
  pinMode(Sol_G,OUTPUT);
 
  pinMode(trigPinB, OUTPUT); 
  pinMode(echoPinB, INPUT); 
  pinMode(Sol_B,OUTPUT);
  
 
}

void loop() {

  unsigned long currentTime = millis();
  if (currentTime - previousTime >= eventInterval){
    
  // Read Red value
  redPW = getRedPW();
  // Map to value from 0-255
  redValue = map(redPW, redMin,redMax,255,0);
  // Delay to stabilize sensor
  delay(200);
  
  // Read Green value
  greenPW = getGreenPW();
  // Map to value from 0-255
  greenValue = map(greenPW, greenMin,greenMax,255,0);
  // Delay to stabilize sensor
  delay(200);
  
  // Read Blue value
  bluePW = getBluePW();
  // Map to value from 0-255
  blueValue = map(bluePW, blueMin,blueMax,255,0);
  // Delay to stabilize sensor
  delay(200);


   
   // Print output to Serial Monitor
  Serial.print("Red = ");
  Serial.print(redValue);
  Serial.print(" - Green = ");
  Serial.print(greenValue);
  Serial.print(" - Blue = ");
  Serial.println(blueValue);

  previousTime = currentTime;
  
  }
  // mixer
  K = exit_vol/255;
  if(redValue > 40 && blueValue> 40 && greenValue> 40)
  {
   Vr =getvolR();
     delay(1000); 
     Serial.print("Red vol. =  ");
     Serial.print(Vr);
    
   Vg = getvolG();
     delay(1000);
     Serial.print("Green vol. =  ");
     Serial.print(Vg);
   
   Vb = getvolB();
   delay(1000);
   Serial.print("Blue vol. =  ");
   Serial.print(Vb);
   Serial.print("\n");
  }

}


// Function to read Red Pulse Widths
int getRedPW() {

  // Set sensor to read Red only
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);
  // Return the value
  return PW;

}

// Function to read Green Pulse Widths
int getGreenPW() {

  // Set sensor to read Green only
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);
  // Return the value
  return PW;

}

// Function to read Blue Pulse Widths
int getBluePW() {

  // Set sensor to read Blue only
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);
  // Return the value
  return PW;

}

float getvolR()
{
digitalWrite(trigPinR, LOW);
delayMicroseconds(2);
digitalWrite(trigPinR, HIGH);
delayMicroseconds(10);
digitalWrite(trigPinR, LOW);
duration = pulseIn(echoPinR, HIGH);
distance= duration*0.034/2;
static float x = distance;
static float z = redValue;
float y=z*K;
change = y/area;
distance2= x+change;

if(distance < distance2)
{
  digitalWrite(Sol_R,HIGH);
}
if(distance >= distance2)
{
  digitalWrite(Sol_R,LOW);
}
return K*redValue;
}

float getvolG()
{
digitalWrite(trigPinG, LOW);
delayMicroseconds(2);
digitalWrite(trigPinG, HIGH);
delayMicroseconds(10);
digitalWrite(trigPinG, LOW);
duration = pulseIn(echoPinG, HIGH);
distance= duration*0.034/2;
static float x = distance;
static float z = greenValue;
float y=z*K;
change = y/area;
distance2= x+change;

if(distance < distance2)
{
  digitalWrite(Sol_G,HIGH);
}
if(distance >= distance2)
{
  digitalWrite(Sol_G,LOW);
}
return K*greenValue;

}

float getvolB()
{
digitalWrite(trigPinB, LOW);
delayMicroseconds(2);
digitalWrite(trigPinB, HIGH);
delayMicroseconds(10);
digitalWrite(trigPinB, LOW);
duration = pulseIn(echoPinB, HIGH);
distance= duration*0.034/2;
static float x = distance;
static float z = blueValue;
float y=z*K;
change = y/area;
distance2= x+change;

if(distance < distance2)
{
  digitalWrite(Sol_B,HIGH);
}
if(distance >= distance2)
{
  digitalWrite(Sol_B,LOW);
}
return K*blueValue;
}
