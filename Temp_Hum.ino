#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <DFRobot_DHT11.h>
DFRobot_DHT11 DHT;
#define DHT11_PIN 17

/*Service UUID*/
#define SERVICE_UUID "00000002-0000-0000-FDFD-FDFDFDFDFDFD"
/* Characteristic UUID*/
BLECharacteristic Tempeture(BLEUUID((uint16_t)0x2A1C), BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
BLECharacteristic Humidity(BLEUUID((uint16_t)0x2A6F), BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
static bool deviceConnected = false;

/*Indication of bluetooth when connected*/
class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* MyServer) {
       deviceConnected = true;
       delay(1000);
       }

    /*Indication of bluetooth when not connected*/
    void onDisconnect(BLEServer* MyServer) {
       deviceConnected = false;
       delay(5000);
       BLEDevice::startAdvertising();
    }
};

/*Bluetooth enabling code*/
void initBLE() {
  BLEDevice::init("Weather");
  BLEServer *MyServer = BLEDevice::createServer();
  MyServer->setCallbacks(new MyServerCallbacks());
  BLEService *pService = MyServer->createService(SERVICE_UUID);//creating the UART service
  pService->addCharacteristic (&Tempeture);
  pService->addCharacteristic(&Humidity);
  Tempeture.addDescriptor(new BLE2902());
  Humidity.addDescriptor(new BLE2902());
  Tempeture.setNotifyProperty(true);
  Humidity.setNotifyProperty(true);
  pService->start();
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  Serial.println("Characteristic defined! Now you can read it in your phone!");
}


void setup(){
  Serial.begin(115200);
  initBLE();  // Bluetooth is start working
}

void loop(){
  DHT.read(DHT11_PIN);
  Serial.print("temp:");
  Serial.print(DHT.temperature);
  Serial.print("  humi:");
  Serial.println(DHT.humidity);
  delay(1000);

if (deviceConnected){
          DHT.read(DHT11_PIN);
          Tempeture.setValue(DHT.temperature);// Sending the data to application through bluetooth
          Tempeture.notify();
          Humidity.setValue(DHT.humidity);// Sending the data to application through bluetooth
          Humidity.notify();
}
}