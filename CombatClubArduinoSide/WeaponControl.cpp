#include "Arduino.h"
#include "WeaponControl.h"
#include "BluetoothConnection.h"

void WeaponControl::setup(char triggerPin /*= 30*/, char reloadPin /*= 3*/,int reloadDelay /*=2000*/, char firePin /*= 13*/, char magCap /*= 30*/, char magSize /*= 30*/, char fireDelay /*= 100*/, bool isEnabled /*=true*/)
{
	this->triggerPin = triggerPin;
	this->reloadPin = reloadPin;
	this->reloadDelay = reloadDelay;
	this->firePin = firePin;
	this->magCap = magCap;
	this->magSize = magSize;
	this->fireDelay = fireDelay;
	this->isEnabled = isEnabled;
}

void WeaponControl::shoot()
{
	if (!isEnabled) return;
	// if there are bullets in the magazine
	if (magSize > 0) 
	{
		// set lazer to high
		digitalWrite(firePin, HIGH);
		// make the lazer be on high for fireDelay time
		delay(fireDelay);
		// one bullet down
		magSize--;
		// send ammo with bluetooth
		bc.sendAmmo(magSize);
		// set lazer to low
		digitalWrite(firePin, LOW);
		//  make the lazer be on low for fireDelay time
		delay(fireDelay);

		// debug print status
		//debugPrint();

	}
	
}

void WeaponControl::reload()
{
	if (!isEnabled) return;
	bc.sendReloadDelay(reloadDelay);
	delay(reloadDelay);
	magSize = magCap;
	bc.sendAmmo(magSize);
	//debugPrint();
}

void WeaponControl::setEnabled(bool isEnabled)
{
	this->isEnabled = isEnabled;
}

const void WeaponControl::debugPrint() const
{
	// DEBUG: print state
	Serial.print("mag state: ");
	Serial.print(magSize, 10); //print decimal value of magSize
	Serial.print(" / ");
	Serial.println(magCap, 10); //print decimal value of magCap
	// END DEBUG
}



WeaponControl wc = WeaponControl();