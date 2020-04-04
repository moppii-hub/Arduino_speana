# About
This is a spectrum analyzer using Arduino and 8x8 matrix LED.  


# BOM
(must)
- Arduino Pro mini
- MAX7219 matrix LED module
- MAX4466 mic module
- Some wires

(any)
- 3V coin battery(CR2032) holder (need 2pcs)
- Push switch (can hold)
- Universal PWB (50x70mm)
- Case by 3D printed


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


# Reference
[Arduino FFT Spectrum Analyzer with pedalSHIELDMEGA](https://www.electrosmash.com/forum/pedalshield-mega/381-arduino-fft-spectrum-analyzer-with-pedalshieldmega)
[Arduino Realtime Audio Spectrum Analyzer with Video out!
](http://blurtime.blogspot.com/2010/11/arduino-realtime-audio-spectrum.html)
[968円で作る。LEDイコライザっぽい表示機](https://qiita.com/hashito/items/d1c94910e11d044e53bb)


