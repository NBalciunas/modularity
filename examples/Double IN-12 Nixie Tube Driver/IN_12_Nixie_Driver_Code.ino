// IN-12 Nixie Driver Example Code

#define DIN_PIN 7
#define CLK_PIN 6
#define EN_PIN  5

void SetNixieMultiple(byte digit1 = 10, byte digit2 = 10, byte digit3 = 10, byte digit4 = 10, byte digit5 = 10, byte digit6 = 10,
                      bool dot1 = false, bool dot2 = false, bool dot3 = false, bool dot4 = false, bool dot5 = false, bool dot6 = false);

int i = 0;

void setup() {  
  pinMode(DIN_PIN, OUTPUT); 
  digitalWrite(DIN_PIN, LOW);    
    
  pinMode(CLK_PIN, OUTPUT);
  digitalWrite(CLK_PIN, LOW);         
  
  pinMode(EN_PIN, OUTPUT);
  digitalWrite(EN_PIN, LOW);
}

void loop(){
  //SetNixieMultiple(1, 2, 3, 4, 5, 6);
  SetNixieMultiple((i+0)%10, (i+1)%10, (i+2)%10, (i+3)%10, (i+4)%10, (i+5)%10);
  delay(1000);

  //SetNixieMultiple(1, 2, 3, 4, 5, 6, true, true, true, true, true, true);
  SetNixieMultiple((i+0)%10, (i+1)%10, (i+2)%10, (i+3)%10, (i+4)%10, (i+5)%10, true, true, true, true, true, true);
  delay(1000);

  i = i + 1;
}

void StartShiftOutData(){
  digitalWrite(EN_PIN, 0); 
  digitalWrite(DIN_PIN, 0);
  digitalWrite(CLK_PIN, 0);  
}

void ShiftOutData(byte digit, bool hasDot = false) {
  const byte digitMap[10] = {9, 0, 1, 2, 3, 4, 5, 6, 7, 8};

  if (digit < 10) {
    digit = digitMap[digit];
  }

  for (int i = 10; i >= 0; i--) {
    if (i == digit || (hasDot && i == 10)) {
      digitalWrite(DIN_PIN, 1);
    } else {
      digitalWrite(DIN_PIN, 0);
    }

    digitalWrite(CLK_PIN, 1);
    digitalWrite(CLK_PIN, 0);
  }
}

void SkipBlankData(){
  for (int i = 1; i >= 0; i--){
    digitalWrite(CLK_PIN, 1);
    digitalWrite(CLK_PIN, 0);  
  }   
}

void EndShiftOutData(){
  digitalWrite(EN_PIN, 1);
  digitalWrite(CLK_PIN, 0);    
}

void SetNixie(byte digit1, byte digit2, bool dot1 = false, bool dot2 = false){
  SkipBlankData();
  if (digit2 != 10) ShiftOutData(digit2, dot1);
  if (digit1 != 10) ShiftOutData(digit1, dot2);
}

void SetNixieMultiple(byte digit1, byte digit2 , byte digit3, byte digit4, byte digit5, byte digit6,
                      bool dot1 = false, bool dot2 = false, bool dot3 = false, bool dot4 = false, bool dot5 = false, bool dot6 = false){
  StartShiftOutData();
  SetNixie(digit5, digit6, dot5, dot6);
  SetNixie(digit3, digit4, dot3, dot4);
  SetNixie(digit1, digit2, dot1, dot2);
  EndShiftOutData();
}