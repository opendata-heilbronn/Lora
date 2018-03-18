
# LoRa_Feinstaub_SDS011
A LoRa based particulate matter sensor.  
Sends the measured data over TTN to luftdaten.info
## Hardware
- Arduino Micro
- RFM95 LoRa module
- SDS011 particulate matter sensor
- BMP280 temperature and pressure sensor
## Notes
- Uses the [TTN to Luftdaten forwarder script](https://github.com/LeoDJ/ttn2luftdaten_forwarder)
   - This forwarder creates the Luftdaten device ID with the pattern [prefix]-[deviceEUI-in-decimal]
   - appID, accessKey are copied from the TTN application, prefix is your own choice (we used `cfh`)
   - this can all be set in the `docke-compose.yaml`
 - Connect BMP280 to Arduino Micro Pins 2 (SDA) and 3 (SCL)
   - maybe need to change address in bmp.begin() to `0x77` depending on your wiring
 - Connect SDS011 to Arduino Micro hardware serial pins (TX and RX pins on pin header)