// RYTHM, the simple drum box
//
// All in the spirit of open-source and open-hardware
// by Jorge Gutiérrez
//
// NANO
//
// 2017 Spain
//
// ISR 

// This is called at 8000 Hz to load the next sample.
ISR(TIMER1_COMPA_vect) {
  
  if (sample >= sounddata_length) {
    if (sample == sounddata_length + lastSample) {
      stopPlayback();
    }
    else {
      // Ramp down to zero to reduce the click at the end of playback.
      OCR2B = sounddata_length + lastSample - sample;
    }
  }
  else {
    OCR2B = pgm_read_byte(&sounddata_data[sample]);
  }
  ++sample; 
}
