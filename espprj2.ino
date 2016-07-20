#include <SoftwareSerial.h>
#include <ESP8266.h>

String newCmd = "";
String str_result ="Empty";
bool bHw_status = false;
uint32_t baud = 115200;
bool bGmr = false;
bool bWaitSSerial = false;
bool bIncomingCmd = false;
bool bSR = false;
bool bOkSetup = false;
bool bCwMode = false;
bool bCfSR = false;
String strBuffer = "";
SoftwareSerial mySerial = SoftwareSerial(8,9);

void setup() {
  pinMode(12,OUTPUT);

  Serial.begin(115200);
  while(!Serial){
    ;
  }
  
  mySerial.begin(9600);
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
    else if( !bCwMode){
      bCwMode = true;
      Serial.println("AT+CWMODE=1");
    }
    else if( !bSR ){
      bSR = true;
      Serial.println("AT+CIPSTA=\"192.168.1.93\"");
    }
    else if( !bCfSR ){
      bCfSR = true;
      Serial.println("AT+CIFSR");
    }
    else if (!bOkSetup) {
      mySerial.println("Done");
      bOkSetup = true;
    }

    if( strBuffer != ""){
      mySerial.print(strBuffer);
      strBuffer = "";
    }
      
    delay(50);  
  }

  if( mySerial.available()){

    char sstmp = mySerial.read();
    if( !bWaitSSerial ){
      if( sstmp == '@' )
        bWaitSSerial = true;
    }
    else{
      newCmd += sstmp;
      if( sstmp == '\n')
      {
        bWaitSSerial = false;
        bIncomingCmd = true;
      }
      else if( sstmp == '|'){
        Serial.println();
      }
    }

    if(bIncomingCmd == true){

      Serial.print(newCmd);
      newCmd = "";
      bIncomingCmd = false;
    }
  }
}

void validate_result(){

  if( str_result == "")
    str_result = "Empty";
}

void serialEvent(){
  char res = Serial.read();
  //mySerial.print(res);
  strBuffer += res;
  //if( res == '\n'){
    //mySerial.print(strBuffer);
    //strBuffer = "";
  //}
    
}

