#include "Arduino_LED_Matrix.h"
#include "ArduinoGraphics.h"

//la durata del giorno (in secondi)
#define dayDuration 10
//la durata della transizione tra il giorno e la notte
#define transitionDuration 2
//la durata della transizione per l'accensione delle luci delle case
#define houseTransitionDuration 2

#define true 1
#define false 0

//Qui a seguito la definizione dei pin dei relay.
//Perché il programma funzioni i relay delle case devono essere messi tutti in PIN successivi.
#define sunPin 3
#define firstHousePin 4
#define lastHousePin 11

ArduinoLEDMatrix matrix;

byte empty[8][12] = {
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};

byte sun[8][12] = {
  { 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0 },
  { 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0 },
  { 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1 },
  { 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
  { 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
  { 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1 },
  { 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0 },
  { 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0 }
};

byte moon[8][12] = {
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0 },
  { 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0 },
  { 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0 },
  { 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0 },
  { 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0 },
  { 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

unsigned long timeNow = 0;
unsigned long lastChange = 0;
int isDay = true;

void normalTransition(int *isDay){
  matrix.loadSequence(LEDMATRIX_ANIMATION_LOAD);
  matrix.play(true);

  Serial.println("\nInizio la transizione...");
  digitalWrite(LED_BUILTIN, HIGH);
  
  Serial.println(*isDay==1?"Faccio sorgere il sole...":"Faccio tramontare il sole...");
  for(int i = 0; i < 255; i++){
    analogWrite(sunPin, abs(((*isDay)*255)-(255/transitionDuration)*i));
    delay(transitionDuration*1000/255);
  }

  Serial.println(*isDay==1?"Spengo le luci delle case...":"Accendo le luci delle case...");
  for(int i = firstHousePin; i < lastHousePin+1; i++){
    digitalWrite(i, (*isDay));
    delay(random(1000,houseTransitionDuration/lastHousePin-firstHousePin));
  }
  
  *isDay = (*isDay==1?0:1);
  Serial.print("La variabile isDay è stata impostata su: ");
  Serial.print((*isDay));

  Serial.print(". La transizione è finita.");
  digitalWrite(LED_BUILTIN, LOW);

  matrix.renderBitmap((*isDay==1?sun:moon), 8, 12);
}

void testConnections(){
  for(int i = firstHousePin; i < lastHousePin+1; i++){
    digitalWrite(i, LOW);
    delay(150);
  }
  digitalWrite(sunPin, LOW);

  delay(2500);

  for(int i = lastHousePin; i > firstHousePin-1; i--){
    digitalWrite(i, HIGH);
    delay(150);
  }
  digitalWrite(sunPin, HIGH);

  delay(2500);
}

void setup(){
  Serial.begin(9600);
  matrix.begin();

  matrix.loadSequence(LEDMATRIX_ANIMATION_STARTUP);
  matrix.play(true);

  for(int i = firstHousePin; i < lastHousePin+1; i++){
    pinMode(i, OUTPUT);
  }
  pinMode(sunPin, OUTPUT);

  testConnections();

  for(int i = firstHousePin; i < lastHousePin+1; i++){
    digitalWrite(i, LOW);
    delay(150);
  }
  digitalWrite(sunPin, LOW);

  matrix.renderBitmap(empty, 8, 12);
}

void loop(){
  timeNow = millis();
  if(timeNow-lastChange >= dayDuration*1000){
    Serial.print("\nSono passati ");
    Serial.print(dayDuration);
    Serial.print(" secondi dall'ultimo giorno. \n");
    normalTransition(&isDay);
    lastChange = millis();
  }
}