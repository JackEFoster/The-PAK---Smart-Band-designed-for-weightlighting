#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>


float X;
float Y;
float Z;
int repCount;
float threshhold = 0.19;
float threshhold2 = 0.35;
float mag;
float avgmag;
int rep;
bool moving = false;
bool stop = true;
int ceilling = 9999999999;
int yuh;
int welit;

/// moving average stuff
const int arraySize = 5;
float Xcord = 0;
float sumx = 0;
int countx = 0; // count for array position
static float arrayX[arraySize];
float averagex;

float Ycord = 0;
float sumy = 0;
static float arrayY[arraySize];
int county = 0; // count for array position
float averagey;

float Zcord = 0;
float sumz = 0;
static float arrayZ[arraySize];
int countz = 0; // count for array position
float averagez;

//calibration stuff
const int arraySizec = 5000;
float Xcordc = 0;
float sumxc = 0;
int countxc = 0; // count for array position
static float arrayXc[arraySizec];
float averagexc=0;

float Ycordc = 0;
float sumyc = 0;
static float arrayYc[arraySizec];
int countyc = 0; // count for array position
float averageyc=0;

float Zcordc = 0;
float sumzc = 0;
static float arrayZc[arraySizec];
int countzc = 0; // count for array position
float averagezc=0;
float calmag;
bool buttonstate;

//motor stuff
int buzz = 13;
String value;
int Temp0;
int Temp2;
int Temp3;
int Temp4;
int Temp5;
int Temp6;
//tempo
//3.5 seconds
unsigned long previousMillis = 0;
bool starttemp = false;
//0 to 250 buzz
/*
const unsigned long up = 125;
//500 - 600 buzz
const unsigned long start1 = 200;
const unsigned long start2 = 225;
//1500 - 1600 buzz
const unsigned long sec11 = 725;
const unsigned long sec12 = 750;

const unsigned long sec21 = 1250;
const unsigned long sec22 = 1275;

const unsigned long sec31 = 1775;
const unsigned long sec32 = 1800;
*/
const unsigned long up = 1000;
//500 - 600 buzz
const unsigned long start1 = 1100;
const unsigned long start2 = 1200;
//1500 - 1600 buzz
const unsigned long sec11 = 2100;
const unsigned long sec12 = 2200;

const unsigned long sec21 = 3100;
const unsigned long sec22 = 3200;

const unsigned long sec31 = 4100;
const unsigned long sec32 = 4200;

const unsigned long sec41 = 5100;
const unsigned long sec42 = 5200;

const unsigned long sec51 = 6100;
const unsigned long sec52 = 6200;

const unsigned long sec61 = 7100;
const unsigned long sec62 = 7200;

const unsigned long sec3 = 3300;
const unsigned long sec4 = 4300;
const unsigned long sec5 = 5300;
const unsigned long sec6 = 6300;
const unsigned long sec7 = 7300;

unsigned long currentMillis = 0;

volatile unsigned long int counter = 0;
volatile unsigned long int motion = 0;

#define SERVICE_UUID           "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID_TX "beb5483e-36e1-4688-b7f5-ea07361b26a8"
#define CHARACTERISTIC_UUID_RX "beb5483e-36e1-4689-b7f5-ea07361b26a8"

static BLEUUID serviceUUID("4fafc201-1fb5-459e-8fcc-c5c9c331914b");
static BLEUUID charUUID("beb5483e-36e1-4689-b7f5-ea07361b26a8");



BLEServer* pServer = NULL;
BLECharacteristic* pCharacteristic = NULL;
BLECharacteristic* pCharacteristic2 = NULL;
bool deviceConnected = false;
int txValue = 0;
bool oldDeviceConnected = false;

class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };
    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};

class MyClientCallback : public BLEClientCallbacks {
  void onConnect(BLEClient* pClient) {
    Serial.println("Connected to server");
  }

  void onDisconnect(BLEClient* pClient) {
    Serial.println("Disconnected from server");
  }
};
class MyCharacteristicCallbacks : public BLECharacteristicCallbacks {
public:
  void onWrite(BLECharacteristic *pCharacteristic2) {
    std::string value = pCharacteristic2->getValue();
    Serial.print("Received value: ");
    Serial.println(value.c_str());
  }
};

class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic2) {
      std::string value = pCharacteristic2->getValue();

      if (value.length() > 0) {
        Serial.println("*********");
        Serial.print("New value: ");
        for (int i = 0; i < value.length(); i++)
          Serial.print(value[i]);
          if(value == "0"){
            Temp0 = 0;
            Temp2 = 1;
            Temp3 = 1;
            Temp4 = 1;
            Temp5 = 1;
            Temp6 = 1;
          }
          if(value == "2"){
            Temp0 = 1;
            Temp2 = 2;
            Temp3 = 1;
            Temp4 = 1;
            Temp5 = 1;
            Temp6 = 1;
          }
          if(value == "3"){
            Temp0 = 1;
            Temp2 = 1;
            Temp3 = 3;
            Temp4 = 1;
            Temp5 = 1;
            Temp6 = 1;
          }
          if(value == "4"){
            Temp0 = 1;
            Temp2 = 1;
            Temp3 = 1;
            Temp4 = 4;
            Temp5 = 1;
            Temp6 = 1;
          }
          if(value == "5"){
            Temp0 = 1;
            Temp2 = 1;
            Temp3 = 1;
            Temp4 = 1;
            Temp5 = 5;
            Temp6 = 1;
          }
          if(value == "6"){
            Temp0 = 1;
            Temp2 = 1;
            Temp3 = 1;
            Temp4 = 1;
            Temp5 = 1;
            Temp6 = 6;
          }
          

        Serial.println();
        Serial.println("*********");
      }
    }
};

void setup()
{
  // Debug console
  Serial.begin(115200);
  pinMode(26, INPUT);
  pinMode(buzz, OUTPUT);
  pinMode(33, INPUT);  //X
  pinMode(35, INPUT);  //Y
  pinMode(34, INPUT);  //Z
  pinMode(buzz,OUTPUT);
  // moving average setup
  Serial.setTimeout(10);
  //initialize array to zeros
  for (int ii =  0; ii < arraySize ; ii++) {
    arrayX[ii] = 0;
    arrayY[ii] = 0;
    arrayZ[ii] = 0;
  }
  BLEDevice::init("ESP32");
  //create server

  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());
  //Create the BLE Service
  BLEService *pService = pServer->createService(SERVICE_UUID);

    //Create a BLE Characteristic
  pCharacteristic = pService->createCharacteristic(
  CHARACTERISTIC_UUID_TX,
  BLECharacteristic::PROPERTY_READ |
  BLECharacteristic::PROPERTY_WRITE |
  BLECharacteristic::PROPERTY_NOTIFY 
  );
  BLECharacteristic *pCharacteristic2 = pService->createCharacteristic(
    CHARACTERISTIC_UUID_RX,
    BLECharacteristic::PROPERTY_READ |
    BLECharacteristic::PROPERTY_WRITE
  );
  pService->addCharacteristic(pCharacteristic);
  pService->addCharacteristic(pCharacteristic2);
  //BLE2902 needed to notify
  pCharacteristic->addDescriptor(new BLE2902());
  //recieve value from the app
  pCharacteristic2->setCallbacks(new MyCallbacks());


  //Start the Service
  pService->start();

  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(false);
  pAdvertising->setMinPreferred(0x0);  // set value to 0x00 to not advertise this parameter
  BLEDevice::startAdvertising();
  Serial.println("Waiting a client connection to notify...");
 
}

void loop()
{

  X=analogRead(33);
  Y=analogRead(35);
  Z=analogRead(34);
  float xG = ((1 / 418.000) * X) - (1934.000 / 418.000);
  float yG = ((1 / 408.000) * Y) - (1968.00 / 408.000);
  float zG = ((1 / 415.000) * Z) - (2000.000 / 415.000); //double check scale for Z
  
  mag = sqrt(pow(xG, 2) + pow(yG, 2) + pow(zG - 1, 2));
  //
  Xcord = xG;
  averagex = movingAverageX(Xcord);

  Ycord = yG;
  averagey = movingAverageY(Ycord);

  Zcord = zG;
  averagez = movingAverageZ(Zcord);

  buttonstate = digitalRead(26);
  //Serial.print(buttonstate);
//pin 13 
unsigned long currentMillis = millis();
  if (Temp0 == 0){
      //Serial.print("success");
      if (currentMillis - previousMillis >= up) {
          previousMillis = currentMillis;
          digitalWrite(buzz, LOW);
        }
      }
  if (Temp2 == 2){
        if(starttemp ==false){
        previousMillis = currentMillis;
        starttemp = true;
        }
        if ((currentMillis - previousMillis) <= up) {
          digitalWrite(buzz, HIGH);
          Serial.println("1");         
          Serial.println("_________"); 
        }
        if ((currentMillis - previousMillis) > up && (currentMillis - previousMillis) < start1) {
          digitalWrite(buzz, LOW);
          Serial.println("2");
          Serial.println("_________");          
        }        
        if ((currentMillis - previousMillis) >= start1 && (currentMillis - previousMillis) < start2) {

          digitalWrite(buzz, HIGH);       
          Serial.println("3");
          Serial.println("_________");   
        }
        if ((currentMillis - previousMillis) >= start2 && (currentMillis - previousMillis) < sec11) {
          digitalWrite(buzz, LOW);
          Serial.println("4");
          Serial.println("_________");  
        }
        if ((currentMillis - previousMillis) >= sec11 && (currentMillis - previousMillis) < sec12) {
          digitalWrite(buzz, HIGH);
          Serial.println("5");
          Serial.println("_________");  
        }
        if ((currentMillis - previousMillis) >= sec12 && (currentMillis - previousMillis) < sec21) {
          digitalWrite(buzz, LOW);
          Serial.println("6");
          Serial.println("_________");  
        }
        if ((currentMillis - previousMillis) >= sec21 && (currentMillis - previousMillis) < sec22) {
          digitalWrite(buzz, HIGH);
          Serial.println("7");
          Serial.println("_________"); 
        }
          if ((currentMillis - previousMillis) >= sec22 && (currentMillis - previousMillis) < sec3) {
          digitalWrite(buzz, LOW);
          Serial.println("7");
          Serial.println("_________");  
        }
      }
        else if (Temp2 == 2 && calmag<=threshhold){
         digitalWrite(buzz, LOW);
         starttemp = false; 
        }
  //Serial.print(Temp3);
  if (Temp3 == 3 && calmag>=threshhold){
        if(starttemp ==false){
        previousMillis = currentMillis;
        starttemp = true;
        }
        if ((currentMillis - previousMillis) <= up) {
          digitalWrite(buzz, HIGH);
          Serial.println("1");         
          Serial.println("_________"); 
        }
        if ((currentMillis - previousMillis) > up && (currentMillis - previousMillis) < start1) {
          digitalWrite(buzz, LOW);
          Serial.println("2");
          Serial.println("_________");          
        }        
        if ((currentMillis - previousMillis) >= start1 && (currentMillis - previousMillis) < start2) {

          digitalWrite(buzz, HIGH);       
          Serial.println("3");
          Serial.println("_________");   
        }
        if ((currentMillis - previousMillis) >= start2 && (currentMillis - previousMillis) < sec11) {
          digitalWrite(buzz, LOW);
          Serial.println("4");
          Serial.println("_________");  
        }
        if ((currentMillis - previousMillis) >= sec11 && (currentMillis - previousMillis) < sec12) {
          digitalWrite(buzz, HIGH);
          Serial.println("5");
          Serial.println("_________");  
        }
        if ((currentMillis - previousMillis) >= sec12 && (currentMillis - previousMillis) < sec21) {
          digitalWrite(buzz, LOW);
          Serial.println("6");
          Serial.println("_________");  
        }
        if ((currentMillis - previousMillis) >= sec21 && (currentMillis - previousMillis) < sec22) {
          digitalWrite(buzz, HIGH);
          Serial.println("7");
          Serial.println("_________"); 
        }

        if ((currentMillis - previousMillis) >= sec22 && (currentMillis - previousMillis) < sec31) {
          digitalWrite(buzz, LOW);
          Serial.println("8");
          Serial.println("_________");  
        }
        if ((currentMillis - previousMillis) >= sec31 && (currentMillis - previousMillis) < sec32) {
          digitalWrite(buzz, HIGH);
          Serial.println("9");
          Serial.println("_________");  
        }

        if ((currentMillis - previousMillis) >= sec32 && (currentMillis - previousMillis) < sec4) {
          digitalWrite(buzz, LOW);
          starttemp = false;
          Serial.println("3secondtemp");
          Serial.println("_________");

        }

      }
        else if (Temp3 == 3 && calmag<=threshhold){
         digitalWrite(buzz, LOW);
         starttemp = false; 
        }
  
  if (Temp4 == 4){
        if(starttemp ==false){
        previousMillis = currentMillis;
        starttemp = true;
        }
        if ((currentMillis - previousMillis) <= up) {
          digitalWrite(buzz, HIGH);
          Serial.println("1");         
          Serial.println("_________"); 
        }
        if ((currentMillis - previousMillis) > up && (currentMillis - previousMillis) < start1) {
          digitalWrite(buzz, LOW);
          Serial.println("2");
          Serial.println("_________");          
        }        
        if ((currentMillis - previousMillis) >= start1 && (currentMillis - previousMillis) < start2) {

          digitalWrite(buzz, HIGH);       
          Serial.println("3");
          Serial.println("_________");   
        }
        if ((currentMillis - previousMillis) >= start2 && (currentMillis - previousMillis) < sec11) {
          digitalWrite(buzz, LOW);
          Serial.println("4");
          Serial.println("_________");  
        }
        if ((currentMillis - previousMillis) >= sec11 && (currentMillis - previousMillis) < sec12) {
          digitalWrite(buzz, HIGH);
          Serial.println("5");
          Serial.println("_________");  
        }
        if ((currentMillis - previousMillis) >= sec12 && (currentMillis - previousMillis) < sec21) {
          digitalWrite(buzz, LOW);
          Serial.println("6");
          Serial.println("_________");  
        }
        if ((currentMillis - previousMillis) >= sec21 && (currentMillis - previousMillis) < sec22) {
          digitalWrite(buzz, HIGH);
          Serial.println("7");
          Serial.println("_________"); 
        }

        if ((currentMillis - previousMillis) >= sec22 && (currentMillis - previousMillis) < sec31) {
          digitalWrite(buzz, LOW);
          Serial.println("8");
          Serial.println("_________");  
        }
        if ((currentMillis - previousMillis) >= sec31 && (currentMillis - previousMillis) < sec32) {
          digitalWrite(buzz, HIGH);
          Serial.println("9");
          Serial.println("_________");  
        }
        if ((currentMillis - previousMillis) >= sec32 && (currentMillis - previousMillis) < sec41) {
          digitalWrite(buzz, LOW);
          Serial.println("10");
          Serial.println("_________");  
        }
        if ((currentMillis - previousMillis) >= sec41 && (currentMillis - previousMillis) < sec42) {
          digitalWrite(buzz, HIGH);
          Serial.println("11");
          Serial.println("_________");  
        }        

        if ((currentMillis - previousMillis) >= sec42 && (currentMillis - previousMillis) < sec5) {
          digitalWrite(buzz, LOW);
          starttemp = false;
          Serial.println("4secondtemp");
          Serial.println("_________");

        }
  }
        else if (Temp4 == 4 && calmag<=threshhold){
         digitalWrite(buzz, LOW);
         starttemp = false; 
        }
  if (Temp5 == 5){
        if(starttemp ==false){
        previousMillis = currentMillis;
        starttemp = true;
        }
        if ((currentMillis - previousMillis) <= up) {
          digitalWrite(buzz, HIGH);
          Serial.println("1");         
          Serial.println("_________"); 
        }
        if ((currentMillis - previousMillis) > up && (currentMillis - previousMillis) < start1) {
          digitalWrite(buzz, LOW);
          Serial.println("2");
          Serial.println("_________");          
        }        
        if ((currentMillis - previousMillis) >= start1 && (currentMillis - previousMillis) < start2) {

          digitalWrite(buzz, HIGH);       
          Serial.println("3");
          Serial.println("_________");   
        }
        if ((currentMillis - previousMillis) >= start2 && (currentMillis - previousMillis) < sec11) {
          digitalWrite(buzz, LOW);
          Serial.println("4");
          Serial.println("_________");  
        }
        if ((currentMillis - previousMillis) >= sec11 && (currentMillis - previousMillis) < sec12) {
          digitalWrite(buzz, HIGH);
          Serial.println("5");
          Serial.println("_________");  
        }
        if ((currentMillis - previousMillis) >= sec12 && (currentMillis - previousMillis) < sec21) {
          digitalWrite(buzz, LOW);
          Serial.println("6");
          Serial.println("_________");  
        }
        if ((currentMillis - previousMillis) >= sec21 && (currentMillis - previousMillis) < sec22) {
          digitalWrite(buzz, HIGH);
          Serial.println("7");
          Serial.println("_________"); 
        }

        if ((currentMillis - previousMillis) >= sec22 && (currentMillis - previousMillis) < sec31) {
          digitalWrite(buzz, LOW);
          Serial.println("8");
          Serial.println("_________");  
        }
        if ((currentMillis - previousMillis) >= sec31 && (currentMillis - previousMillis) < sec32) {
          digitalWrite(buzz, HIGH);
          Serial.println("9");
          Serial.println("_________");  
        }
        if ((currentMillis - previousMillis) >= sec32 && (currentMillis - previousMillis) < sec41) {
          digitalWrite(buzz, LOW);
          Serial.println("10");
          Serial.println("_________");  
        }
        if ((currentMillis - previousMillis) >= sec41 && (currentMillis - previousMillis) < sec42) {
          digitalWrite(buzz, HIGH);
          Serial.println("11");
          Serial.println("_________");  
        }        
        if ((currentMillis - previousMillis) >= sec42 && (currentMillis - previousMillis) < sec51) {
          digitalWrite(buzz, LOW);
          Serial.println("12");
          Serial.println("_________");  
        }
        if ((currentMillis - previousMillis) >= sec51 && (currentMillis - previousMillis) < sec52) {
          digitalWrite(buzz, HIGH);
          Serial.println("13");
          Serial.println("_________");  
        }        
        if ((currentMillis - previousMillis) >= sec52 && (currentMillis - previousMillis) < sec6) {
          digitalWrite(buzz, LOW);
          starttemp = false;
          Serial.println("5secondtemp");
          Serial.println("_________");

        }
  }
        else if (Temp5 == 5 && calmag<=threshhold){
         digitalWrite(buzz, LOW);
         starttemp = false; 
        }
  if (Temp6 == 6){
        if(starttemp ==false){
        previousMillis = currentMillis;
        starttemp = true;
        }
        if ((currentMillis - previousMillis) <= up) {
          digitalWrite(buzz, HIGH);
          Serial.println("1");         
          Serial.println("_________"); 
        }
        if ((currentMillis - previousMillis) > up && (currentMillis - previousMillis) < start1) {
          digitalWrite(buzz, LOW);
          Serial.println("2");
          Serial.println("_________");          
        }        
        if ((currentMillis - previousMillis) >= start1 && (currentMillis - previousMillis) < start2) {

          digitalWrite(buzz, HIGH);       
          Serial.println("3");
          Serial.println("_________");   
        }
        if ((currentMillis - previousMillis) >= start2 && (currentMillis - previousMillis) < sec11) {
          digitalWrite(buzz, LOW);
          Serial.println("4");
          Serial.println("_________");  
        }
        if ((currentMillis - previousMillis) >= sec11 && (currentMillis - previousMillis) < sec12) {
          digitalWrite(buzz, HIGH);
          Serial.println("5");
          Serial.println("_________");  
        }
        if ((currentMillis - previousMillis) >= sec12 && (currentMillis - previousMillis) < sec21) {
          digitalWrite(buzz, LOW);
          Serial.println("6");
          Serial.println("_________");  
        }
        if ((currentMillis - previousMillis) >= sec21 && (currentMillis - previousMillis) < sec22) {
          digitalWrite(buzz, HIGH);
          Serial.println("7");
          Serial.println("_________"); 
        }

        if ((currentMillis - previousMillis) >= sec22 && (currentMillis - previousMillis) < sec31) {
          digitalWrite(buzz, LOW);
          Serial.println("8");
          Serial.println("_________");  
        }
        if ((currentMillis - previousMillis) >= sec31 && (currentMillis - previousMillis) < sec32) {
          digitalWrite(buzz, HIGH);
          Serial.println("9");
          Serial.println("_________");  
        }
        if ((currentMillis - previousMillis) >= sec32 && (currentMillis - previousMillis) < sec41) {
          digitalWrite(buzz, LOW);
          Serial.println("10");
          Serial.println("_________");  
        }
        if ((currentMillis - previousMillis) >= sec41 && (currentMillis - previousMillis) < sec42) {
          digitalWrite(buzz, HIGH);
          Serial.println("11");
          Serial.println("_________");  
        }        
        if ((currentMillis - previousMillis) >= sec42 && (currentMillis - previousMillis) < sec51) {
          digitalWrite(buzz, LOW);
          Serial.println("12");
          Serial.println("_________");  
        }
        if ((currentMillis - previousMillis) >= sec51 && (currentMillis - previousMillis) < sec52) {
          digitalWrite(buzz, HIGH);
          Serial.println("13");
          Serial.println("_________");  
        }      
        if ((currentMillis - previousMillis) >= sec52 && (currentMillis - previousMillis) < sec61) {
          digitalWrite(buzz, LOW);
          Serial.println("14");
          Serial.println("_________");  
        }
        if ((currentMillis - previousMillis) >= sec61 && (currentMillis - previousMillis) < sec62) {
          digitalWrite(buzz, HIGH);
          Serial.println("15");
          Serial.println("_________");  
        }   
        if ((currentMillis - previousMillis) >= sec62 && (currentMillis - previousMillis) < sec7) {
          digitalWrite(buzz, LOW);
          starttemp = false;
          Serial.println("6secondtemp");
          Serial.println("_________");

        }
  }
        else if (Temp6 == 6 && calmag<=threshhold){
         digitalWrite(buzz, LOW);
         starttemp = false; 
        }
  ///calibration
  /// why is this count to 11?????????????
  if (buttonstate == HIGH){
    for (int cc = 0; cc < arraySizec; cc++) {
      yuh = 0;
      Xcordc = xG;
      averagexc = CalX(Xcordc);

      Ycordc = yG;
      averageyc = CalY(Ycordc);

      Zcordc = zG;
      averagezc = CalZ(Zcordc);

    }
  }

//avgmag no cal
  avgmag = sqrt(pow(averagex, 2) + pow(averagey, 2) + pow(averagez, 2));
//cal mag
  calmag = sqrt(pow(averagex-averagexc, 2) + pow(averagey-averageyc, 2) + pow(averagez-averagezc, 2));
  Serial.println(calmag);
  Serial.println("______");
  //Serial.println(welit);
  //Serial.println("______");
  //Serial.println(yuh);
  //Serial.println("______");

  if (calmag >= threshhold ) {
/*
        if(starttemp2 ==false){
        previousMillis2 = currentMillis;
        starttemp = true;
        }
*/
    repCount++;
    moving = true;
    stop = false;
  }
  else if (calmag < threshhold2) {
    ceilling = repCount - 1;
    moving = false;
    //Serial.print("2");
    //Serial.println("________");
    //Serial.println(averagex);
    if (ceilling < repCount & stop == false) {
      yuh++;
      welit = yuh - 1;
      stop = true;
      repCount = 0;
      ceilling = 999999999;
      //Serial.print("3");

    }
    if (welit >= 10) {
      yuh = 1;
      rep++;
    }
    //  displayArray();
  }

  if(deviceConnected){
    //txValue =80085;
    txValue = welit;


    //Conversion TxVAlue
    char txString[8];
    dtostrf(txValue,1,2,txString);

    //Setting value to characterisitc
    pCharacteristic->setValue(txString);

    //Notify the connected client
    pCharacteristic->notify();
    //Serial.println(String(txString));
    delay(100);
  }
    if (!deviceConnected && oldDeviceConnected) {
        delay(100); // give the bluetooth stack the chance to get things ready
        pServer->startAdvertising(); // restart advertising
        Serial.println("start advertising");
        oldDeviceConnected = deviceConnected;
    }
    // connecting
    if (deviceConnected && !oldDeviceConnected) {
        // do stuff here on connecting
        oldDeviceConnected = deviceConnected;
    }
}

void displayArray() { // Display everything
  for (int ii =  0; ii <= 9; ii++) {


    Serial.print(arrayX[ii]);
    Serial.print(" ");
    Serial.print(averagex);
    Serial.print("     ");
    Serial.print(averagey);
    Serial.print("     ");
    Serial.print(averagez);
    Serial.print("     ");
    Serial.print(avgmag);
    Serial.print("     ");
    Serial.println(welit);
  }
  Serial.println();
}
int recieve(){
  std::string value = pCharacteristic2->getValue();
  Serial.print("Received value: ");
  Serial.println(value.c_str());
}
//smoothing
float movingAverageX(float vx) {
  //first check to make sure that we haven't reached the end of the array
  if (countx >= arraySize) {
    countx = 0;
  }
  arrayX[countx] = vx; //set the value in place
  countx++; //increment count
  for (int jj = 0; jj < arraySize; jj++) {
    sumx = sumx + arrayX[jj];
  }

  float avgx = sumx / arraySize;
  sumx = 0;//reset sum
  return avgx;
}
float movingAverageY(float vy) {
  //first check to make sure that we haven't reached the end of the array
  if (county >= arraySize) {
    county = 0;
  }
  arrayY[county] = vy; //set the value in place
  county++; //increment count
  for (int jj = 0; jj < arraySize; jj++) {
    sumy = sumy + arrayY[jj];
  }

  float avgy = sumy / arraySize;
  sumy = 0;//reset sum
  return avgy;
}
float movingAverageZ(float vz) {
  //first check to make sure that we haven't reached the end of the array
  if (countz >= arraySize) {
    countz = 0;
  }
  arrayZ[countz] = vz; //set the value in place
  countz++; //increment count
  for (int jj = 0; jj < arraySize; jj++) {
    sumz = sumz + arrayZ[jj];
  }

  float avgz = sumz / arraySize;
  sumz = 0;//reset sum
  return avgz;

}
////caliiii boiiii
float CalX(float vxc) {
  //first check to make sure that we haven't reached the end of the array
  if (countxc >= arraySizec) {
    countxc = 0;
  }
  arrayXc[countxc] = vxc; //set the value in place
  countxc++; //increment count
  for (int kk = 0; kk < arraySizec; kk++) {
    sumxc = sumxc + arrayXc[kk];
  }

  float avgxc = sumxc / arraySizec;
  sumxc = 0;//reset sum
  return avgxc;
}
float CalY(float vyc) {
  //first check to make sure that we haven't reached the end of the array
  if (countyc >= arraySizec) {
    countyc = 0;
  }
  arrayYc[countyc] = vyc; //set the value in place
  countyc++; //increment count
  for (int kk = 0; kk < arraySizec; kk++) {
    sumyc = sumyc + arrayYc[kk];
  }

  float avgyc = sumyc / arraySizec;
  sumyc = 0;//reset sum
  return avgyc;
}
float CalZ(float vzc) {
  //first check to make sure that we haven't reached the end of the array
  if (countzc >= arraySizec) {
    countzc = 0;
  }
  arrayZc[countzc] = vzc; //set the value in place
  countzc++; //increment count
  for (int kk = 0; kk< arraySizec; kk++) {
    sumzc = sumzc + arrayZc[kk];
  }

  float avgzc = sumzc / arraySizec;
  sumzc = 0;//reset sum
  return avgzc;

}
