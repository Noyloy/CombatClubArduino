#include <MemoryFree.h>
#include <ByteBuffer.h>
#include <PinChangeInt.h>

#include "Arduino.h"
#include "BluetoothConnection.h"	// extern bc = BluetoothConnection();
#include "WeaponControl.h"			// extern wc = WeaponControl();
#include "HealthControl.h"			// extern hc = HealthControl();

// Arduino Pins
const int laserPin		= 13;
const int highHitPin	= 12;
const int mediumHitPin	= 11;
const int lowHitPin		= 10;
const int reloadPin		= 3;
const int triggerPin	= 2;

volatile bool isShooting = false;
volatile bool isReloading = false;

void setup()
{
	pinMode(laserPin, OUTPUT);		// init the laser emmiter as output
	pinMode(triggerPin, INPUT);		// init the trigger button as input
	pinMode(reloadPin, INPUT);		// init the reaload button as input
	pinMode(highHitPin, INPUT);		// init the fire mode button as input

	digitalWrite(triggerPin, HIGH);	// set first time high
	digitalWrite(reloadPin, HIGH);	// set first time high


	/* Bluetooth Init */
	bc.setup();
	bc.connect();

	/* Weapon Init */
	wc.setup();

	/* Set Behaivior of trigger interrupts*/
	PCintPort::attachInterrupt(triggerPin, startStopShoot, CHANGE);
	/* Set Behaivior of reload interrupts*/
	PCintPort::attachInterrupt(reloadPin, reloadWeapond, CHANGE);
	/* Set Behaivior of hit interrupts*/
	PCintPort::attachInterrupt(highHitPin, hitHigh, RISING);
	PCintPort::attachInterrupt(mediumHitPin, hitMed, RISING);
	PCintPort::attachInterrupt(lowHitPin, hitLow, RISING);

}

void loop() {
	// reload trigger pressed
	if (isReloading) { wc.reload(); isReloading = false; }
	// shoot trigger pressed
	if (isShooting) wc.shoot();
	// user died
	if (hc.hp == 0) hc.waitForRevive();
}

//////////////////////////////////////
// ISR - Interrupt Service Routines //
//////////////////////////////////////
// weapond section
void startStopShoot() { isShooting = (digitalRead(triggerPin) == LOW); }
void reloadWeapond() { isReloading = (digitalRead(reloadPin) == LOW); }
// health section
void hitHigh() { hc.hit(2); }
void hitMed() { hc.hit(1); }
void hitLow() { hc.hit(0); }