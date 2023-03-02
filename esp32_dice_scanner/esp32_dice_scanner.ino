/*
 * esp32 dice scanner 
 * 
 * it should works on every esp32 board with antenna
 * after upload, open ur serial terminal to see the output
 * 
 * https://github.com/libc0607/GI_Dice
 */

#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include <BLEBeacon.h>

#define DICE_NAME_PREFIX  "Dice"
#define DICE_MANUFACTURER_DATA_PREFIX  "GI"
#define DICE_SERVICE_UUID_PREFIX_STR "0000fff0"
#define DICE_MANUFACTURER_DATA_LEN 4

int scanTime = 1; //In seconds
BLEScan *pBLEScan;

class DiceAdvFilterCallbacks : public BLEAdvertisedDeviceCallbacks
{
    void onResult(BLEAdvertisedDevice advertisedDevice) 
    {
      if (!advertisedDevice.haveName()) {
        return;
      }
      String strDiceName = advertisedDevice.getName().c_str();
      if (!strDiceName.startsWith(DICE_NAME_PREFIX)) {
        return;
      }
      if (!advertisedDevice.haveServiceUUID()) {
        return;
      } 
      String strDiceServiceUUID = advertisedDevice.getServiceUUID().toString().c_str();
      if (!strDiceServiceUUID.startsWith(DICE_SERVICE_UUID_PREFIX_STR)) {
        return;
      } 
      if ((!advertisedDevice.haveManufacturerData())) {
        return;
      } 
      String strManufacturerData = advertisedDevice.getManufacturerData().c_str();
      if (!strManufacturerData.startsWith(DICE_MANUFACTURER_DATA_PREFIX)) {
        return;
      }
      int diceBatMv = strManufacturerData[2]*4+3200;
      uint8_t diceOri = strManufacturerData[3];
      int diceRSSI = advertisedDevice.getRSSI();
      Serial.printf("Found: %s, ori %d, bat %d mV, RSSI %d dBm\n", strDiceName, diceOri, diceBatMv, diceRSSI);
    }
};

void setup()
{
  Serial.begin(115200);
  BLEDevice::init("");
  pBLEScan = BLEDevice::getScan(); 
  pBLEScan->setAdvertisedDeviceCallbacks(new DiceAdvFilterCallbacks());
  pBLEScan->setActiveScan(true); 
  pBLEScan->setInterval(200);
  pBLEScan->setWindow(199); 
}

void loop()
{
  BLEScanResults foundDevices = pBLEScan->start(scanTime, false);
  pBLEScan->clearResults(); 
  Serial.printf("Start new scan, heap=%d\n", ESP.getFreeHeap());
}
