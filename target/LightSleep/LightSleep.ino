extern "C" {
#include "user_interface.h"
}

#define SLEEP_TIME  10

unsigned long last_print_time;
const unsigned long print_interval = 10e6;

void setup() {
  Serial.begin(115200);
  wifi_set_sleep_type(LIGHT_SLEEP_T);
  last_print_time = micros();
}

void loop() {
  unsigned long time_now = micros();

  if((time_now - last_print_time) > print_interval) {
    Serial.print("tempo total: ");
    Serial.print(time_now/1e6);
    Serial.println("");
    last_print_time = time_now;
  }
  delay(SLEEP_TIME);
}
