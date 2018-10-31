enum plaquinhaStates {
  CONFIG,
  PARADO, // blink disable
  RECEBEU, // blink enable
};
/*
- Arduino Serial Echo Server -
Cada byte recebido e reenvidado pela serial. Ainda durante a recepço
de um byte o LED ligado ao pino 13 pisca.
*/
enum plaquinhaStates pState;
void setup() {
 /* Inicializa a porta serial em 9600 bytes/s */
 Serial.begin(9600);
 /* Configura o pino de IO para piscar o led durante a recepção. */
 pinMode(13, OUTPUT);
 pinMode(12, OUTPUT);
 pinMode(11, OUTPUT);
 pinMode(10, OUTPUT);
 pState = CONFIG;
}
void loop() {
 char inByte;

 /* Aguarda o recebimento de dados */
 if (Serial.available()) {
   /* liga o LED */
   /* Le byte da serial */
   inByte = Serial.read();
   /* Responde o byte pela serial */
   Serial.write(inByte);
   /* Desliga o LED */
   
 }
 switch (pState) {
      case CONFIG:
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
        break;
      default:
        delay(500);
        break;   
  }
}
