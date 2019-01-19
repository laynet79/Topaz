#pragma once
#include <string>
#include <vector>
using namespace std;
class TopazImp;

//-------------------------------------------------------
// This class serves as the interface into the Topaz
// library.  It utilizes the TopazImp implementation
// class which hides the implementation of Topaz from
// the user.
//-------------------------------------------------------
class __declspec(dllexport) Topaz
{
public:
	Topaz();
	~Topaz();
	void run();
	bool compile(const string& input);

private:
	TopazImp* mImp;
};

