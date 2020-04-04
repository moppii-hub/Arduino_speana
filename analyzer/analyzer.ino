#define LOG_OUT 0
#define LIN_OUT 1
#define FFT_N 256

#include <FFT.h>
#include <MatrizLed.h>
MatrizLed pantalla;

#define VALUE_TO_BIT(BIT) ((1<<BIT)-1)  // convert value such as 4 -> 0b00001111

#define REC_UPPER_LIM 1500
#define REC_LOWER_LIM 150

bool debug_mode = false;

//filter to adjust height. DEFAULT : {1, 1, 1, 1, 1, 1, 1, 1}
//float filter[8] = {1.1, 1.15, 1.25, 1.45, 1.55, 1.75, 2, 3};    //boost at middle and high freq
float filter[8] = {3, 2.5, 1.5, 0.5, 0.6, 1, 2, 3};       //boost at low and high freq

//borders of the frequency axis. DEFAULT : {16,32,48,64,80,96,112,128}
//uint8_t border[8] = {2,3,7,11,16,24,32,69};  //large area
//uint8_t border[8] = {1,2,3,4,8,12,24,32};    //low-freq area
uint8_t border[8] = {1,2,3,4,7,12,16,24};      //narrow area


byte swapbit(byte in_data, int bitsize){
  byte buf = 0;
  while(bitsize--){
    buf = buf << 1;
    buf = buf | (in_data & 1);
    in_data = in_data >> 1;
  }
  return buf;
}

void setup(){
  Serial.begin(115200);

  TIMSK0 = 0;   //turn off timer0 for lower jitter
  ADCSRA = 0xe5;//set the adc to free running mode
  ADMUX = 0x40; // use adc0
  DIDR0 = 0x01; // turn off the digital input for adc0
  analogReference(DEFAULT);                                        //set aref to external

  pantalla.begin(12, 11, 10, 2); // dataPin, clkPin, csPin
  pantalla.setIntensity(0, 0);

}

void loop() {
  while(1) {                       //reduces jitter
    cli();                         //UDRE interrupt slows this way down on arduino1.0
    for (int i=0;i<FFT_N*2;i+=2) { //save 256 samples
      while(!(ADCSRA & 0x10));     //wait for adc to be ready
      ADCSRA = 0xf5;               //restart adc
      byte m = ADCL;               //fetch adc data
      byte j = ADCH;
      int k = (j << 8) | m;        //form into an int
      k -= 0x0200;                 //form into a signed int
      k <<= 6;                     //form into a 16b signed int
      fft_input[i] = k;            //put real data into even bins
      fft_input[i+1] = 0;          //put real data into odd bins
    }

    fft_window();                  // window the data for better frequency response
    fft_reorder();                 // reorder the data before doing the fft
    fft_run();                     // process the data in the fft
    fft_mag_lin();                 // take the output of the fft
    sei();

    for(int i=0;i<8;i++){
      uint16_t maxSignal = 0;
      for(int j=border[i];j<border[i+1];j++){
        if(fft_lin_out[j] > maxSignal){
          maxSignal = fft_lin_out[j];
        }
      }

      if(debug_mode){
        Serial.print(maxSignal);
        Serial.print("->");
      }

      //filtering
      if(maxSignal < REC_LOWER_LIM){
        maxSignal = 0;
      }else if(maxSignal > REC_UPPER_LIM){
        maxSignal = 65535;
      }else {
        maxSignal = map(maxSignal, REC_LOWER_LIM, REC_UPPER_LIM, 0, 65535);
        maxSignal = (uint16_t)(maxSignal * filter[i]);
        if(maxSignal > 65535) maxSignal = 65535;
      }

      //calc height
      uint8_t height = (uint8_t)map(maxSignal, 0, 65535, 0, 8);

      if(debug_mode){
        Serial.print(maxSignal);
        Serial.print("->");
        Serial.print(height);
        Serial.print(" | ");
      }

      //LED output
      byte led_value = VALUE_TO_BIT(height);
      pantalla.setRow(0, i, swapbit(led_value, 8));
    }
    Serial.println("");
  }
}
