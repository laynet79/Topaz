#pragma once
#include <iostream>
#include <string>
using namespace std;
#include "Symbol.h"

//-------------------------------------------------------
// This class represents a virtual machine instruction
// (base class)
//-------------------------------------------------------
class Command
{
public:
	Command(int line, Symbol* A = nullptr, Symbol* B = nullptr, Symbol* C = nullptr) : a(A), b(B), c(C), mLine(line) {}
	virtual string name() const = 0;
	virtual bool run(VirtualMachine& vm, int& pc) = 0;
	Symbol *a, *b, *c;
	int mLine;
protected:
	//------------------------------------------
	// These methods are called to set the destination value
	void set(VirtualMachine& vm, Symbol* dst, bool v) { Value::set(dst->value(vm), Value::boolean(v)); }
	void set(VirtualMachine& vm, Symbol* dst, double v) { Value::set(dst->value(vm), Value::number(v)); }
	void set(VirtualMachine& vm, Symbol* dst, const string& v) { Value::set(dst->value(vm), Value::str(v)); }
	void setTuple(VirtualMachine& vm, Symbol* dst, vector<Value*>& v) { Value::set(dst->value(vm), Value::tuple(v)); }
	void setList(VirtualMachine& vm, Symbol* dst, vector<Value*>& v) { Value::set(dst->value(vm), Value::list(v)); }
	void setList(VirtualMachine& vm, Symbol* dst, List* v) { Value::set(dst->value(vm), v); }

	ValueType type(VirtualMachine& vm, Symbol* s)			{ return s->value(vm)->type();		}
	Value*& value(VirtualMachine& vm, Symbol* s)            { return s->value(vm);              }
	bool boolean(VirtualMachine& vm, Symbol* s)				{ return s->value(vm)->boolean();	}
	double number(VirtualMachine& vm, Symbol* s)			{ return s->value(vm)->number();    }
	int integer(VirtualMachine& vm, Symbol* s)				{ return (int)s->value(vm)->number(); }
	string str(VirtualMachine& vm, Symbol* s)				{ return s->value(vm)->str();		}
	Instance* inst(VirtualMachine& vm, Symbol* s)			{ return s->value(vm)->inst();      }
	vector<Value*>& tuple(VirtualMachine& vm, Symbol* s)	{ return s->value(vm)->tuple();		}
	Tuple* tuplePtr(VirtualMachine& vm, Symbol* s)			{ return s->value(vm)->tuplePtr();  }
	vector<Value*>& list(VirtualMachine& vm, Symbol* s)		{ return s->value(vm)->list();      }
	List* listPtr(VirtualMachine& vm, Symbol* s)			{ return s->value(vm)->listPtr();   }

	void error(const string& msg) { throw msg.c_str(); }
};
//-------------------------------------------------------
inline
ostream& operator << (ostream& out, const Command& c)
{
	out << c.name() << " " << (c.a ? c.a->id : "") << " " << (c.b ? c.b->id : "") << " " << (c.c ? c.c->id : "");
	return out;
}
//-------------------------------------------------------
