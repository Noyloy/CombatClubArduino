#ifndef __WEAPONCONTROL_H
#define __WEAPONCONTROL_H

class WeaponControl
{
private:
	char magCap = 30;
	char magSize = 30;
	char triggerPin = 2;
	char reloadPin = 3;
	int reloadDelay = 1000;
	char firePin = 13;
	char fireDelay = 100;
	bool isEnabled = true;

public:
	void setup(char triggerPin = 30, char reloadPin = 3,int reloadDelay = 2000, char firePin = 13, char magCap = 30, char magSize = 30, char fireDelay = 100, bool isEnabled=true);
	void shoot();
	void reload();
	void setEnabled(bool isEnabled);

private:
	const void debugPrint() const;
};

extern WeaponControl wc;

#endif //__WEAPONCONTROL_H