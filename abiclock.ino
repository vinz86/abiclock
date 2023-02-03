/*
 * Orologio binario
 * By vinz
 */
int latchPin = 8;
int clockPin = 12;
int dataPin = 11;

int numOfRegisters = 2;
byte* registerState;

long effectId = 0;
long prevEffect = 0;
long effectRepeat = 0;
long effectSpeed = 30;

void setup() {
  //Initialize array
  registerState = new byte[numOfRegisters];
  for (size_t i = 0; i < numOfRegisters; i++) {
    registerState[i] = 0;
  }

  //imposto i pin su output per controllare il registro a scorrimento
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop() {
  for(int i=8;i<=15;i++){
    regWrite(i, HIGH);
    delay(500);
  }
}

void regWrite(int pin, bool state){
  // Determina il registro
  int reg = pin / 8;
  // Determino il pin per il registro attuale
  int actualPin = pin - (8 * reg);

  //Inizio la sessione
  digitalWrite(latchPin, LOW);

  for (int i = 0; i < numOfRegisters; i++){
    //Salvo lo stato attuale del registro
    byte* states = &registerState[i];

    // Aggiorno lo stato
    if (i == reg){
      bitWrite(*states, actualPin, state);
    }

    // Scrittura
    shiftOut(dataPin, clockPin, MSBFIRST, *states);
  }

  // Fine sessione 
  digitalWrite(latchPin, HIGH);
}
