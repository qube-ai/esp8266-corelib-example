#if defined(RELEASE)
#include <Arduino.h>

#include "ArduinoJson.h"
#include "corelib.h"
#include <CloudIoTCore.h>
#include <CloudIoTCoreMqtt.h>

long last_state_time = 0;
#define SENDING_PERIOD 10000

void myCallback(MQTTClient *client, char topic[], StaticJsonDocument<120> doc)
{
  // Serialize and create a new JSON string representation
  String final_payload;
  serializeJson(doc, final_payload);
  Serial.print("myCallback payload -> ");
  Serial.println(final_payload);
}

String deviceState()
{
  StaticJsonDocument<2096> doc;

  doc["fw_version"] = "1.0";
  doc["on_time"] = millis() / 1000;

  // Prepare the message to be sent to IoT Core
  String message_string;
  serializeJson(doc, message_string);
  iotcore::publishState(message_string);

  return message_string;
}

void setup()
{
  Serial.begin(115200);
  delay(100);

  corelib::setup();

  // Get IoTCore details
  char project_id[20] = "";
  storage::getProjectID(project_id);
  Serial.printf("Project ID -> %s\n", project_id);

  char location[20] = "";
  storage::getLocation(location);
  Serial.printf("Location -> %s\n", location);

  char registry_id[20] = "";
  storage::getRegistryID(registry_id);
  Serial.printf("Registry ID -> %s\n", registry_id);

  char device_id[20] = "";
  storage::getDeviceID(device_id);
  Serial.printf("Device ID -> %s\n", device_id);

  // Setup callback for IoTCore
  messageHandler::registerUserCallback(myCallback);
  messageHandler::registerDeviceStateFunction(deviceState);

  Serial.println("All work in setup section is complete.");
}

void loop()
{
  corelib::loop();

  if (millis() - last_state_time > SENDING_PERIOD)
  {
    Serial.print("Running device state function...");
    deviceState();
    last_state_time = millis();
    Serial.println("DONE");
  }
}
#endif