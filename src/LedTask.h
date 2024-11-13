
#include "GlobalData.h"

// define tasks
void ledTask( void *pvParameters );


int oneTick = 200 / portTICK_RATE_MS; // delay for one element 200 msec

//----------------------------------- Main Task -------------------------------

void ledTask(void *pvParameters) {

  // initialize digital LED_BUILTIN on pin 13 as an output.
  pinMode(LED_1, OUTPUT);
  pinMode(DOOR_INPUT, INPUT_PULLUP);

  while (true) // A Task shall never return or exit.
  {
    gDoorState = digitalRead(DOOR_INPUT); // 1 = DOOR OPEN
    gDoorState = gDoorState == 1 ? 0 : 1;

    if (gDoorState == 0) {
      digitalWrite(LED_1, HIGH);  // Turn the LED on by making the voltage HIGH
    }
    else {
      digitalWrite(LED_1, LOW);   // Turn the LED off (Note that LOW is the voltage level
    }
    vTaskDelay(oneTick);  // one tick delay (15ms) in between reads for stability
  }
}
