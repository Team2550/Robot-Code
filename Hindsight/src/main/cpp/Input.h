#ifndef INPUT_H
#define INPUT_H

class Input{
public:
	virtual bool shoot() = 0;
	virtual bool climb() = 0;
	virtual bool autoAim() = 0;
};
#endif