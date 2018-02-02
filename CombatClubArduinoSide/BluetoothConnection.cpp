#include "Arduino.h"
#include "BluetoothConnection.h"

/* Sets the serial port bits per second, and Sets transmitter and reciever pins*/
void BluetoothConnection::setup(int serialBPS /*= 9600*/, char rxPin /*= 0*/, char txPin /*= 1*/, char ammoChar /*= 'a'*/, char healthChar /*= 'h'*/, char reloadChar /* = 'r'*/)
{
	this->serialBPS = serialBPS;
	this->rxPin = rxPin;
	this->txPin = txPin;
	this->ammoChar = ammoChar;
	this->healthChar = healthChar;
	this->reloadChar = reloadChar;
}

/* Starts the Serial, sets pinMode of transmiter and reciever Pins */
void BluetoothConnection::connect()
{
	Serial.begin(serialBPS);
	pinMode(rxPin, INPUT);  // Setup the Arduino to receive INPUT from the bluetooth shield
	pinMode(txPin, OUTPUT); // Setup the Arduino to send data (OUTPUT) to the bluetooth shield
}

void BluetoothConnection::sendAmmo(char shotsFired)
{
	Serial.print(ammoChar);
	Serial.print(",");
	Serial.println(shotsFired, 10);
}

void BluetoothConnection::sendReloadDelay(int reloadDelay)
{
	Serial.print(reloadChar);
	Serial.print(",");
	Serial.println(reloadDelay);
}

void BluetoothConnection::sendHP(char healthRemain)
{
	Serial.print(healthChar);
	Serial.print(",");
	Serial.println(healthRemain,10);
}

BluetoothConnection bc = BluetoothConnection();