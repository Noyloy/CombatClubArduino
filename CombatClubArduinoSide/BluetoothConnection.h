#ifndef __BLUETOOTHCONNECTION_H
#define __BLUETOOTHCONNECTION_H

class BluetoothConnection
{
private:
	int serialBPS = 9600;
	char rxPin = 0;
	char txPin = 1;
	char ammoChar = 'a';
	char healthChar = 'h';
	char reloadChar = 'r';

public:
	void setup(int serialBPS = 9600, char rxPin = 0, char txPin = 1, char ammoChar = 'a', char healthChar = 'h', char reloadChar = 'r');
	void connect();
	void sendAmmo(char shotsFired);
	void sendHP(char healthRemain);
	void sendReloadDelay(int reloadDelay);
};

extern BluetoothConnection bc;

#endif //__BLUETOOTHCONNECTION_H