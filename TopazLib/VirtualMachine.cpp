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
void VirtualMachine::run()
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
	return nullptr;
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
		string varName = va_arg(args, char*);
		cls->add(varName, Symbol::Kind::MEMBER);
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
		string methodName = va_arg(args, char*);
		m->add(methodName, Symbol::Kind::PARAM);
	}
}
//-------------------------------------------------------
ValueType VirtualMachine::type(Value* v) { return v->type(); }
string VirtualMachine::toStr(Value* v) { return v->toString(); }

//-------------------------------------------------------
Value* VirtualMachine::value(bool b) { return Value::boolean(b); }
Value* VirtualMachine::value(double n) { return Value::number(n)->ref(); }
Value* VirtualMachine::value(const string& s) { return Value::str(s)->ref(); }
Value* VirtualMachine::valueTuple(const vector<Value*>& t) { return Value::tuple(t)->ref(); }
Value* VirtualMachine::valueList(const vector<Value*>& l) { return Value::list(l)->ref(); }

//-------------------------------------------------------
bool   VirtualMachine::boolean(Value* v) { return v->boolean(); }
double VirtualMachine::number(Value* v) { return v->number(); }
string VirtualMachine::str(Value* v) { return v->str(); }
vector<Value*>& VirtualMachine::tuple(Value* v) { return v->tuple(); }
vector<Value*>& VirtualMachine::list(Value* v) { return v->list(); }

//-------------------------------------------------------
void VirtualMachine::release(Value* v) { if (v) v->deref(); }
//-------------------------------------------------------
