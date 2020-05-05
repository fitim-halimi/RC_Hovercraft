//HoverCraft contole code, Fitim Halimi 
#include <Servo.h> //Libraria per Servo Motorrin
#include <IRremote.h> //Libraria per IR Pranuesin
Servo servo; //Objekti i Servo Motorrit
int Motorri2 = 2;  // Pini ku lidhet aktivizimi i motorrit te pare
int Motorri1 = 3;  // Pini ku lidhet aktivizimi i motorrit te dyte
int IR_Pranuesi = 4; // Pini ku lidhet IR Pranuesi
int Majtas = 0; // Variabla per kthimin majtas
int Djathtas = 0; // Variabla per kthimin djathtas
int Ndizu = 0; // Variabla per ndezjen e motorrit per ngritje
IRrecv irrecv(IR_Pranuesi); //E lidh PIN'in nr. 4 [IR Pranuesit] me objektin e IR
decode_results results;
void setup() {
  //Serial.begin(9600);
  irrecv.enableIRIn(); // Starto IR Pranuesin
  servo.attach(5);  // E lidh PIN'in nr. 5 me objektin e Servos
  pinMode(Motorri1, OUTPUT); //Deklarimi i PIN'it te motorrit te pare si dales
  pinMode(Motorri2, OUTPUT); //Deklarimi i PIN'it te motorrit te dyte si dales
}
void loop() {
  
  if (irrecv.decode(&results)) { Serial.println(results.value, HEX); irrecv.resume(); } // Prano vlerat dhe ruaji ne variabel
  else if(results.value == 0x410E21D) { digitalWrite(Motorri1, HIGH); } //Butoni 0 shtypur, ndizet motorri i poshtem

  else if(results.value == 0x41018E7) { digitalWrite(Motorri1, LOW); } //Butoni Kuq shtypur, ndalet motorri i poshtem
  else if(results.value == 0x41048B7) { //Butoni Para, Aktivizo shtytjen para te hovercraft 
    digitalWrite(Motorri2, HIGH); } //Ndez motorrin per shtytje
  else if (results.value == 0x410C837) { digitalWrite(Motorri2, LOW); } //Butoni Mbrapa shtypur, ndal motorron per shtytje
  else if (results.value == 0x410A857) { //Butoni OK shtypur, ecja behet drejt [ kthehet ne pozicion te drejte nese eshte kthyer me heret ne ndonje ane tjeter ]
    Majtas = 0; Djathtas = 0; //Reseton variablat per kthime majtas ose djathtas
    servo.write(90); } // tregoi servos se ne cilin pozicion te shkoje [ Drejt ]
  else if (results.value == 0x41028D7) { //Butoni Majtas shtypur, ecja behet drejt [ kthehet ne pozicion majtas nese eshte kthyer me heret ne ndonje ane tjeter]
    Majtas++; //Rrit vleren per nje
    if ( Majtas =! 0 ) { //Nese vlera eshte rritur, aktivizo kthimin djathtas
    servo.write(140); } } // tregoi servos se ne cilin pozicion te shkoje [ Majtas ]
  else if (results.value == 0x4106897) { //Butoni Djathtas shtypur, ecja behet drejt [ kthehet ne pozicion te drejte nese eshte kthyer me heret ne ndonje ane tjeter]
    Djathtas++; //Rrit vleren per nje
    if ( Djathtas =! 0 ) { //Nese vlera eshte rritur, aktivizo kthimin djathtas
    servo.write(40); } } }// tregoi servos se ne cilin pozicion te shkoje [Djathtas ]
