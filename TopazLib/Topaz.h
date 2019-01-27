#pragma once
#include <string>
#include <vector>
using namespace std;
#include "CallBack.h"
#include "ValueType.h"
class VirtualMachine;
class Class;
class Method;
class Value;

//-------------------------------------------------------
// This class serves as the interface into the Topaz
// library.  It utilizes the internal VirtualMachine class
// which hides the implementation of Topaz from the user.
//-------------------------------------------------------
class __declspec(dllexport) Topaz
{
public:
	//------------------------------------------
	// Constructor/destructor
	Topaz();
	~Topaz();

	void runTest();

	//------------------------------------------
	// Compile a Topaz source code file
	void compile(const string& input);

	//------------------------------------------
	// call a class function
	Value* call(Value* object, const string& cls, const string& name, int argCnt, ...);
	Value* call(Value* object, const string& cls, const string& name, int argCnt, va_list args);

	//------------------------------------------
	// add a new class to the virtual machine
	Class* addClass(const string& name, int varCnt, ...);
	Class* addClass(const string& name, int varCnt, va_list args);

	//------------------------------------------
	// add a method to a new class
	void addMethod(Class* cls, const string& name, CallBack* handler, int paramCnt, ...);
	void addMethod(Class* cls, const string& name, CallBack* handler, int paramCnt, va_list args);

	//------------------------------------------
	// get the type of a value
	ValueType type(Value* v);

	//------------------------------------------
	// construct a value out of the given data
	Value* value(bool b);
	Value* value(double n);
	Value* value(const string& s);
	Value* valueTuple(const vector<Value*>& t);
	Value* valueList(const vector<Value*>& l);

	//------------------------------------------
	// retrieve the data out of a value
	// (throws exception if value type doesn't match request)
	bool   boolean(Value* v);
	double number(Value* v);
	string str(Value* v);
	vector<Value*>& tuple(Value* v);
	vector<Value*>& list(Value* v);

	//------------------------------------------
	// This function is called to release a value.
	void release(Value* v);

	//------------------------------------------
	// these methods retrieve parameters off of the
	// runtime stack.
	// (throws a char* exception)
	void verifyParamCnt(int n);
	bool boolParam(int i);
	double numberParam(int i);
	string& stringParam(int i);
	vector<Value*>& tupleParam(int i);
	vector<Value*>& listParam(int i);

	//------------------------------------------
	// These methods are used return a value from a function
	void Return(Value* v);
	void Return(bool v);
	void Return(double v);
	void Return(const string& v);
	void ReturnTuple(vector<Value*>& v);
	void ReturnList(vector<Value*>& v);

private:
	VirtualMachine* vm;
};

