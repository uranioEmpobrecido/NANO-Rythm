// RYTHM, the simple drum box
//
// All in the spirit of open-source and open-hardware
// by Jorge Gutiérrez
//
// NANO
//
// 2017 Spain
//
// BEAT 

void deleteBeat(void){
  
  setBeat = false;
  selectBeat1 = false;
  selectBeat2 = false;
  selectBeat3 = false;
  selectBeat4 = false;
  selectBeat5 = false;
  selectBeat6 = false;
  selectBeat7 = false;
  selectBeat8 = false;
}


void beatPlay(void){

  if (!digitalRead(startButton)){
    stateBeat = true;
    if (prevStateBeat != stateBeat){
      beatRun = !beatRun;
      patternBeat = 8;
    }
  } else { stateBeat = false; }

  if (!digitalRead(resetButton)){
    startPlayback(blip,blip_length);
    deleteBeat();
    delay(1000);
  }

  if (beatRun){

  if (countBeat >= ((analogRead(tempo)/2)+50)){
    digitalWrite(tempoLed, !digitalRead(tempoLed));
    patternBeat++;
    countBeat = 0;
  }

  if (patternBeat == 8){ 
    patternBeat = 0; 
    beatstep1 = false;
    beatstep2 = false;
    beatstep3 = false;
    beatstep4 = false;
    beatstep5 = false;
    beatstep6 = false;
    beatstep7 = false;
    beatstep8 = false;
    }
  
  if (patternBeat == 0){
    if (!beatstep1) { startPlayback(beat1,beatLength1); beatstep1 = true; }
    countBeat++;
  }
  else if (patternBeat == 1){
    if (!beatstep2) { startPlayback(beat2,beatLength2); beatstep2 = true; }
    countBeat++;
  }
  else if (patternBeat == 2){
    if (!beatstep3) { startPlayback(beat3,beatLength3); beatstep3 = true; }
    countBeat++;
  }
  else if (patternBeat == 3){
    if (!beatstep4) { startPlayback(beat4,beatLength4); beatstep4 = true; }
    countBeat++;
  }
  else if (patternBeat == 4){
    if (!beatstep5) { startPlayback(beat5,beatLength5); beatstep5 = true; }
    countBeat++;
  }
  else if (patternBeat == 5){
    if (!beatstep6) { startPlayback(beat6,beatLength6); beatstep6 = true; }
    countBeat++;
  }
  else if (patternBeat == 6){
    if (!beatstep7) { startPlayback(beat7,beatLength7); beatstep7 = true; }
    countBeat++;
  }
  else if (patternBeat == 7){
    if (!beatstep8) { startPlayback(beat8,beatLength8); beatstep8 = true; }
    countBeat++;
  }
  countBeat++;
  delay(1);
  }
  prevStateBeat = stateBeat;
}

uint16_t mapLength(unsigned char * sound){

  if (sound == kick)       { return kick_length     ;}
  if (sound ==cowbell)     { return cowbell_length  ;}
  if (sound == snare)      { return snare_length    ;}
  if (sound == hat)        { return hat_length      ;}
  if (sound == voidSound)  { return voidSound_length;}
}

unsigned char * mapBeat(void){

  while (!beatOK){
  if (!digitalRead(sound1)){
    startPlayback(kick,kick_length);
    beatOK = true;
    return kick;
    }
  else if (!digitalRead(sound2)){
    startPlayback(cowbell,cowbell_length);
    beatOK = true;
    return cowbell;
    }
  else if (!digitalRead(sound3)){
    startPlayback(snare,snare_length);
    beatOK = true;
    return snare;
    }
  else if (!digitalRead(sound4)){
    startPlayback(hat,hat_length);
    beatOK = true;
    return hat;
    }
  else if (!digitalRead(startButton)){
    beatOK = true;
    return voidSound;
    }
  }
}

void setBeatSequence(void){

  digitalWrite(recordLed,HIGH);

  startPlayback(blip,blip_length);
  delay(200);
  startPlayback(blip,blip_length);
  
  while (!selectBeat1){
    beat1 = mapBeat();
    beatLength1 = mapLength(beat1);
    selectBeat1 = true;}
    
  beatOK = false;
  delay(500);
  
  startPlayback(blip,blip_length);
  
  while (!selectBeat2){
    beat2 = mapBeat();
    beatLength2 = mapLength(beat2);
    selectBeat2 = true;}
    
  beatOK = false;
  delay(500);
  
  startPlayback(blip,blip_length);
  
  while (!selectBeat3){
    beat3 = mapBeat();
    beatLength3 = mapLength(beat3);
    selectBeat3 = true;}
    
  beatOK = false;
  delay(500);
  
  startPlayback(blip,blip_length);
  
  while (!selectBeat4){
    beat4 = mapBeat();
    beatLength4 = mapLength(beat4);
    selectBeat4 = true;}
    
  beatOK = false;
  delay(500);

  startPlayback(blip,blip_length);

  while (!selectBeat5){
    beat5 = mapBeat();
    beatLength5 = mapLength(beat5);
    selectBeat5 = true;}
    
  beatOK = false;
  delay(500);

  startPlayback(blip,blip_length);

  while (!selectBeat6){
    beat6 = mapBeat();
    beatLength6 = mapLength(beat6);
    selectBeat6 = true;}
    
  beatOK = false;
  delay(500);

  startPlayback(blip,blip_length);

  while (!selectBeat7){
    beat7 = mapBeat();
    beatLength7 = mapLength(beat7);
    selectBeat7 = true;}
    
  beatOK = false;
  delay(500);

  startPlayback(blip,blip_length);

  while (!selectBeat8){
    beat8 = mapBeat();
    beatLength8 = mapLength(beat8);
    selectBeat8 = true;}
    
  beatOK = false;
  delay(500);

  startPlayback(blip,blip_length);

  digitalWrite(recordLed,LOW);
}

void BeatEffect(void){

  if (!digitalRead(resetButton) || beatOn){
    if (!setBeat){
      setBeatSequence();
      setBeat = true;
      beatOn  = true;
    }
    beatPlay();
  }

  
  if (!digitalRead(sound1)){
    while (!digitalRead(sound1)){
      //Nothing
    }
    startPlayback(kick,kick_length);
  }
  if (!digitalRead(sound2)){
    while (!digitalRead(sound2)){
      //Nothing
    }
    startPlayback(cowbell,cowbell_length);
  }
    if (!digitalRead(sound3)){
    while (!digitalRead(sound3)){
      //Nothing
    }
    startPlayback(snare,snare_length);
  }
    if (!digitalRead(sound4)){
    while (!digitalRead(sound4)){
      //Nothing
    }
    startPlayback(hat,hat_length);
  }
}

