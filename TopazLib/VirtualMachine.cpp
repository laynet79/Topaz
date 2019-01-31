#include "VirtualMachine.h"
#include "Symbol.h"
#include "Class.h"
#include "Method.h"
#include "MethodHandler.h"
#include "Tokenizer.h"

#include <fstream>

//-------------------------------------------------------
VirtualMachine::VirtualMachine() : mSymbols(mConstants)
{
	mOut = &cout;
	mMath.initialize(*this);
}
//-------------------------------------------------------
VirtualMachine::~VirtualMachine()
{
}
//-------------------------------------------------------
Value*& VirtualMachine::constant(int index)
{
	Constant* c = mConstants[index]; return c->value();
}
//-------------------------------------------------------
void VirtualMachine::runTest()
{
	ifstream f("test.txt");
	string input = "";
	getline(f, input, '\0');
	Tokenizer tok(input);
	tok.begin();
	Token* t = tok.getToken();
	while (t->type() != Token::ENDOF)
	{
		cout << *t << endl;
		tok.nextToken();
		t = tok.getToken();
	}
	cout << *t << endl;
}
//-------------------------------------------------------
void VirtualMachine::compile(const string & input)
{

}
//-------------------------------------------------------
Value* VirtualMachine::call(Value* object, const string& cls, const string& name, int argCnt, ...)
{
	va_list args;
	va_start(args, argCnt);
	Value* result = call(object, cls, name, argCnt, args);
	va_end(args);
	return result;
}
Value* VirtualMachine::call(Value* object, const string& cls, const string& name, int argCnt, va_list args)
{
	Class* c = mSymbols.lookupClass(cls);
	Method* m;
	if (c == nullptr || (m = c->lookupMethod(name)) == nullptr)
		throw string("method does not exist: ") + cls + "." + name;
	for (int i = 0; i < argCnt; i++)
	{
		Value* arg = va_arg(args, Value*);
		push(arg);
	}
	if (object == nullptr)
		object = c->nullInstance();
	makeCall((Instance*)object, m, name, argCnt, 0);
	Value* result = pop();
	return result;
}
//-------------------------------------------------------
void VirtualMachine::makeCall(Instance* object, Method* method, const string& methodName, int paramCnt, int localCnt)
{
	newFrame(object, paramCnt, localCnt);
	try
	{
		if (method == nullptr)
			throw "undefined method";
		if (paramCnt != method->paramCnt())
			throw "wrong number of parameters";
		method->run(*this);
	}
	catch (const char* msg)
	{
		out() << msg << endl;
		out() << object->cls()->name << "." << methodName << "(";
		for (int i = 0; i < paramCnt; i++)
		{
			if (i > 0)
				out() << ",";
			out() << param(i)->toString();
		}
		out() << ")" << endl;
		Return(nullptr); // pop stack frame
		throw msg;
	}
}
//-------------------------------------------------------
Class* VirtualMachine::addClass(const string& name, int varCnt, ...)
{
	va_list args;
	va_start(args, varCnt);
	Class* cls = addClass(name, varCnt, args);
	va_end(args);
	return cls;
}
//-------------------------------------------------------
Class* VirtualMachine::addClass(const string& name, int varCnt, va_list args)
{
	Class* cls = (Class*)mSymbols.add(name, Symbol::Kind::CLASS);
	for (int i = 0; i < varCnt; i++)
	{
		string var = va_arg(args, char*);
		cls->add(var, Symbol::Kind::MEMBER);
	}
	return cls;
}
//-------------------------------------------------------
void VirtualMachine::addMethod(Class* cls, const string& name, CallBack* handler, int paramCnt, ...)
{
	va_list args;
	va_start(args, paramCnt);
	addMethod(cls, name, handler, paramCnt, args);
	va_end(args);
}
//-------------------------------------------------------
void VirtualMachine::addMethod(Class* cls, const string& name, CallBack* handler, int paramCnt, va_list args)
{
	if (cls == nullptr)
		throw "bad class";
	// add code to make sure that method does not exist
	Method* m = (Method*)cls->add(name, Symbol::Kind::METHOD);
	m->setHandler(new NativeMethodHandler(handler));
	for (int i = 0; i < paramCnt; i++)
	{
		string param = va_arg(args, char*);
		m->add(param, Symbol::Kind::PARAM);
	}
	m->link();
}
//-------------------------------------------------------
ValueType VirtualMachine::type(Value* v) { return v->type(); }

//-------------------------------------------------------
Value* VirtualMachine::value(bool b) { return Value::boolean(b); }
Value* VirtualMachine::value(double n) { return Value::number(n); }
Value* VirtualMachine::value(const string& s) { return Value::str(s); }
Value* VirtualMachine::valueTuple(const vector<Value*>& t) { return Value::tuple(t); }
Value* VirtualMachine::valueList(const vector<Value*>& l) { return Value::list(l); }

//-------------------------------------------------------
bool   VirtualMachine::boolean(Value* v) { return v->boolean(); }
double VirtualMachine::number(Value* v) { return v->number(); }
string VirtualMachine::str(Value* v) { return v->toString(); }
vector<Value*>& VirtualMachine::tuple(Value* v) { return v->tuple(); }
vector<Value*>& VirtualMachine::list(Value* v) { return v->list(); }

//-------------------------------------------------------
void VirtualMachine::release(Value* v) { if (v) v->deref(); }

//-------------------------------------------------------
void VirtualMachine::verifyParamCnt(int n)
{
	if (mStack.paramCnt() != n)
		throw "wrong number of parameters passed to function";
}
Value* VirtualMachine::param(int i) { return mStack.param(i); }
bool VirtualMachine::boolParam(int i) { return mStack.param(i)->boolean(); }
double VirtualMachine::numberParam(int i) { return mStack.param(i)->number(); }
string& VirtualMachine::stringParam(int i) { return mStack.param(i)->str(); }
vector<Value*>& VirtualMachine::tupleParam(int i) { return mStack.param(i)->tuple(); }
vector<Value*>& VirtualMachine::listParam(int i) { return mStack.param(i)->list(); }

//-------------------------------------------------------
void VirtualMachine::Return(Value* v) { mStack.popFrame(v); }
void VirtualMachine::Return(bool v) { mStack.popFrame(Value::boolean(v)); }
void VirtualMachine::Return(double v) { mStack.popFrame(Value::number(v)); }
void VirtualMachine::Return(const string& v) { mStack.popFrame(Value::str(v)); }
void VirtualMachine::ReturnTuple(vector<Value*>& v) { mStack.popFrame(Value::tuple(v)); }
void VirtualMachine::ReturnList(vector<Value*>& v) { mStack.popFrame(Value::tuple(v)); }

//-------------------------------------------------------
void VirtualMachine::push(Value* v) { mStack.push(v); }
Value* VirtualMachine::pop() { return mStack.pop(); }
void VirtualMachine::newFrame(Value* inst, int paramCnt, int localCnt) { mStack.newFrame(inst, paramCnt, localCnt); }
//-------------------------------------------------------
