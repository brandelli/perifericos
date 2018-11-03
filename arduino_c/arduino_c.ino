int inByte = 0;
int lastInByte = 0;
int fromSerial = 0;
int pat2, pat3, pat4, pat5, pat6, pat7,pat8;
void setup() {
 /* Inicializa a porta serial em 9600 bytes/s */
 Serial.begin(9600);
 /* Configura o pino de IO para piscar o led durante a recepção. */
 pinMode(13, OUTPUT);
 pinMode(12, OUTPUT);
 pinMode(11, OUTPUT);
 pinMode(10, OUTPUT);
 pat2 = 0;
 pat3 = 0;
 pat4 = 0;
 pat5 = 0;
 pat6 = 0;
 pat7 = 0;
 pat8 = 0;
}

void configArduino(){
  digitalWrite(13, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(10, HIGH);
  delay(500);
  digitalWrite(13, LOW);
  digitalWrite(12, LOW);
  digitalWrite(11, LOW);
  digitalWrite(10, LOW);
  delay(500);
  if(fromSerial == 1){
    fromSerial = 0;
  }
}

void pattern2(){
  digitalWrite(13, LOW);
  digitalWrite(12, LOW);
  digitalWrite(11, HIGH);
  digitalWrite(10, LOW);
  delay(500);
  digitalWrite(13, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(11, LOW);
  digitalWrite(10, HIGH);
  delay(500);
  if(fromSerial == 1){
    pat2++;
    fromSerial = 0;
  }
}

void pattern3(){
  digitalWrite(13, LOW);
  digitalWrite(12, LOW);
  digitalWrite(11, HIGH);
  digitalWrite(10, HIGH);
  delay(500);
  digitalWrite(13, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(11, LOW);
  digitalWrite(10, LOW);
  delay(500);
  if(fromSerial == 1){
    pat3++;
    fromSerial = 0;
  }
}

void pattern4(){
  digitalWrite(13, LOW);
  digitalWrite(12, HIGH);
  digitalWrite(11, LOW);
  digitalWrite(10, LOW);
  delay(500);
  digitalWrite(13, HIGH);
  digitalWrite(12, LOW);
  digitalWrite(11, HIGH);
  digitalWrite(10, HIGH);
  delay(500);
  if(fromSerial == 1){
    pat4++;
    fromSerial = 0;
  }
}

void pattern5(){
  digitalWrite(13, LOW);
  digitalWrite(12, HIGH);
  digitalWrite(11, LOW);
  digitalWrite(10, HIGH);
  delay(500);
  digitalWrite(13, HIGH);
  digitalWrite(12, LOW);
  digitalWrite(11, HIGH);
  digitalWrite(10, LOW);
  delay(500);
  if(fromSerial == 1){
    pat5++;
    fromSerial = 0;
  }
}

void pattern6(){
  digitalWrite(13, LOW);
  digitalWrite(12, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(10, LOW);
  delay(500);
  digitalWrite(13, HIGH);
  digitalWrite(12, LOW);
  digitalWrite(11, LOW);
  digitalWrite(10, HIGH);
  delay(500);
  if(fromSerial == 1){
    pat6++;
    fromSerial = 0;
  }
}

void pattern7(){
  digitalWrite(13, LOW);
  digitalWrite(12, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(10, HIGH);
  delay(500);
  digitalWrite(13, HIGH);
  digitalWrite(12, LOW);
  digitalWrite(11, LOW);
  digitalWrite(10, LOW);
  delay(500);
  if(fromSerial == 1){
    pat7++;
    fromSerial = 0;
  }
}

void pattern8(){
  digitalWrite(13, HIGH);
  digitalWrite(12, LOW);
  digitalWrite(11, LOW);
  digitalWrite(10, LOW);
  delay(500);
  digitalWrite(13, LOW);
  digitalWrite(12, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(10, HIGH);
  delay(500);
  if(fromSerial == 1){
    pat8++;
    fromSerial = 0;
  }
}

void pattern1(){
   Serial.write(pat2);
   delay(10);
   Serial.write(pat3);
   delay(10);
   Serial.write(pat4);
   delay(10);
   Serial.write(pat5);
   delay(10);
   Serial.write(pat6);
   delay(10);
   Serial.write(pat7);
   delay(10);
   Serial.write(pat8);
   delay(10);
   inByte = lastInByte;
   if(fromSerial == 1){
    fromSerial = 0;
  }   
}

void loop() {
 /* Aguarda o recebimento de dados */
 if (Serial.available() > 0) {
   lastInByte = inByte;
   inByte = Serial.read();
   fromSerial = 1;
 }
 switch (inByte) {
      case 0:
        configArduino();
        break;
      case 1:
        pattern1();
        break;
      case 2:
        pattern2();
        break;
      case 3:
        pattern3();
        break;
      case 4:
        pattern4();
        break;
      case 5:
        pattern5();
        break;
      case 6:
        pattern6();
        break;
      case 7:
        pattern7();
        break;
      case 8:
        pattern8();
        break;
      default:
        break;   
  }
}

