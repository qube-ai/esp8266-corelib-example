#if defined(INIT_EEPROM)

#include <Arduino.h>

#include "corelib.h"

#define PROJECT_ID "podnet-switch"
#define CLOUD_LOCATION "us-central1"
#define REGISTRY_ID "test-registry"
#define DEVICE_ID "test-device-2"

#define SSID0 "Qube"
#define PASS0 "Deepwaves007"

#define SSID1 "Apoorva"
#define PASS1 "testing123"

#define SSID2 ""
#define PASS2 ""

#define SSID3 ""
#define PASS3 ""

#define SSID4 ""
#define PASS4 ""

void print_creds(storage::wifi_cred t)
{
	Serial.print("SSID = ");
	Serial.print(t.ssid);
	Serial.print("Pass = ");
	Serial.println(t.password);
}

void setup()
{
	Serial.begin(115200);
	while (!Serial)
		;

	Serial.print("Starting corelib setup...");
	corelib::setup();
	Serial.println("DONE");

	// Set WiFi creds
	Serial.print("Setting WiFi credentials...");
	storage::setWiFiCreds(0, SSID0, PASS0);
	storage::setWiFiCreds(1, SSID1, PASS1);
	storage::setWiFiCreds(2, SSID2, PASS2);
	storage::setWiFiCreds(3, SSID3, PASS3);
	storage::setWiFiCreds(4, SSID4, PASS4);
	Serial.println("DONE");

	// Get WiFi Creds
	storage::wifi_cred cred1 = storage::getWiFiCreds(0);
	storage::wifi_cred cred2 = storage::getWiFiCreds(1);
	storage::wifi_cred cred3 = storage::getWiFiCreds(2);
	storage::wifi_cred cred4 = storage::getWiFiCreds(3);
	storage::wifi_cred cred5 = storage::getWiFiCreds(4);

	Serial.printf("Credential 1 SSID: %s, Pass: %s\n", cred1.ssid,
		      cred1.password);
	Serial.printf("Credential 2 SSID: %s, Pass: %s\n", cred2.ssid,
		      cred2.password);
	Serial.printf("Credential 3 SSID: %s, Pass: %s\n", cred3.ssid,
		      cred3.password);
	Serial.printf("Credential 4 SSID: %s, Pass: %s\n", cred4.ssid,
		      cred4.password);
	Serial.printf("Credential 5 SSID: %s, Pass: %s\n", cred5.ssid,
		      cred5.password);

	// Set IoTCore details
	Serial.print("Setting Google Cloud Credentials...");
	storage::setProjectID(PROJECT_ID);
	storage::setLocation(CLOUD_LOCATION);
	storage::setRegistryID(REGISTRY_ID);
	storage::setDeviceID(DEVICE_ID);
	storage::setTimezone(19800);
	Serial.println("DONE");

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

	Serial.println("Device Setup complete.");
}

void loop() {}

#endif