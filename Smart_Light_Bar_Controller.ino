#include <TinyGPS++.h>
#include <SparkFun_ADXL345.h>         // SparkFun ADXL345 Library
#include <ezButton.h>
//#include <SoftwareSerial.h>
 
 
/*********** acellerometer COMMUNICATION SELECTION ***********/
/*    Comment Out The One You Are Not Using    */
//ADXL345 adxl = ADXL345(10);           // USE FOR SPI COMMUNICATION, ADXL345(CS_PIN);
ADXL345 adxl = ADXL345();             // USE FOR I2C COMMUNICATION
 
static const int RXPin = 19, TXPin = 18;
static const uint32_t GPSBaud = 9600;
int currentLightsetting = 0;
static const int lightTXPin = 3;
int cLight = 41;
int cSpeed = 1;
// MPH of full spot setting
int spotSpeed = 50;
int newSpeedSetting = 1;
int justbooted = 1;
unsigned long gpsSpeedMillis;
int previousGPSspeed = 0 ;
int currentGpsSpeed = 0; 
 
//Array of speeds to change light settings
int lightSettingsSpeeds[5];
int hasRecentAcitivity;
// The TinyGPS++ object
TinyGPSPlus gps;
 
//Button pressing vars
const int SHORT_PRESS_TIME = 1000; // 1000 milliseconds
const int LONG_PRESS_TIME  = 2000; // 1000 milliseconds
ezButton button(2);  // create ezButton object that attach to pin
unsigned long pressedTime  = 0;
unsigned long releasedTime = 0;
bool isPressing = false;
bool isLongDetected = false;
 
const int buzzerPin = 4; //buzzer to arduino pin 9
 
 
// The serial connection to the GPS device
//SoftwareSerial ss(RXPin, TXPin);
 
void setup()
{
 Serial.begin(9600);
 Serial2.begin(GPSBaud);
 button.setDebounceTime(50); // set debounce button time to 50 milliseconds
 
 // /*
 //     setup accelerometer
 // */
 // adxl.powerOn();                     // Power on the ADXL345
 
 // adxl.setRangeSetting(16);           // Give the range settings
 //                                     // Accepted values are 2g, 4g, 8g or 16g
 //                                     // Higher Values = Wider Measurement Range
 //                                     // Lower Values = Greater Sensitivity
 
 // adxl.setSpiBit(0);                  // Configure the device to be in 4 wire SPI mode when set to '0' or 3 wire SPI mode when set to 1
 //                                     // Default: Set to 1
 //                                     // SPI pins on the ATMega328: 11, 12 and 13 as reference in SPI Library
 
 // adxl.setActivityXYZ(1, 1, 1);       // Set to activate movement detection in the axes "adxl.setActivityXYZ(X, Y, Z);" (1 == ON, 0 == OFF)
 // adxl.setActivityThreshold(21);      // 62.5mg per increment   // Set activity   // Inactivity thresholds (0-255)
 // adxl.setInactivityXYZ(1, 1, 1);     // Set to detect inactivity in all the axes "adxl.setInactivityXYZ(X, Y, Z);" (1 == ON, 0 == OFF)
 // adxl.setInactivityThreshold(20);    // 62.5mg per increment   // Set inactivity // Inactivity thresholds (0-255)
 // adxl.setTimeInactivity(5);         // How many seconds of no activity is inactive?
 
 //  // Turn on Interrupts for each mode (1 == ON, 0 == OFF)
 // adxl.InactivityINT(1);
 // adxl.ActivityINT(1);
 
 /*
   Setup led pins
 */
 
 //Lighting control pins
  pinMode(41, OUTPUT);
  pinMode(42, OUTPUT);
  pinMode(43, OUTPUT);
  pinMode(44, OUTPUT);
  pinMode(45, OUTPUT);
  pinMode(46, OUTPUT);
  pinMode(47, OUTPUT);
 
 //Blue Ready Lighting 
  pinMode(48, OUTPUT);
 //Error led light
  pinMode(49, OUTPUT);
 // buzzer pin
  pinMode(buzzerPin, OUTPUT);

  pinMode(lightTXPin, OUTPUT);
 
 Serial.println(F("DeviceExample.ino"));
 Serial.println(F("A simple demonstration of TinyGPS++ with an attached GPS module"));
 Serial.print(F("Testing TinyGPS++ library v. ")); Serial.println(TinyGPSPlus::libraryVersion());
 Serial.println(F("by Mikal Hart"));
 Serial.println();
}
 
void loop()
{
  
 int blueLight = 0;
 //ADXL_ISR();
 // This sketch displays information every time a new sentence is correctly encoded.
 while (Serial2.available() > 0){
 
   //Check new speed and populate light settings ranges
   if(newSpeedSetting){
     Serial.println("New Speed Setting");
     int tempVar = spotSpeed / 5;
     for (byte i = 0; i < 5; i = i + 1) {
       lightSettingsSpeeds[i] = (i+1)*(tempVar);
              
       Serial.println(lightSettingsSpeeds[i]);
     }
     Serial.println("full array");
     Serial.println(lightSettingsSpeeds[0]);
     Serial.println(lightSettingsSpeeds[1]);
     Serial.println(lightSettingsSpeeds[2]);
     Serial.println(lightSettingsSpeeds[3]);
     Serial.println(lightSettingsSpeeds[4]);
     Serial.println("full done");
     //reset new speed setting
     newSpeedSetting = 0;
    
   }

    
  
   /*
   Main logic to change light bar settings based on speed     
   */ 
    if (gps.encode(Serial2.read()))
     //displayInfo();
 
    if (gps.speed.isValid())
    {
      // if(justbooted == 1){
      //   Serial.println("in just booted");
      //   previousGPSspeed = gps.speed.mph();
      //   cSpeed = previousGPSspeed;
      //   gpsSpeedMillis = millis();  //timmer for gps MPH refresh rate
      //   justbooted = 0;        
      //  }        
    
      // if(justbooted == 0 ){
      //   Serial.println("in no just booted");
      //   int currentMillis = millis();
      //   if ((currentMillis - gpsSpeedMillis) < 1000) 
      //   {
      //     int acell = (currentGpsSpeed - previousGPSspeed ) / ((currentMillis - gpsSpeedMillis)/1000);
      //     Serial.println("Acell is ---");
      //     Serial.println(acell);
      //     cSpeed = cSpeed + acell;
      //   }
      //   else{
      //     Serial.println("in 1sec else");
      //     previousGPSspeed = currentGpsSpeed;           
      //     currentGpsSpeed = gps.speed.mph();
      //     cSpeed = currentGpsSpeed;
      //     gpsSpeedMillis = millis();
      //   }

      // }
      
    
      // else {
      //   Serial.println("just booted issue") ;        
      // }

      /*
          GPS MPH speed update logging
      */      
      if(gps.speed.isUpdated()){
        int time = (millis() - gpsSpeedMillis);

        Serial.print("Speed updated to: ");
        Serial.print(gps.speed.mph());
        Serial.print(" in ");
        Serial.print(time);
        Serial.println(" milliseconds ");
        gpsSpeedMillis = millis();

        digitalWrite(48, LOW);
        

        
      }
      else if(!gps.speed.isUpdated()){
        int time = gpsSpeedMillis - millis();
        Serial.print("Speed Not Updated: ");
        Serial.println(gps.speed.mph());
        digitalWrite(48, HIGH);
      }
      else{
        Serial.println("speed update check failed");        
      }

      cSpeed = gps.speed.mph()   ;
      //Serial.println(cSpeed);
    
      // clear error light
      digitalWrite(49, LOW);
    
      if(cSpeed < lightSettingsSpeeds[0]){
    
        digitalWrite(cLight, LOW);
        digitalWrite(41, HIGH);
        cLight = 41;
        sendLightSetting(1);
        //Serial.println("1st light");
      
      }
      else if(cSpeed < lightSettingsSpeeds[1] ){
        digitalWrite(cLight, LOW);
        digitalWrite(42, HIGH);
        cLight = 42;
        sendLightSetting(2);
        //Serial.println("2th light");
      
      }
      else if(cSpeed < lightSettingsSpeeds[2] ){

        digitalWrite(cLight, LOW);
        digitalWrite(43, HIGH);
        cLight = 43;
        sendLightSetting(3);
        //Serial.println("3th light");
      
      }
      else if(cSpeed < lightSettingsSpeeds[3] ){
        digitalWrite(cLight, LOW);
        digitalWrite(44, HIGH);
        cLight = 44;
        sendLightSetting(4);
        //Serial.println("4th light");
      
      
      }
      else if(cSpeed < lightSettingsSpeeds[4]){
        digitalWrite(cLight, LOW);
        digitalWrite(45, HIGH);
        cLight = 45;
        sendLightSetting(5);
        //Serial.println("5th light");    
      }
      else if(cSpeed >= lightSettingsSpeeds[4]){
        digitalWrite(cLight, LOW);
        digitalWrite(46, HIGH);
        cLight = 46;
        sendLightSetting(6);
        //Serial.println("6th light");    
      }
      else{
        digitalWrite(49, HIGH);
        Serial.println("MPH exeption...");
        Serial.println(cSpeed);
      
      }
    }
    else
    {
      Serial.println("Waiting on gps");
      digitalWrite(49, HIGH);
    }
 
   //Inactivity check
  
   // if (ADXL_ISR()== 0){
   //   digitalWrite(48, HIGH);
 
   // }
   // else{
   //   digitalWrite(48, LOW);
 
   // }
   //button logic check
   //runButtonLogic();     
    
 }
 if (millis() > 5000 && gps.charsProcessed() < 10)
 {
   Serial.println(F("No GPS detected: check wiring."));
   while(true);
   //write login to flash red light for major error
 }
 
 
}
 
/*
 accelerometer inturrups
*/
bool ADXL_ISR() {
 int inActivity;
 // getInterruptSource clears all triggered actions after returning value
 // Do not call again until you need to recheck for triggered actions
 byte interrupts = adxl.getInterruptSource();
 
 int activity;
 // Inactivity
 if(adxl.triggered(interrupts, ADXL345_INACTIVITY)){
   Serial.println("*** INACTIVITY triggered ***");
   activity = 0;
   hasRecentAcitivity = 0;
 }
 else if(adxl.triggered(interrupts, ADXL345_ACTIVITY)){
   //Serial.println("*** ACTIVITY triggered ***");
   activity = 1;
   hasRecentAcitivity = 1;
 
    //add code here to do when activity is sensed
 }
 else if(hasRecentAcitivity){ // if recent activity has occuredbut no innactive trigger... there is still acitivity
   activity = 1;
 }
  // Activity
 
 return activity;
 }
 
void runButtonLogic(){
 button.loop(); // MUST call the loop() function first
 
 if(button.isPressed()){
   pressedTime = millis();
   isPressing = true;
   isLongDetected = false;
 }
 
 if(button.isReleased()) {
   isPressing = false;
   releasedTime = millis();
 
   long pressDuration = releasedTime - pressedTime;
 
   if( pressDuration < SHORT_PRESS_TIME ){
     Serial.println("A short press is detected");
     buzzerBeep1();
   }
 }
 
 if(isPressing == true && isLongDetected == false) {
   long pressDuration = millis() - pressedTime;
 
   if( pressDuration > LONG_PRESS_TIME ) {
     Serial.println("A long press is detected");
     isLongDetected = true;
     buzzerBeep2();     
   }
 } 
}
 
void buzzerBeep1(){
 tone(buzzerPin, 2300);
 delay(100); 
 noTone(buzzerPin);
}
void buzzerBeep2(){
 tone(buzzerPin, 2300);
 delay(100); 
 noTone(buzzerPin);
 delay(100);
 tone(buzzerPin, 2300);
 delay(100); 
 noTone(buzzerPin);
}
// GPS info debugging
void displayInfo()
{
 Serial.print(F("Location: "));
 if (gps.location.isValid())
 {
   Serial.print(gps.location.lat(), 6);
   Serial.print(F(","));
   Serial.print(gps.location.lng(), 6);
 }
 else
 {
   Serial.print(F("INVALID"));
 }
 
 Serial.print(F("  Date/Time: "));
 if (gps.date.isValid())
 {
   Serial.print(gps.date.month());
   Serial.print(F("/"));
   Serial.print(gps.date.day());
   Serial.print(F("/"));
   Serial.print(gps.date.year());
 }
 else
 {
   Serial.print(F("INVALID"));
 }
 
 Serial.print(F(" "));
 if (gps.time.isValid())
 {
   if (gps.time.hour() < 10) Serial.print(F("0"));
   Serial.print(gps.time.hour());
   Serial.print(F(":"));
   if (gps.time.minute() < 10) Serial.print(F("0"));
   Serial.print(gps.time.minute());
   Serial.print(F(":"));
   if (gps.time.second() < 10) Serial.print(F("0"));
   Serial.print(gps.time.second());
   Serial.print(F("."));
   if (gps.time.centisecond() < 10) Serial.print(F("0"));
   Serial.print(gps.time.centisecond());
 }
 else
 {
   Serial.print(F("INVALID"));
 }
 
 Serial.print(F(" ,speed="));
 if (gps.speed.isValid())
 {
   Serial.print(gps.speed.mph());
 }
 else
 {
   Serial.println("INVALID");
 }
 
 Serial.println();
}
void sendLightSetting(int lightIndex)
{

 //Serial.println("Speed Setting"+lightIndex);

  if (currentLightsetting == lightIndex ){
    Serial.println("no light change");
  }
  else {
    digitalWrite(lightTXPin, HIGH);
    delayMicroseconds(1050);
    digitalWrite(lightTXPin, LOW);
    delayMicroseconds(80);
    digitalWrite(lightTXPin, HIGH);
    delayMicroseconds(1050);
    digitalWrite(lightTXPin, LOW);
    delayMicroseconds(80);

    for (int i =0 ; i < lightIndex; i++){
      digitalWrite(lightTXPin, HIGH);
      delayMicroseconds(80);
      digitalWrite(lightTXPin, LOW);
      delayMicroseconds(80);
    }
    currentLightsetting = lightIndex;
    Serial.println("It Changed!");
  }


}
