#include <Arduino_CAN.h>

void setup()
{
  Serial.begin(115200);
  while (!Serial) { }

  if (!CAN.begin(CanBitRate::BR_500k))
  {
    Serial.println("CAN.begin(...) failed.");
    for (;;) {}
  }
}

void loop()
{
CANBusData();

}

void CANBusData(){
    if (CAN.available())
  {
    CanMsg const msg = CAN.read();
    Serial.println(msg);
  }

}
