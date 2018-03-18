# Lora

## LMIC_improved_example
Easier to use code for LMIC library for the RFM95 module.

## LoRa_Feinstaub_SDS011
A LoRa based particulate matter sensor.  
Sends the measured data over TTN to luftdaten.info
### Hardware
- Arduino Micro
- RFM95 LoRa module
- SDS011 particulate matter sensor
- BMP280 temperature and pressure sensor
### Notes
- Uses the TTN to Luftdaten forwarder script from [Cinezaster](https://github.com/Cinezaster/ttn2luftdaten_forwarder)
  - This forwarder creates the Luftdaten device ID with the pattern [prefix]-[deviceEUI-in-decimal]
  - Using the following `docker-compose.yaml` file:
  ```yaml
    version: '3'
    services:
        ttn2luftdaten_forwarder:
            environment:
                - appID=xxx
                - accessKey=xxx
                - prefix=xxx
            image: 'cinezaster/ttn2luftdaten_forwarder:latest'
  ```
   - appID, accessKey are copied from the TTN application, prefix is your own choice (we used `cfh`)
 - Connect BMP280 to Arduino Micro Pins 2 (SDA) and 3 (SCL)
   - maybe need to change address in bmp.begin() to `0x77` depending on your wiring
 - Connect SDS011 to Arduino Micro hardware serial pins (TX and RX pins on pin header)