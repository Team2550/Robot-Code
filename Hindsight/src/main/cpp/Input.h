#ifndef INPUT_H
#define INPUT_H

class Input{
public:
	virtual bool boost();
	virtual bool turtle();
	virtual double leftTankAxis();
	virtual double rightTankAxis();	
};
#endif