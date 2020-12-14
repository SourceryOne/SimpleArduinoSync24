/*
 * Simple Sync24 / Dinsync / DIN24 input sync to half notes, quarter note, 8th, 16th, 32th note outputs.
 * 
 */

//Sync24 inputs
#define DIN_SYNC_CLOCK 2
#define DIN_SYNC_RUN 3
#define DIN_SYNC_RESET 4 //maybe leave out because of pins or not needed?

//trigger outs
#define TRIG_OUT_16 8
#define TRIG_OUT_8 9
#define TRIG_OUT_4 10
#define TRIG_OUT_2 11

#define LED 13

int runState = 0;
int lastRunState = 0;
int clockState = 0;
int lastClockState = 0;
int clockCount = 0;
int resetState = 0;

void setup() {
  // initialize the Sync24 input:
  pinMode(DIN_SYNC_CLOCK, INPUT_PULLUP);
  pinMode(DIN_SYNC_RUN, INPUT_PULLUP);
  pinMode(DIN_SYNC_RESET, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  //add other pins
}

void loop() {
  // put your main code here, to run repeatedly:
  runState = digitalRead(DIN_SYNC_RUN);
  clockState = digitalRead(DIN_SYNC_CLOCK);
  resetState = digitalRead(DIN_SYNC_RESET);
  if (resetState == HIGH) { digitalWrite(LED, HIGH); } else {digitalWrite(LED, LOW);}
  
  
  //if the runState changes, and the runState is LOW, the reset the counter. Put it after the clockState to get the first beat.
    if(runState != lastRunState) {
      if (runState == LOW) {
        clockCount = 0;
        digitalWrite(LED, HIGH);
      }
    }

  //Run below for as long as the RUN pin is high.
  if (runState ==HIGH) {
    
    //if the clockState changes, then add a pulse to the count.
    if(clockState != lastClockState) {
      if (clockState == HIGH) {
        clockCount++;
      }
    }
    
    //add if 0 to everyone, and remove 48 eller resett
    //32th note
    if (clockCount == 0 || clockCount == 3 || clockCount == 6 || clockCount == 9 || clockCount == 12 || clockCount == 15 || clockCount == 18 || clockCount == 21 || clockCount == 24 || clockCount == 27 || clockCount == 30 || clockCount == 33 || clockCount == 36 || clockCount == 39 || clockCount == 42 || clockCount == 45 || clockCount == 48) {
      //digitalWrite(TRIG_OUT_32, HIGH);
    } else { 
      //digitalWrite(TRIG_OUT_32, LOW); 
    }
    //16th notes
    if (clockCount == 0 || clockCount == 6 || clockCount == 12 || clockCount == 18 || clockCount == 24 || clockCount == 30 || clockCount == 36 || clockCount == 42 || clockCount == 48) {
      digitalWrite(TRIG_OUT_16, HIGH);
    } else { 
      digitalWrite(TRIG_OUT_16, LOW); 
    }
    //8th notes
    if (clockCount == 0 || clockCount == 12 || clockCount == 24 || clockCount == 36 || clockCount == 48) {
      digitalWrite(TRIG_OUT_8, HIGH);
    } else { 
      digitalWrite(TRIG_OUT_8, LOW); 
    }
    //Quarter note
    if (clockCount == 0 || clockCount == 24) {
      digitalWrite(TRIG_OUT_4, HIGH);
      digitalWrite(LED, HIGH);
    } else { 
      digitalWrite(TRIG_OUT_4, LOW); 
      digitalWrite(LED, LOW); 
    }
    //Half notes
    if (clockCount == 0 || clockCount == 48) { //actually just 0
      digitalWrite(TRIG_OUT_2, HIGH);
    } else { 
      digitalWrite(TRIG_OUT_2, LOW); 
    }
    if (clockCount == 48) { //24 or 48 Reset
      clockCount = 0;
    }
    
    // save the current state as the last state, for next time through the loop
    lastClockState = clockState;
    lastRunState = runState;
  }
}
