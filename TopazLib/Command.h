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
	Value*& value(VirtualMachine& vm, Symbol* s)			{ return s->value(vm);				}
	ValueType type(VirtualMachine& vm, Symbol* s)			{ return s->value(vm)->type();		}
	bool boolean(VirtualMachine& vm, Symbol* s)				{ return s->value(vm)->boolean();	}
	double number(VirtualMachine& vm, Symbol* s)			{ return s->value(vm)->number();	}
	string& str(VirtualMachine& vm, Symbol* s)				{ return s->value(vm)->str();		}
	string pstr(VirtualMachine& vm, Symbol* s)				{ return s->value(vm)->pstr();		}
	Instance* object(VirtualMachine& vm, Symbol* s)			{ return s->value(vm)->object();	}
	vector<Value*>& tuple(VirtualMachine& vm, Symbol* s)	{ return s->value(vm)->tuple();		}
	Tuple* tuplePtr(VirtualMachine& vm, Symbol* s)			{ return s->value(vm)->tuplePtr();  }
	vector<Value*>& list(VirtualMachine& vm, Symbol* s)		{ return s->value(vm)->list();      }
	List* listPtr(VirtualMachine& vm, Symbol* s)			{ return s->value(vm)->listPtr();   }

	void error(const string& msg) { throw string("line ") + to_string(mLine) + " " + msg; }
};
//-------------------------------------------------------
inline
ostream& operator << (ostream& out, const Command& c)
{
	out << c.name() << " " << (c.a ? c.a->id : "") << " " << (c.b ? c.b->id : "") << " " << (c.c ? c.c->id : "");
	return out;
}
//-------------------------------------------------------
