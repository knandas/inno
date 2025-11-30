///////////////////// code 1 12-bits analog input /////////////////////////////////
/*
  ReadAnalogVoltage
  https://www.arduino.cc/en/Tutorial/BuiltInExamples/ReadAnalogVoltage
*/

// the setup routine runs once when you press reset:
void setup() 
{
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
}

// the loop routine runs over and over again forever:
void loop() 
{
  int sensorValue = analogRead(36);   // pin 36
  int percent=map(sensorValue,0,4095,0,100); // 0-100
  //Convert the analog reading from 0 - 4095 to a voltage 0 - 3.3V:
  float voltage = sensorValue * (3.3 / 4095.0);
  // print out the value you read:
  Serial.print("sensor: ");
  Serial.print(sensorValue);
  Serial.print(" output: ");
  Serial.print(percent);
  Serial.print(" Volt: ");
  Serial.println(voltage);
  delay(100);
}


/////////////////////////////////////////////////////////////
///////  code 2 12-bits analog input serial plotter  ///////////////


void setup() 
{
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);
}

// the loop routine runs over and over again forever:
void loop() 
{
  int sensorValue = analogRead(36);   // pin 36
  int percent=map(sensorValue,0,4095,0,100); // 0-100
  //Convert the analog reading from 0 - 4095 to a voltage 0 - 3.3V:
  float voltage = sensorValue * (3.3 / 4095.0);
  //print out the value you read:
  //Serial.print("sensor:");
  //Serial.print(sensorValue);
  //Serial.print(" output:");
  //Serial.print(percent);
  Serial.print("Volt:");
  Serial.println(voltage);
  
  //Serial.print("min:");
  //Serial.println(0);
  //Serial.print("max:");
  //Serial.println(3.3);
  delay(100);
}

////////////////////////////////////////////////////////////////
///////////////////// code3 test servo ledc ///////////////////////////////////////////


unsigned long delayTime1=0,delayTime2=0 ; 
#define servo1 25
#define freq  50
#define resolution  16

 #define COUNT_LOW 2676
 #define COUNT_HIGH 7553

void setup() 
{
  Serial.begin(115200);
  ledcSetup(1, 50, 16);
  ledcAttachPin(servo1, 1);
}

void loop() 
{
  for(int vol=COUNT_LOW;vol<COUNT_HIGH;vol=vol+10)
  {
   ledcWrite(1, vol);
   Serial.println(vol);
   delay(10);
  }

  for(int vol=COUNT_HIGH;vol>COUNT_LOW;vol=vol-10)
  {
   ledcWrite(1, vol);
   Serial.println(vol);
   delay(10);
  }
}

//////////////////////////////////////////////////////////
/////////////// code 4 servo by vr///////////////////////////////////

#define servo1Pin 25
#define servo1Ch 1
#define freq  50
#define resolution  16
#define Ain 36
#define COUNT_LOW 2676
#define COUNT_HIGH 7553
int VR,pos,count;

void setup() 
{
  Serial.begin(115200);
  Serial.println("Start");
  ledcSetup(servo1Ch, freq, resolution); //ch,freq,res
  ledcAttachPin(servo1Pin, servo1Ch);
}

void loop() 
{
   VR=analogRead(Ain);
   pos=map(VR,0,4095,0,180);
   count=map(VR,0,4095,COUNT_LOW,COUNT_HIGH);
   ledcWrite(servo1Ch,count );
   Serial.printf("position=%d count=%d\n",pos,count);
   delay(50);
}


//////////////////////////////////////////////////////////////////
/////////////// code for remoteXY ///////////////////////////

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////


#define analogInPin 36
#define led1 4
#define servo1Pin 25
#define servo1Ch 1
#define freq  50
#define resolution  16
#define Ain 36
#define COUNT_LOW 2676
#define COUNT_HIGH 7553
int VR,pos,count;
unsigned long lastTime=0; 

void setup() 
{
  RemoteXY_Init ();  // initialization by macros 
  pinMode(led1,OUTPUT);
  ledcSetup(servo1Ch, freq, resolution); //ch,freq,res
  ledcAttachPin(servo1Pin, servo1Ch);
  //Serial.begin(115200);
}


void loop() 
{ 
  RemoteXY_Handler ();
   
  digitalWrite(led1, (RemoteXY.switch_01==0)?LOW:HIGH);
  count=map(RemoteXY.slider_01,0,100,COUNT_LOW,COUNT_HIGH);
  ledcWrite(servo1Ch,count );

  if(millis()>lastTime+500)
  {
   float sensorValue = analogRead(analogInPin);
   int percent= sensorValue *(100/4096.0);
   float volt= sensorValue *(3.3/4096.0);
   RemoteXY.circularBar_01=percent;
   RemoteXY.value_01=volt;
   lastTime=millis();
  } 
  
}
  
  

////////////////////////////////////////////////////////////////////////////////////////////////////////////
