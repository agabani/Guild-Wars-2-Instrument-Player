#pragma once
class Controller
{
public:
	Controller(void);
	~Controller(void);

public:
	virtual int init() = 0;
	virtual int pressNumber(int number) = 0;
};

