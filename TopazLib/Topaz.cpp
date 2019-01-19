#include <string>
#include <fstream>
using namespace std;

#include "Topaz.h"
#include "TopazImp.h"

//-------------------------------------------------------
Topaz::Topaz()
{
	mImp = new TopazImp();
}
//-------------------------------------------------------
Topaz::~Topaz()
{
	delete mImp;
}
//-------------------------------------------------------
void Topaz::run()
{
	mImp->run();
}
//-------------------------------------------------------
bool Topaz::compile(const string & input)
{
	return mImp->compile(input);
}
//-------------------------------------------------------
