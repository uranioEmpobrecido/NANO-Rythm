// RYTHM, the simple drum box
//
// All in the spirit of open-source and open-hardware
// by Jorge Gutiérrez
//
// NANO
//
// 2017 Spain
//
// GPIO 

void GPIOSetup(void){
  
  pinMode(startButton,INPUT_PULLUP);
  pinMode(resetButton,INPUT_PULLUP);
  pinMode(sound1,INPUT_PULLUP);
  pinMode(sound2,INPUT_PULLUP);
  pinMode(sound3,INPUT_PULLUP);
  pinMode(sound4,INPUT_PULLUP);

  pinMode(tempoLed,OUTPUT);
  pinMode(recordLed,OUTPUT);
  
  pinMode(speakerPin,OUTPUT);
}
