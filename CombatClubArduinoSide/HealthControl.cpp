#include "Arduino.h"
#include "HealthControl.h"
#include "WeaponControl.h"
#include "BluetoothConnection.h"

void HealthControl::hit(char severity)
{
	if (hp > 0) 
	{
		hp = (hp - severityVal[severity] < 0) ? 0 : hp - severityVal[severity];
		bc.sendHP(hp);
		//debugPrint();
		if (hp <= 0) wc.setEnabled(false);
	}
}

void HealthControl::revive(char reviveHp)
{
	hp = reviveHp;
	bc.sendHP(hp);
	wc.setEnabled(true);
}

const void HealthControl::debugPrint() const
{
	// DEBUG: print state
	Serial.print("hp state: ");
	Serial.print(hp, 10); //print decimal value of hp
	Serial.println("%");
	// END DEBUG
}

void HealthControl::waitForRevive()
{
	Serial.println("Waiting for revive");
	// Wait For Revive From Mobile
	while (true)
	{
		if (Serial.available()>0)
		{
			Serial.println("Serial avialable");
			char commandChar = Serial.read();
			Serial.println("Serial Char = "+commandChar);
			if (commandChar == '*') {
				Serial.println("command char ok");
				revive(100);
				Serial.println("after revive");
				break;
			}
		}
	}
}


HealthControl hc = HealthControl();
