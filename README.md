# perifericos
https://isocpp.org/wiki/faq/mixing-c-and-cpp#overview-mixing-langs

http://renangreinert.blogspot.com/2011/08/extern-c.html

# Parte do Raspberry (buttons e serial)
* serial.c e serial.h são a parte da comunicação entre rpi e arduino
* button.ccp faz a parte de manipulação de GPIO (buttons)
* Necessário utilizar o extern "C" para integrar codigo C e C++
* Para compilar seguir os seguintes passos:
* gcc -c serial.c
* g++ button.cpp
* g++ button.o serial.o
* Para executar utilizar o superuser, para nao dar problema na configuraçao dos GPIO-> sudo ./a.out 

# Parte do Arduino
* Botão1 -> GPIO25 ligado ao pino B1
* Botão2 -> GPIO24 ligado ao pino B2
* Botão3 -> GPIO23 ligado ao pino B3

* LED1 -> PB5 ligado ao pino BUF1
* LED2 -> PB4 ligado ao pino BUF2
* LED3 -> PB3 ligado ao pino BUF3
* LED4 -> PB2 ligado ao pino BUF4
