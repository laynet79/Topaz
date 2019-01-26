#pragma once
#include <vector>
using namespace std;
#include <cstdarg>

class Class;
class Constant;
#include "CallBack.h"
#include "Stack.h"
#include "SymbolTable.h"

class VirtualMachine
{
public:
	VirtualMachine();
	~VirtualMachine();

	Value*& constant(int index);
	Stack& stack() { return mStack; }

	void run();

	void compile(const string& input);

	Value* call(Value* object, const string& cls, const string& name, int argCnt, ...);
	Value* call(Value* object, const string& cls, const string& name, int argCnt, va_list args);

	Class* addClass(const string& name, int varCnt, ...);
	Class* addClass(const string& name, int varCnt, va_list args);

	void addMethod(Class* cls, const string& name, CallBack* handler, int paramCnt, ...);
	void addMethod(Class* cls, const string& name, CallBack* handler, int paramCnt, va_list args);

	//------------------------------------------
	// get the type of a value
	ValueType type(Value* v);

	//------------------------------------------
	// convert to printable string
	string toStr(Value* v);

	//------------------------------------------
	// these methods construct a value out of the given data
	Value* value(bool b);
	Value* value(double n);
	Value* value(const string& s);
	Value* valueTuple(const vector<Value*>& t);
	Value* valueList(const vector<Value*>& l);

	//------------------------------------------
	// these methods retrieve the data out of a value object
	// (throws a char* exception)
	bool   boolean(Value* v);
	double number(Value* v);
	string str(Value* v);
	vector<Value*>& tuple(Value* v);
	vector<Value*>& list(Value* v);

	//------------------------------------------
	// This function is called to release a value.
	void release(Value* v);


private:
	SymbolTable mSymbols;
	vector<Constant*> mConstants;
	Stack mStack;
};
