//HoverCraft contole code, Fitim Halimi 
#include <Servo.h> //Library for Servo Motor
#include <IRremote.h> //Library for IR Receiver
Servo servo; //Servo motor object
int Motorri2 = 2;  // Pin where the activation of the first motor is connected 
int Motorri1 = 3;  // Pin where the activation of the second motor is connected 
int IR_Pranuesi = 4; // Pin where the IR Receiver is connected
int Majtas = 0; // Variable for turning left
int Djathtas = 0; // Variable for turning right
int Ndizu = 0; // Variable for turning on the hovering motor
IRrecv irrecv(IR_Pranuesi); //Connects PIN nr.4 of the IR receiver with the servo's object
decode_results results;
void setup() {
  //Serial.begin(9600);
  irrecv.enableIRIn(); // Start IR Receiver
  servo.attach(5);  // Connects Pin nr.5 with servo's object
  pinMode(Motorri1, OUTPUT); //Declaration of first motor's pin as output
  pinMode(Motorri2, OUTPUT); //Declaration of first motor's pin as output
}
void loop() {
  
  if (irrecv.decode(&results)) { Serial.println(results.value, HEX); irrecv.resume(); } // Accept the values and save them
  else if(results.value == 0x410E21D) { digitalWrite(Motorri1, HIGH); } //Button 0 pressed, turn on the hovering motor

  else if(results.value == 0x41018E7) { digitalWrite(Motorri1, LOW); } //Red button pressed, turn off the hovering motor
  else if(results.value == 0x41048B7) { //Arrow up, activate the second motor 
    digitalWrite(Motorri2, HIGH); } //Turns the motor for thrusting (second motor)
  else if (results.value == 0x410C837) { digitalWrite(Motorri2, LOW); } //Arrow down, deactivate the second motor 
  else if (results.value == 0x410A857) { //Button OK pressed, moves forward
    Majtas = 0; Djathtas = 0; //Resets the value for turning left or righ. (Majtas=Left, Djathtas=Right)
    servo.write(90); } // Tell servo in which position it will go (forward)
  else if (results.value == 0x41028D7) { //Button Left pressed, moves forward 
    Majtas++; //Increase value for one
    if ( Majtas =! 0 ) { //IF the value is increased, activate turning left
    servo.write(140); } } //Tell servo in which position it will go (left)
  else if (results.value == 0x4106897) { //Buton right pressed, move forward kthehet ne pozicion te drejte nese eshte kthyer me heret ne ndonje ane tjeter]
    Djathtas++; //Increase value for one
    if ( Djathtas =! 0 ) { //If the value is increased, activate turning right
    servo.write(40); } } }// Tell servo in which position it will go (right)
