#ifndef INPUT_H
#define INPUT_H

class Input{
public:
	virtual bool boost() = 0;
	virtual bool turtle() = 0;
	virtual double leftTankAxis() = 0;
	virtual double rightTankAxis() = 0;	
};
#endif