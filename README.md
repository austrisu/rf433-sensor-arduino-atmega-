# Sensor with rf433 somunication possibilities

In  this project I will create sensor whitch will transmit its state (on/off) via rf433

# RF protocol

RF comunication protocol is explained here (https://www.itead.cc/wiki/images/5/5e/RF_Universal_Transeceive_Module_Serial_Protocol_v1.0.pdf)

This is sent from Arduino using RCSwitch library		
		
mySwitch.send("000000000001010100010001");		
		
These are couple of codes recieved with SonofRF, thay sligthly changes		
		
2A7601860406001511		
2A7601860406001511		
2A7601860406001511		
2A6C01860406001511		
2A6C018603FC001511		
		
This codes are in HEX and first 13 digits are not that consotant but important part is last 6 digits and by that RF devices designete each other. The final 3 bytes are the code itself and it should be unique for every button in the same remote.		
		
00000000   00010101   00010001		These are sent data from arduino
		
  00         15          11		    And this is how it decodes in SonofRF


# References

* Turotial - (https://dronebotworkshop.com/433mhz-rf-modules-arduino/)
* (RadioHead library)[http://www.airspayce.com/mikem/arduino/RadioHead/]
* SONOF rf decoding manual - https://www.itead.cc/wiki/images/5/5e/RF_Universal_Transeceive_Module_Serial_Protocol_v1.0.pdf
* SONOF RF hack - http://tinkerman.cat/hacking-sonoff-rf-bridge-433/#lightbox-gallery-p5nMuj1w/12/
* (https://wireless.murata.com/media/products/apnotes/tr_swg05.pdf?ref=rfm.com)[ASH Transceiver Software Designer's Guide of 2002.08.07]
* (http://web.engr.oregonstate.edu/~moon/research/files/cas2_mar_07_dpll.pdf) [Future reading]
* (https://www.airspayce.com/mikem/arduino/RadioHead/classRH__ASK.html#ad8fe587d5651b972ffe1b35b701305b8)[RadioHead ASK Documantation]
* (http://forum.elektor.com/download/file.php?id=2428034&sid=e5435be69d352a5ba6e669d3b676cd25) -- Antena for 433 tutor
* (https://github.com/sui77/rc-switch/wiki/HowTo_OperateLowCostOutlets) - RC switch library explained
* (https://github.com/xoseperez/espurna/issues/271) - some explanation on whitch bites of rf code is actual data
* (http://tinkerman.cat/decoding-433mhz-rf-data-from-wireless-switches/)
* (https://www.steute.de/fileadmin/Downloads/wireless/Kataloge/Wireless_book.pdf) - evolution and explanation of WIFI
* (http://www.ti.com/lit/ml/slap127/slap127.pdf) - RF comnication phisics and diferetn types
* (http://tech.jolowe.se/home-automation-rf-protocols/) - small post about RF protocols
* (https://1technophile.blogspot.com/2017/11/sonoff-rf-bridge-with-custom-firmware.html) -  Some explanation why first bits is diferent and that only last 3 bites are value sent
* (https://github.com/1technophile/OpenMQTTGateway/wiki/Sonoff-RFB) - something how to extract necesary sent values from whole key
