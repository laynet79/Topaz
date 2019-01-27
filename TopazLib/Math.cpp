#include "Math.h"
#include "VirtualMachine.h"

//-------------------------------------------------------
void Math::initialize(VirtualMachine& vm)
{
	Class* c = vm.addClass("Math", 0);
	vm.addMethod(c, "int", new MethodCallBack<Math>(this, &Math::handleInt), 1, "n");
	vm.addMethod(c, "frac", new MethodCallBack<Math>(this, &Math::handleFrac), 1, "n");
	vm.addMethod(c, "sqrt", new MethodCallBack<Math>(this, &Math::handleSqrt), 1, "n");
	vm.addMethod(c, "pow", new MethodCallBack<Math>(this, &Math::handlePow), 2, "x", "n");
	vm.addMethod(c, "pi", new MethodCallBack<Math>(this, &Math::handlePi), 0);
	vm.addMethod(c, "sin", new MethodCallBack<Math>(this, &Math::handleSin), 1, "n");
	vm.addMethod(c, "cos", new MethodCallBack<Math>(this, &Math::handleCos), 1, "n");
	vm.addMethod(c, "tan", new MethodCallBack<Math>(this, &Math::handleTan), 1, "n");
	vm.addMethod(c, "asin", new MethodCallBack<Math>(this, &Math::handleAsin), 1, "n");
	vm.addMethod(c, "acos", new MethodCallBack<Math>(this, &Math::handleAcos), 1, "n");
	vm.addMethod(c, "atan", new MethodCallBack<Math>(this, &Math::handleAtan), 1, "n");
	vm.addMethod(c, "atan2", new MethodCallBack<Math>(this, &Math::handleAtan), 2, "y", "x");
}
//-------------------------------------------------------
void Math::handleInt(void* ctx)
{
	VirtualMachine& vm = *(VirtualMachine*)ctx;
	vm.verifyParamCnt(1);
	double a = vm.numberParam(0);
	vm.Return(floor(a));
}
//-------------------------------------------------------
void Math::handleFrac(void* ctx)
{
	VirtualMachine& vm = *(VirtualMachine*)ctx;
	vm.verifyParamCnt(1);
	double a = vm.numberParam(0);
	vm.Return(a - floor(a));
}
//-------------------------------------------------------
void Math::handleSqrt(void* ctx)
{
	VirtualMachine& vm = *(VirtualMachine*)ctx;
	vm.verifyParamCnt(1);
	double a = vm.numberParam(0);
	vm.Return(sqrt(a));
}
//-------------------------------------------------------
void Math::handlePow(void* ctx)
{
	VirtualMachine& vm = *(VirtualMachine*)ctx;
	vm.verifyParamCnt(2);
	double a = vm.numberParam(0);
	double b = vm.numberParam(0);
	vm.Return(pow(a, b));
}
//-------------------------------------------------------
void Math::handlePi(void * ctx)
{
	VirtualMachine& vm = *(VirtualMachine*)ctx;
	vm.verifyParamCnt(0);
	vm.Return(3.141592654);
}
//-------------------------------------------------------
void Math::handleSin(void* ctx)
{
	VirtualMachine& vm = *(VirtualMachine*)ctx;
	vm.verifyParamCnt(1);
	double a = vm.numberParam(0);
	vm.Return(sin(a));
}
//-------------------------------------------------------
void Math::handleCos(void* ctx)
{
	VirtualMachine& vm = *(VirtualMachine*)ctx;
	vm.verifyParamCnt(1);
	double a = vm.numberParam(0);
	vm.Return(cos(a));
}
//-------------------------------------------------------
void Math::handleTan(void* ctx)
{
	VirtualMachine& vm = *(VirtualMachine*)ctx;
	vm.verifyParamCnt(1);
	double a = vm.numberParam(0);
	vm.Return(tan(a));
}
//-------------------------------------------------------
void Math::handleAsin(void* ctx)
{
	VirtualMachine& vm = *(VirtualMachine*)ctx;
	vm.verifyParamCnt(1);
	double a = vm.numberParam(0);
	vm.Return(asin(a));
}
//-------------------------------------------------------
void Math::handleAcos(void* ctx)
{
	VirtualMachine& vm = *(VirtualMachine*)ctx;
	vm.verifyParamCnt(1);
	double a = vm.numberParam(0);
	vm.Return(acos(a));
}
//-------------------------------------------------------
void Math::handleAtan(void* ctx)
{
	VirtualMachine& vm = *(VirtualMachine*)ctx;
	vm.verifyParamCnt(1);
	double a = vm.numberParam(0);
	vm.Return(atan(a));
}
//-------------------------------------------------------
void Math::handleAtan2(void* ctx)
{
	VirtualMachine& vm = *(VirtualMachine*)ctx;
	vm.verifyParamCnt(2);
	double a = vm.numberParam(0);
	double b = vm.numberParam(0);
	vm.Return(atan2(a, b));
}
//-------------------------------------------------------
