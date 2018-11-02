#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
extern "C"{
	#include "serial.h"
} 
#include <iostream>
using namespace std;
 
#define IN  0
#define OUT 1
 
#define LOW  0
#define HIGH 1
 
static int
GPIOExport(int pin)
{
        #define BUFFER_MAX 3
	char buffer[BUFFER_MAX];
	ssize_t bytes_written;
	int fd;
 
	fd = open("/sys/class/gpio/export", O_WRONLY);
	if (-1 == fd) {
		fprintf(stderr, "Failed to open export for writing!\n");
		return(-1);
	}
 
	bytes_written = snprintf(buffer, BUFFER_MAX, "%d", pin);
	write(fd, buffer, bytes_written);
	close(fd);
	return(0);
}
 
static int
GPIOUnexport(int pin)
{
	char buffer[BUFFER_MAX];
	ssize_t bytes_written;
	int fd;
 
	fd = open("/sys/class/gpio/unexport", O_WRONLY);
	if (-1 == fd) {
		fprintf(stderr, "Failed to open unexport for writing!\n");
		return(-1);
	}
 
	bytes_written = snprintf(buffer, BUFFER_MAX, "%d", pin);
	write(fd, buffer, bytes_written);
	close(fd);
	return(0);
}
 
static int
GPIODirection(int pin, int dir)
{
	static const char s_directions_str[]  = "in\0out";
 
        #define DIRECTION_MAX 35
	char path[DIRECTION_MAX];
	int fd;
	snprintf(path, DIRECTION_MAX, "/sys/class/gpio/gpio%d/direction", pin);
	fd = open(path, O_WRONLY);
	if (-1 == fd) {
		fprintf(stderr, "Failed to open gpio direction for writing!\n");
		return(-1);
	}
 
	if (-1 == write(fd, &s_directions_str[IN == dir ? 0 : 3], IN == dir ? 2 : 3)) {
		fprintf(stderr, "Failed to set direction!\n");
		return(-1);
	}
 
	close(fd);
	return(0);
}
 
static int
GPIORead(int pin)
{
        #define VALUE_MAX 30
	char path[VALUE_MAX];
	char value_str[3];
	int fd;
 
	snprintf(path, VALUE_MAX, "/sys/class/gpio/gpio%d/value", pin);
	fd = open(path, O_RDONLY);
	if (-1 == fd) {
		fprintf(stderr, "Failed to open gpio value for reading!\n");
		return(-1);
	}
 
	if (-1 == read(fd, value_str, 3)) {
		fprintf(stderr, "Failed to read value!\n");
		return(-1);
	}
 
	close(fd);
 
	return(atoi(value_str));
}
 
static int
GPIOWrite(int pin, int value)
{
	static const char s_values_str[] = "01";
 
	char path[VALUE_MAX];
	int fd;
 
	snprintf(path, VALUE_MAX, "/sys/class/gpio/gpio%d/value", pin);
	fd = open(path, O_WRONLY);
	if (-1 == fd) {
		fprintf(stderr, "Failed to open gpio value for writing!\n");
		return(-1);
	}
 
	if (1 != write(fd, &s_values_str[LOW == value ? 0 : 1], 1)) {
		fprintf(stderr, "Failed to write value!\n");
		return(-1);
	}
 
	close(fd);
	return(0);
}

// faz o unexport indivudual da GPIO
int unexportButton(int button)
{
	if(-1 == GPIOUnexport(button))
		return 0;
	return 1;
}

// faz o export individual da GPIO
int exportButton(int button)
{
	if(-1 == GPIOExport(button))
		return 0;
	return 1;
}

// Realiza a inicialiação dos GPIOs que vao ser utilizados (23, 24, 25)
int initializeGPIOs()
{
	// fazer o unexport para ter certeza que ele não está bloqueado pela ultima execução
	if(!unexportButton(23) || !unexportButton(24) || !unexportButton(25)){
		cout << "Falha no unexport" << endl;
		return 0;	
	}

	if(!exportButton(23) || !exportButton(24) || !exportButton(25)){
		cout << "Falha no export" << endl; 	
		return 0;
	}
	return 1;
}

// configura o botão individualmente(direction e escrita)
int configButton(int button)
{
	if(-1 == GPIODirection(button, OUT))
      return 0;

    if(-1 == GPIOWrite(button, 1))
      return 0;
 
    if(-1 == GPIODirection(button, IN))
      return 0;
	
	return 1;
}


// faz a configuração dos 3 botões
int configButtons()
{
	if(!configButton(23) || !configButton(24) || !configButton(25)){
		cout << "Falha na configuracao dos buttons" << endl;
		return 0;
	}
	return 1;
}


 
int main(int argc, char *argv[])
{
	int btn1, btn2,btn3;	
	cout << "Inicio do programa" << endl;    
 
	if(!initializeGPIOs())
		return 1;

	while(1){
		if(!configButtons())
			return 2;
		
		btn1 = GPIORead(25);
		btn2 = GPIORead(24);
		btn3 = GPIORead(23);
		
		cout << "Button 1 " << btn1 << endl;
		cout << "Button 2 " << btn2 << endl;
		cout << "Button 3 " << btn3 << endl;
		usleep(500 * 1000);	
	}

  return(0);
}

