//la durata del giorno (in secondi)
#define dayDuration 180
#define transitionDuration 20
#define houseLightsChangeDelay 0
#define true 1
#define false 0

#define sunPin 3
#define firstHousePin 4
#define lastHousePin 11

void transitionWithHouses(int isDay){
  for(int i = 0; i < transitionDuration; i++){
    analogWrite(sunPin, abs((isDay*255)-(255/transitionDuration)*i));
    if(i > i*houseLightsChangeDelay){
      digitalWrite(random(firstHousePin, lastHousePin), isDay);
    }
    delay(1000);
  }
  
  isDay != isDay;

  for(int i = firstHousePin; i < lastHousePin+1; i++){
    digitalWrite(i, isDay);
  }
}

void transitionWithoutHouses(int isDay){
  for(int i = 0; i < 255; i++){
    analogWrite(sunPin, abs((isDay*255)-(255/transitionDuration)*i));
    delay(transitionDuration*1000/255);
  }

  for(int i = firstHousePin; i < lastHousePin+1; i++){
    digitalWrite(i, isDay);
    delay(random(1000,5000));
  }
  
  isDay != isDay;
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
}

void loop(){
  unsigned long time;
  unsigned long lastChange;
  int isDay = true;
  
  /*time = millis();
  if(time-lastChange >= dayDuration){
    time = lastChange;
    transition(isDay);
  }*/

  /*transitionWithHouses(isDay);

  delay(10000);

  transitionWithHouses(isDay);

  delay(10000);

  transitionWithHouses(isDay);

  delay(10000);

  transitionWithHouses(isDay);*/
}