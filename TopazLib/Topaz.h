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

	void run();

	//------------------------------------------
	// Compile the Topaz source code contained in the (thows a char* exception);
	void compile(const string& input);

	//------------------------------------------
	// call a class method.  The Optional parameters are pointers
	// to values.
	// (thows a char* exception)
	Value* call(Value* object, const string& cls, const string& name, int argCnt, ...);

	//------------------------------------------
	// Add a new class to Topaz.  Optional parameters is
	// a list of member variables. Variable names that start with an underscore
	// are protected. Variables that start with a capital letter (after
	// optional underscore) are class variables, otherwise instance variables.
	Class* addClass(const string& name, int varCnt, ...);

	//------------------------------------------
	// Add a method to a new class definition.
	// Method names that start with an underscore are protected
	// Method names that start with a capital letter (after optional underscore)
	// are class methods, otherwise instance methods. Method with the same
	// name as class is a constructor.  Option parameters is a list
	// of parameter names.
	// Throws a char* exception if method of the given name already exists
	// in the given class.
	void addMethod(Class* cls, const string& name, CallBack* handler, int paramCnt, ...);

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
	VirtualMachine* vm;
};

