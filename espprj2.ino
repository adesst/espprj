#include <SoftwareSerial.h>
#include <ESP8266.h>

String str_result ="Empty";
bool bHw_status = false;
uint32_t baud = 115200;
bool bGmr = false;
bool bSR = false;
SoftwareSerial mySerial = SoftwareSerial(3,2);
//ESP8266 wifi(Serial,115200);

void setup() {
  pinMode(12,OUTPUT);

  Serial.begin(115200);
  while(!Serial){
    ;
  }
  
  mySerial.begin(4800);
  mySerial.println("Started");
  
}

void loop() {

  if( Serial.available() )
  {
    
  }
  else
  {
    if( !bGmr ){
      Serial.println("AT+GMR");
      bGmr = true;  
    }
    else if( !bSR ){
      bSR = true;
      Serial.println("AT+CIPSTA=\"192.168.1.93\"");
    }
    else{
      mySerial.println("Done");
      delay(10000);
    }
    
    delay(500);
  }  
}

void validate_result(){

  if( str_result == "")
    str_result = "Empty";
}

void serialEvent(){
  char res = Serial.read();
  mySerial.print(res);
}

