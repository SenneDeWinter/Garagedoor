#include <DFRobot_ID809.h>

DFRobot_ID809_IIC fingerprint;


void setup(){

  pinMode(7, OUTPUT);
  
  Serial.begin(9600);
  
  fingerprint.begin();
  
  while(!Serial);
  
  while(fingerprint.isConnected() == false){
    Serial.println("Communication with device failed, please check connection");
    
    delay(1000);
  }
}

void loop(){
  uint8_t ret = 0;

  fingerprint.ctrlLED(fingerprint.eBreathing, fingerprint.eLEDBlue, 0);
  Serial.println("Please press down your finger");
  
  if((fingerprint.collectionFingerprint(10)) != ERR_ID809){
    
    fingerprint.ctrlLED(fingerprint.eFastBlink, fingerprint.eLEDYellow, 3);
    Serial.println("Capturing succeeds");
  }else{
    Serial.println("Capturing fails");
    
  }
  Serial.println("Please release your finger");
  
  while(fingerprint.detectFinger());

  
  ret = fingerprint.search();
   
  if(ret != 0){
    
    fingerprint.ctrlLED(fingerprint.eKeepsOn, fingerprint.eLEDGreen, 0);
    Serial.print("Matching succeeds,ID=");
    Serial.println(ret);
    digitalWrite(7, HIGH);
    delay(500);
    digitalWrite(7, LOW);
  }else{
    
    fingerprint.ctrlLED(fingerprint.eKeepsOn, fingerprint.eLEDRed, 0);
    Serial.println("Matching fails");
  }
  Serial.println("-----------------------------");
  delay(1000);
}
