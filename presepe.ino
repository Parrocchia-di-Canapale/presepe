#include <LinkedList.h>

#define dayDuration 60
#define transitionDuration 20
#define houseTransitionDuration 20
#define housesTransitionDelay 10

#define true 1
#define false 0

#define sunPin 10
#define firstHousePin 0
#define lastHousePin 7

TaskHandle_t sunTaskHandle;
TaskHandle_t housesTaskHandle;
LinkedList<int> pinList = LinkedList<int>();

unsigned long lastChange = 0;
int isDay = true;

void housesTask(void *pvParameters){
  Serial.print("--> housesTask è partita sul core ");
  Serial.println(xPortGetCoreID());

  int pinIndex = 0;

  for(;;){
    if(pinList.size() != lastHousePin-firstHousePin+1){
      Serial.println("Ricostruisco la lista dei pin...");
      /*Serial.print(pinList.size());
      Serial.print(lastHousePin-firstHousePin);
      Serial.println(")...");
      delay(1000);*/
      for(int i = firstHousePin; i < lastHousePin+1; i++){
        pinList.add(i);
      }
    }

    if(millis()-lastChange >= (dayDuration+housesTransitionDelay)*1000){
      Serial.print(isDay==1?"Accendo le luci delle case...":"Spengo le luci delle case...");
      Serial.println(!isDay);
      for(int i = firstHousePin; i < lastHousePin+1; i++){
        pinIndex = random(0, pinList.size());
        digitalWrite(pinList.get(pinIndex), !isDay);
        delay(random(500, 2500));
        pinList.remove(pinIndex);
      }

      isDay = (isDay==1?0:1);
      Serial.print("Ho impostato il giorno su ");
      Serial.println(isDay);
    }
  }
}

void sunTask(void *pvParameters){
  Serial.print("--> sunTask è partita sul core ");
  Serial.println(xPortGetCoreID());

  for(;;){
    if(millis()-lastChange >= dayDuration*1000){
      Serial.println(isDay==1?"Faccio tramontare il sole...":"Faccio sorgere il sole...");

      for(int i = 0; i < 256; i++){
        analogWrite(sunPin, abs(((isDay)*255)-i)); //(-1.0+pow(1.022,i))
        delay(transitionDuration*1000/255);
      }
      lastChange = millis();
    }
  }
}

void testConnections(){
  for(int i = firstHousePin; i < lastHousePin+1; i++){
    digitalWrite(i, LOW);
    delay(50);
  }
  digitalWrite(sunPin, LOW);

  delay(150);

  for(int i = lastHousePin; i > firstHousePin-1; i--){
    digitalWrite(i, HIGH);
    delay(50);
  }
  digitalWrite(sunPin, HIGH);
}

void clearSerial(){
  Serial.print("\n\n\n");
  for(int i = 0; i < 100; i++){
    Serial.print(("-"));
  }
  Serial.print("\n\n\n");
}

void setup(){
  Serial.begin(9600);
  delay(1000);

  clearSerial();

  Serial.print("Imposto i pin e li inserisco nella lista...");
  for (int i = firstHousePin; i < lastHousePin+1; i++) {
    pinMode(i, OUTPUT);
    pinList.add(i);
  }
  analogWrite(sunPin, 255);
  Serial.println(" Fatto!");

  Serial.print("Testo le connessioni...");
  testConnections();
  Serial.println("Fatto!");

  Serial.println("Avvio le task...");
  //...(function, name, stack size, parameter, priority, task handle, core)
  xTaskCreate(sunTask, "Task del sole", 10000, NULL, 1, &sunTaskHandle);
  xTaskCreate(housesTask, "Task delle case", 10000, NULL, 1, &housesTaskHandle);
  Serial.println("\n\n\n");

}

void loop(){}