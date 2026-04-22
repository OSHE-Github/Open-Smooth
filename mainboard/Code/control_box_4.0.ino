#include <Adafruit_NeoPixel.h>
#include <Servo.h>

#include "Thermister.h"
#include "Vars.h"
#include "Heater.h"
#include "Acetone.h"



//libray setup
NTC_100k tempSence(thmist);
RelayHeater heater(heaterPin, fan1, tempSence);
bomb acetone(ultrasonic, fanHeater);
Servo servo;
Adafruit_NeoPixel neo(ledCount, 7, NEO_GRB + NEO_KHZ800 );

void setup() {
  //inishalise Serial
  Serial.begin(115200);
  neo.begin();
  

  while (!Serial) { delay(10); }  // Wait for serial console to open
  //set up gas sencer in acetone
  acetone.Setup();
  //chamber fan setup
  pinMode(fanPin, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  pinMode(encloser, INPUT_PULLUP);
  //estop
  //attachInterrupt(digitalPinToInterrupt(button), stop, LOW);
  //servo setup
  servo.attach(6);

  //screen turn on
  digitalWrite(fanPin,LOW);
  delay(1000);
  digitalWrite(fanPin,HIGH);
  //color(neo.Color(255, 255, 255));

}

void loop() {
  update(timer > 0);


  if (time + 2000 < millis()) {
    if (timer > 0) timer--;
    send();
    time = millis();
  }

  read();
}

//update sencers
//need to rewrite
void update(bool ace) {

  if (!digitalRead(button)){
    delay(500);
    if (!digitalRead(button)) stop();
  }

  if (digitalRead(encloser) == 1 && open) {
    //pauses system if lid is opened
    heater.run();
    acetone.run(ace);
    Serial.println("CLOSE");
    open = false;
  } else if (digitalRead(encloser) == 1) {
    //updates heater and acetone
    heater.run();
    acetone.run(ace);
  } else {
    //pauses system if lid is opened
    heater.pause();
    acetone.pause();
    servo.write(90);
    if(!open) Serial.println("OPEN");
    open = true;
  }
  //estop if max temp is reached
  //if (heater.read(false) >= heatMax) stop();
}

//reads in serial and sends to parce
void read() {
  String in;
  String comand;
  int space;
  double input;
  if (Serial.available()) {

    in = Serial.readStringUntil('\n');  // Read until newline
    space = in.indexOf(" ");            // find space
    if (space != -1) {
      //if there is a space split in comand in 2
      comand = in.substring(0, space);
      input = in.substring(space + 1).toDouble();
    } else {
      //only send comand
      comand = in;
      input = 0;
    }
    //send comands to be parsed
    set(comand, input);
  }
}

//parse the comand and give its input
void set(String comand, double input) {
  //all of the parsing
  comand.trim();
  if (comand.equalsIgnoreCase("setTemp")) heater.setTemp(input, farenhight);
  else if (comand.equalsIgnoreCase("setAcetone")) acetone.setAcetone(input);
  else if (comand.equalsIgnoreCase("setFilter")) {
    if (input == 0) acetone.runFilter(false);
    else acetone.runFilter(true);
  } else if (comand.equalsIgnoreCase("setHeatFan")) {
    if (input == 0) heater.runFan(false);
    else heater.runFan(true);
  } else if (comand.equalsIgnoreCase("setCircFan")) {
    if (input == 0) fan = false;
    else fan = true;
  } else if (comand.equalsIgnoreCase("setServo")) {
    if (input == 0) servo.write(90);
    else servo.write(105);
  } else if (comand.equalsIgnoreCase("Run")) {
    timer = (int)input;
  } else if (comand.equalsIgnoreCase("KILL")) {
    stop();
  } else if (comand.equalsIgnoreCase("RED")) {
    color(neo.Color(255, 0, 0));
  } else if (comand.equalsIgnoreCase("GREEN")) {
    color(neo.Color(0, 255, 0));
  } else if (comand.equalsIgnoreCase("BLUE")) {
    color(neo.Color(0, 0, 255));
  } else if (comand.equalsIgnoreCase("YELLOW")) {
    color(neo.Color(255, 255, 0));
  } else if (comand.equalsIgnoreCase("WHITE")) {
    color(neo.Color(255, 255, 255));
  } else if (comand.equalsIgnoreCase("PURPLE")) {
    color(neo.Color(135, 0, 255));
  } else if (comand.equalsIgnoreCase("BLACK")) {
    color(neo.Color(0, 0, 0));
  } else Serial.println("Unknown Comand");
}

//sets the leds a color
void color(uint32_t color) {
  for (int i = 0; i < ledCount; i++)
    neo.setPixelColor(i, color);
  neo.show();
}

//sends info to screen
void send() {
  Serial.print("TEMP ");
  Serial.println((int)heater.read(farenhight));
  Serial.print("TempTarget ");
  Serial.println((int)heater.curentSet(farenhight));
  Serial.print("ACETONE ");
  Serial.println((acetone.getAcetone()));
  Serial.print("AcetoneTarget ");
  Serial.println(((int)acetone.getPresent()));
  // Serial.print(" Fans: ");
  // if (heater.curentFan()) Serial.print(1);
  // else Serial.print(0);
  // if (acetone.getFilter()) Serial.print(1);
  // else Serial.print(0);
  // if (fan) Serial.print(1);
  // else Serial.print(0);
  // Serial.print(" Timer: ");
  // Serial.println(timer);
}

//estop. stop all prosesed exsept fan
void stop() {
  detachInterrupt(digitalPinToInterrupt(button));
  heater.kill();
  acetone.kill();
  servo.write(90);
  digitalWrite(fanPin, HIGH);
  // Serial.println("KILL");
  while (true)
    Serial.println("KILL");
}