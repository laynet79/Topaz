#include <string>
#include <fstream>
using namespace std;
#include <cstdarg>

#include "Topaz.h"
#include "VirtualMachine.h"

//-------------------------------------------------------
Topaz::Topaz()
{
	vm = new VirtualMachine();
}
//-------------------------------------------------------
Topaz::~Topaz()
{
	delete vm;
}

void Topaz::runTest() { vm->runTest(); }

//-------------------------------------------------------
void Topaz::compile(const string & input)
{
	vm->compile(input);
}
//-------------------------------------------------------
Value* Topaz::call(Value* object, const string& cls, const string& name, int argCnt, ...)
{
	va_list args;
	va_start(args, argCnt);
	Value* result = vm->call(object, cls, name, argCnt, args);
	va_end(args);
	return result;
}
//-------------------------------------------------------
Class* Topaz::addClass(const string& name, int varCnt, ...)
{
	va_list args;
	va_start(args, varCnt);
	Class* cls = vm->addClass(name, varCnt, args);
	va_end(args);
	return cls;
}
//-------------------------------------------------------
void Topaz::addMethod(Class* cls, const string& name, CallBack* handler, int paramCnt, ...)
{
	va_list args;
	va_start(args, paramCnt);
	vm->addMethod(cls, name, handler, paramCnt, args);
	va_end(args);
}
//-------------------------------------------------------
ValueType Topaz::type(Value* v) { return vm->type(v); }

//-------------------------------------------------------
Value* Topaz::value(bool b) { return vm->value(b); }
Value* Topaz::value(double n) { return vm->value(n); }
Value* Topaz::value(const string& s) { return vm->value(s); }
Value* Topaz::valueTuple(const vector<Value*>& t) { return vm->valueTuple(t); }
Value* Topaz::valueList(const vector<Value*>& l) { return vm->valueList(l); }

//-------------------------------------------------------
bool   Topaz::boolean(Value* v) { return v->boolean(); }
double Topaz::number(Value* v) { return v->number(); }
string Topaz::str(Value* v, bool quoted)
{
	if (v == nullptr)
		return "null";
	if (quoted && v->type() == STRING)
		return "\"" + v->str() + "\"";
	else
		return v->str();
}
vector<Value*>& Topaz::tuple(Value* v) { return v->tuple(); }
vector<Value*>& Topaz::list(Value* v) { return v->list(); }

//-------------------------------------------------------
void Topaz::release(Value* v) { if (v) v->deref(); }

//-------------------------------------------------------
void Topaz::verifyParamCnt(int n) { vm->verifyParamCnt(n); }
bool Topaz::boolParam(int i) { return vm->boolParam(i); }
double Topaz::numberParam(int i) { return vm->numberParam(i); }
string& Topaz::stringParam(int i) { return vm->stringParam(i); }
vector<Value*>& Topaz::tupleParam(int i) { return vm->tupleParam(i); }
vector<Value*>& Topaz::listParam(int i) { return vm->listParam(i); }

//-------------------------------------------------------
void Topaz::Return(Value* v) { vm->Return(v); }
void Topaz::Return(bool v) { vm->Return(v); }
void Topaz::Return(double v) { vm->Return(v); }
void Topaz::Return(const string& v) { vm->Return(v); }
void Topaz::ReturnTuple(vector<Value*>& v) { vm->ReturnTuple(v); }
void Topaz::ReturnList(vector<Value*>& v) { vm->ReturnList(v); }
//-------------------------------------------------------
