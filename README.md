# About
This is a spectrum analyzer using Arduino and 8x8 matrix LED.    
![Appearance](https://github.com/moppii-hub/Arduino_speana/blob/master/photos/appearance.JPG?raw=true)  
![Backview](https://github.com/moppii-hub/Arduino_speana/blob/master/photos/backview.JPG?raw=true)  


# BOM
(must)
- Arduino Pro mini
- MAX7219 matrix LED module
- MAX4466 mic module
- Some wires

(any)
- Mini breadboard (HiLetgo SY-170 35x47x8.5mm)
- 3V coin battery(CR2032) holder (need 2pcs)
- Push switch (can hold)
- Universal PWB (50x70mm)
- Case by 3D printed

![Parts](https://github.com/moppii-hub/Arduino_speana/blob/master/photos/parts.JPG?raw=true)  


# Library which need to build
[Arduino FFT Library](http://wiki.openmusiclabs.com/)  
[MatrizLed](https://www.arduinolibraries.info/libraries/matriz-led)


# Building
- Build circuits
  - A0 - mic out
  - 10 - CS(MAX7219 module)
  - 11 - CLK(MAX7219 module)
  - 12 - DIN(MAX7219 module)
- Print case
- Assemble
- Adjust mic sensitivity and some parameters in a sketch.
- Finish!

![](https://github.com/moppii-hub/Arduino_speana/blob/master/photos/inside_bottom.JPG?raw=true)  
![](https://github.com/moppii-hub/Arduino_speana/blob/master/photos/inside_top.JPG?raw=true)  


# Reference
[Arduino FFT Spectrum Analyzer with pedalSHIELDMEGA](https://www.electrosmash.com/forum/pedalshield-mega/381-arduino-fft-spectrum-analyzer-with-pedalshieldmega)  
[Arduino Realtime Audio Spectrum Analyzer with Video out!
](http://blurtime.blogspot.com/2010/11/arduino-realtime-audio-spectrum.html)  
[968円で作る。LEDイコライザっぽい表示機](https://qiita.com/hashito/items/d1c94910e11d044e53bb)  


