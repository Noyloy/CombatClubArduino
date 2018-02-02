#ifndef __HEALTHCONTROL_H
#define __HEALTHCONTROL_H

class HealthControl
{
private:
	char severityVal[3] = { 14,25,36 };

public:
	volatile char hp = 100;
	void hit(char severity);
	void revive(char reviveHp);
	void waitForRevive();
private:
	const void debugPrint() const;
	
};

extern HealthControl hc;

#endif //__HEALTHCONTROL_H