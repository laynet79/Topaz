#pragma once
class VirtualMachine;

//-------------------------------------------------------
// this class implements the Math class library
//-------------------------------------------------------
class Math
{
public:
	Math() {}
	~Math() {}

	void initialize(VirtualMachine& vm);

private:
	void handleInt(void*);
	void handleFrac(void*);
	void handleSqrt(void*);
	void handlePow(void*);
	void handlePi(void*);
	void handleSin(void*);
	void handleCos(void*);
	void handleTan(void*);
	void handleAsin(void*);
	void handleAcos(void*);
	void handleAtan(void*);
	void handleAtan2(void*);
};

