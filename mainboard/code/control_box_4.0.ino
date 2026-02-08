#include "Thermister.h"
#include "Vars.h"
#include "Heater.h"
#include "Acetone.h"



//libray setup
NTC_100k tempSence(thmist);
RelayHeater heater(heaterPin, fan1, tempSence);
bomb acetone(ultrasonic, fanHeater);

void setup() {
  //inishalise Serial
  Serial.begin(9600);
  while (!Serial) { delay(10); } // Wait for serial console to open
  //set up gas sencer in acetone
  acetone.Setup();
  //chamber fan setup
  pinMode(fanPin,OUTPUT);
  //estop
  attachInterrupt(digitalPinToInterrupt(button), stop, LOW);
}

void loop() {
  update(timer>0);

  if(time+1000<millis()){
    if(timer>0) timer--;
    send();
    time = millis();
  }
  
  read();
}

//update sencers
//need to rewrite
void update(bool ace) {
  if (digitalRead(encloser) == 1) {
    //updates heater and acetone
    heater.run();
    acetone.run(ace);
  } else {
    //pauses system if lid is opened
    heater.pause();
    acetone.pause();
    Serial.println("OPEN");
  }
  //estop if max temp is reached
  if (heater.read(false) >= heatMax) stop();
  digitalWrite(fanPin,fan);
}

//reads in serial and sends to parce 
void read() {
  String in;
  String comand;
  int space;
  double input;
  if (Serial.available()) {
    
    in = Serial.readStringUntil('\n');  // Read until newline
    space = in.indexOf(" "); // find space
    if(space!=-1) {
      //if there is a space split in comand in 2
      comand = in.substring(0, space);
      input = in.substring(space + 1).toDouble();
    }
    else{
      //only send comand
      comand = in;
      input = 0;
    }
    //send comands to be parsed 
    set(comand, input);
  }
}

//parse the comand and give its input
void set(String comand, double input){
  //all of the parsing
  if(comand.equalsIgnoreCase("setTemp")) heater.setTemp(input, farenhight);
  else if(comand.equalsIgnoreCase("setAcetone")) acetone.setAcetone(input);
  else if(comand.equalsIgnoreCase("setFilter")) {
    if(input == 0) acetone.runFilter(false);
    else acetone.runFilter(true);
  }
  else if(comand.equalsIgnoreCase("setHeatFan")) {
    if(input == 0) heater.runFan(false);
    else heater.runFan(true);
  }
  else if(comand.equalsIgnoreCase("setCircFan")) {
    if(input == 0) fan = false;
    else fan = true;
  }
  else if(comand.equalsIgnoreCase("Run")) {
    timer = (int) input;
  }
  else if(comand.equalsIgnoreCase("kill")) {
    stop();
  }
  else Serial.println("Unknown Comand");
}


//sends info to screen
void send() {
  Serial.print("Temp: ");
  Serial.print(heater.read(farenhight));
  Serial.print(" TempTarget: ");
  Serial.print(heater.curentSet(farenhight));
  Serial.print(" Acetone: ");
  Serial.print((acetone.getAcetone()));
  Serial.print(" AcetoneTarget: ");
  Serial.print((acetone.getPresent()));
  Serial.print(" Fans: ");
  if (heater.curentFan()) Serial.print(1);
  else Serial.print(0);
  if (acetone.getFilter()) Serial.print(1);
  else Serial.print(0);
  if (fan) Serial.print(1);
  else Serial.print(0);
  Serial.print(" Timer: ");
  Serial.println(timer);
}

//estop. stop all prosesed exsept fan
void stop() {

  heater.kill();
  acetone.kill();
  digitalWrite(fanPin, HIGH);
  while (true)
    Serial.println("KILL");
}