/*  
Bluetooth test application with power control
Copyright 2022, Digame Systems. All rights reserved.    
 */


// Includes
#include <esp_bt.h>          // Espressif's bluetooth library
#include "BluetoothSerial.h" // Part of the ESP32 board package
                             //   By Evandro Copercini - 2018

// Defines
#define debugUART Serial

// Globals
BluetoothSerial btUART;      // Create a BT serial port
long int counter = 0;


// Declares
void splash();
void readPowers();
void setPowers(esp_power_level_t power);
void adjustPower(esp_power_level_t power);


//****************************************************************************************
void setup()
//****************************************************************************************
{ 
  Serial.begin(115200);           // Intialize terminal debugUART port  
  btUART.begin("ShuttleCounter"); // Bluetooth device name  

  splash();                       // Copyright screen
  adjustPower(ESP_PWR_LVL_P6);    // See below

  debugUART.println("Transmitting COUNT...");
    
  /* From: https://docs.espressif.com/projects/esp-idf/en/v4.1/api-reference/bluetooth/controller_vhci.html#_CPPv417esp_power_level_t
   enum esp_power_level_t
      Bluetooth TX power level(index), it’s just a index corresponding to power(dbm).
      
      Values:
      
      ESP_PWR_LVL_N12 = 0
      Corresponding to -12dbm
      
      ESP_PWR_LVL_N9 = 1
      Corresponding to -9dbm
      
      ESP_PWR_LVL_N6 = 2
      Corresponding to -6dbm
      
      ESP_PWR_LVL_N3 = 3
      Corresponding to -3dbm
      
      ESP_PWR_LVL_N0 = 4
      Corresponding to 0dbm
      
      ESP_PWR_LVL_P3 = 5
      Corresponding to +3dbm
      
      ESP_PWR_LVL_P6 = 6
      Corresponding to +6dbm
      
      ESP_PWR_LVL_P9 = 7
      Corresponding to +9dbm
  */  
}

 
//****************************************************************************************
void loop()
//****************************************************************************************
{
  delay(500);
  btUART.println(counter);
  counter++;
}


//****************************************************************************************
void splash()
//****************************************************************************************
{
  debugUART.println("*****************************************************");
  debugUART.println("Bluetooth Test Application /w Power Control");
  debugUART.println("Version 1.0");
  debugUART.println("Copyright 2022, Digame Systems. All rights reserved.");
  debugUART.println("*****************************************************");
}


//****************************************************************************************
// Bluetooth Power Control
//****************************************************************************************

void readPowers()
{
  esp_power_level_t min,max;
  debugUART.println("Reading...");
  esp_bredr_tx_power_get(&min,&max);
  debugUART.println("Power levels set to: ");
  debugUART.printf("min %d max %d\n\n",min,max);
}


void setPowers(esp_power_level_t power)
{
  esp_power_level_t min,max;
  min = power;
  max = power;
  
  debugUART.println("Adjusting power...\n");
  
  // Min - Max power for connetions. (I think)
  esp_bredr_tx_power_set(min,max); 
  
  //Power for Adversiting Messages
  esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_ADV, max);
}


void adjustPower(esp_power_level_t power)
{
  readPowers();
  setPowers(power);
  readPowers(); 
}
