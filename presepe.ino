#include <LinkedList.h>
#include "Planet.h"
#include "House.h"
#include "Neighborhood.h"

#define dayDuration 60
#define houseTransitionDuration 20
#define housesTransitionDelay 10

#define true 1
#define false 0

TaskHandle_t sunTaskHandle;
TaskHandle_t moonTaskHandle;
TaskHandle_t housesTaskHandle;

Planet sun = Planet(16, true); //TODO: Set the correct pin for the sun light
Planet moon = Planet(17, true); //TODO: Set the correct pin for the moon light
Neighborhood neighborhood = Neighborhood();

unsigned long lastChange = 0;
int isDay = true;

void housesTask(void *pvParameters){
  Serial.print("--> housesTask è partita sul core ");
  Serial.println(xPortGetCoreID());

  int pinIndex = 0;

  for(;;){
    if(millis()-lastChange >= (dayDuration+housesTransitionDelay)*1000){
      Serial.print(isDay==1?"Accendo le luci delle case...":"Spengo le luci delle case...");
      if(isDay){
        neighborhood.turnOnHouses();
      }else{
        neighborhood.turnOffHouses();
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
      if(isDay){
        sun.turnOn();
      }else{
        sun.turnOff();
      }
      lastChange = millis();
    }
  }
}

void moonTask(void *pvParameters){
  Serial.print("--> sunTask è partita sul core ");
  Serial.println(xPortGetCoreID());

  for(;;){
    if(millis()-lastChange >= dayDuration*1000){
      Serial.println(isDay==1?"Faccio tramontare il sole...":"Faccio sorgere il sole...");
      if(isDay){
        moon.turnOff();
      }else{
        moon.turnOn();
      }
      lastChange = millis();
    }
  }
}

void testConnections(){

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

  Serial.print("Creo le luci e le aggiungo alla lista...");
  neighborhood.addHouse(House(32));
  neighborhood.addHouse(House(33));
  neighborhood.addHouse(House(25));
  neighborhood.addHouse(House(26));
  neighborhood.addHouse(House(27));
  neighborhood.addHouse(House(14));
  neighborhood.addHouse(House(12));
  neighborhood.addHouse(House(13));
  analogWrite(sun.getPin(), 255);
  analogWrite(moon.getPin(), 255);
  Serial.println(" Fatto!");

  Serial.print("Testo le connessioni...");
  testConnections();
  Serial.println("Fatto!");

  Serial.println("Avvio le task...");
  //...(function, name, stack size, parameter, priority, task handle, core)
  xTaskCreate(sunTask, "Task del sole", 10000, NULL, 1, &sunTaskHandle);
  xTaskCreate(moonTask, "Task della luna", 10000, NULL, 1, &moonTaskHandle);
  xTaskCreate(housesTask, "Task delle case", 10000, NULL, 1, &housesTaskHandle);
  Serial.println("\n\n\n");

}

void loop(){}