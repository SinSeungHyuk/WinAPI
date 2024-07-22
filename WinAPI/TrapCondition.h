#pragma once

class CTrap;

class TrapCondition
{
public:
	virtual void ActiveTrap() = 0;
	CTrap* owner;
};

