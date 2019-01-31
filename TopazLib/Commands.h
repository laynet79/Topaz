#pragma once
#include "VirtualMachine.h"
#include "Command.h"
#include "Class.h"
#include "Method.h"
#include "Stack.h"

//-------------------------------------------------------
// Add
//-------------------------------------------------------
class Add : public Command
{
public:
	Add(Symbol* s1, Symbol* s2, Symbol* d, int line) : Command(line, s1, s2, d) {}
	string name() const override { return "ADD"; }
	bool run(VirtualMachine& vm, int& pc) override
	{
		switch (type(vm, a))
		{
		case NUMBER:
			set(vm, c, number(vm, a) + number(vm, b));
			break;
		case STRING:
			set(vm, c, str(vm, a) + str(vm, b));
			break;
		case LIST:
			set(vm, c, listPtr(vm, a)->add(listPtr(vm, b)));
			break;
		default:
			error("incompatible types");
		}
		pc += 1;
		return true;
	}
};
//-------------------------------------------------------
// Sub
//-------------------------------------------------------
class Sub : public Command
{
public:
	Sub(Symbol* s1, Symbol* s2, Symbol* d, int line) : Command(line, s1, s2, d) {}
	string name() const override { return "SUB"; }
	bool run(VirtualMachine& vm, int& pc) override
	{
		set(vm, c, number(vm, a) - number(vm, b));
		pc += 1;
		return true;
	}
};
//-------------------------------------------------------
// Mult
//-------------------------------------------------------
class Mult : public Command
{
public:
	Mult(Symbol* s1, Symbol* s2, Symbol* d, int line) : Command(line, s1, s2, d) {}
	string name() const override { return "MUL"; }
	bool run(VirtualMachine& vm, int& pc) override
	{
		set(vm, c, number(vm, a) * number(vm, b));
		pc += 1;
		return true;
	}
};
//-------------------------------------------------------
// Div
//-------------------------------------------------------
class Div : public Command
{
public:
	Div(Symbol* s1, Symbol* s2, Symbol* d, int line) : Command(line, s1, s2, d) {}
	string name()const  override { return "DIV"; }
	bool run(VirtualMachine& vm, int& pc) override
	{
		double B = number(vm, b);
		if (B == 0.0)
			error("divide by zero");
		set(vm, c, number(vm, a) / B);
		pc += 1;
		return true;
	}
};
//-------------------------------------------------------
// Mod
//-------------------------------------------------------
class Mod : public Command
{
public:
	Mod(Symbol* s1, Symbol* s2, Symbol* d, int line) : Command(line, s1, s2, d) {}
	string name() const override { return "MOD"; }
	bool run(VirtualMachine& vm, int& pc) override
	{
		double B = number(vm, b);
		if (B == 0.0)
			error("divide by zero");
		set(vm, c, fmod(number(vm, a), B));
		pc += 1;
		return true;
	}
};
//-------------------------------------------------------
// Index
//-------------------------------------------------------
class Index : public Command
{
public:
	Index(Symbol* v, Symbol* i, Symbol* d, int line) : Command(line, v, i, d) {}
	string name() const override { return "IDX"; }
	bool run(VirtualMachine& vm, int& pc) override
	{
		int index = integer(vm, b);
		switch (type(vm, a))
		{
		case ValueType::STRING:
		{
			string s = str(vm, a);
			if (index >= s.size())
				error("index out of range");
			set(vm, c, string(1, s[index]));
			break;
		}
		case ValueType::TUPLE:
		case ValueType::LIST:
		{
			vector<Value*>& s = tuple(vm, a);
			if (index >= s.size())
				error("index out of range");
			set(vm, c, s[index]);
			break;
		}

		default:
			error("invalid type for indexing");
			break;
		}
		pc += 1;
		return true;
	}
};
//-------------------------------------------------------
// Push
//-------------------------------------------------------
class Push : public Command
{
public:
	Push(Symbol* s, int line = 0) : Command(line, s) {}
	string name() const override { return "PSH"; }
	bool run(VirtualMachine& vm, int& pc) override
	{
		vm.push(value(vm, 0));
		return true;
	}
};
//-------------------------------------------------------
// Pop
//-------------------------------------------------------
class Pop : public Command
{
public:
	Pop(Symbol* d, int line = 0) : Command(line, d) {}
	string name() const override { return "PSH"; }
	bool run(VirtualMachine& vm, int& pc) override
	{
		set(vm, a, vm.pop());
		return true;
	}
};
//-------------------------------------------------------
// Call
//-------------------------------------------------------
class Call : public Command
{
public:
	Call(Symbol* obj, Symbol* meth, Symbol* pcnt, int line = 0) : Command(line, obj, meth, pcnt) {}
	string name() const override { return "CAL"; }
	bool run(VirtualMachine& vm, int& pc) override
	{
		Instance* object = inst(vm, a);
		Symbol* selector = b;
		int paramCnt = integer(vm, c);
		Method* m = object->cls()->lookupMethod(selector);
		int localCnt = m ? m->localCnt() : 0;
		vm.makeCall((Instance*)object, m, selector->name, paramCnt, 0);
		pc += 1;
		return true;
	}
};
//-------------------------------------------------------
// Return
//-------------------------------------------------------
class Return : public Command
{
public:
	Return(Symbol* s, int line = 0) : Command(line, s) {}
	string name() const override { return "RTN"; }
	bool run(VirtualMachine& vm, int& pc) override
	{
		Value*& v = value(vm, a);
		vm.Return(v);
		pc += 1;
		return false;
	}
};
//-------------------------------------------------------
// Jump
//-------------------------------------------------------
class Jump : public Command
{
public:
	Jump(Symbol* a, int line = 0) : Command(line, a) {}
	string name() const override { return "JMP"; }
	bool run(VirtualMachine& vm, int& pc) override
	{
		pc = integer(vm, a);
		return true;
	}
};
//-------------------------------------------------------
// BranchFalse
//-------------------------------------------------------
class BranchFalse : public Command
{
public:
	BranchFalse(Symbol* s, Symbol* a, int line = 0) : Command(line, s, a) {}
	string name() const override { return "BRF"; }
	bool run(VirtualMachine& vm, int& pc) override
	{
		if (boolean(vm, a))
			pc += 1;
		else
			pc = integer(vm, b);
		return true;
	}
};
//-------------------------------------------------------
// LT
//-------------------------------------------------------
class LT : public Command
{
public:
	LT(Symbol* s1, Symbol* s2, Symbol* d, int line) : Command(line, s1, s2, d) {}
	string name() const override { return "LT "; }
	bool run(VirtualMachine& vm, int& pc) override
	{
		set(vm, c, number(vm, a) < number(vm, b));
		pc += 1;
		return true;
	}
};
//-------------------------------------------------------
// LTE
//-------------------------------------------------------
class LTE : public Command
{
public:
	LTE(Symbol* s1, Symbol* s2, Symbol* d, int line) : Command(line, s1, s2, d) {}
	string name() const override { return "LTE"; }
	bool run(VirtualMachine& vm, int& pc) override
	{
		set(vm, c, number(vm, a) <= number(vm, b));
		pc += 1;
		return true;
	}
};
//-------------------------------------------------------
// GT
//-------------------------------------------------------
class GT : public Command
{
public:
	GT(Symbol* s1, Symbol* s2, Symbol* d, int line) : Command(line, s1, s2, d) {}
	string name() const override { return "GT "; }
	bool run(VirtualMachine& vm, int& pc) override
	{
		set(vm, c, number(vm, a) > number(vm, b));
		pc += 1;
		return true;
	}
};
//-------------------------------------------------------
// GTE
//-------------------------------------------------------
class GTE : public Command
{
public:
	GTE(Symbol* s1, Symbol* s2, Symbol* d, int line) : Command(line, s1, s2, d) {}
	string name() const override { return "GTE"; }
	bool run(VirtualMachine& vm, int& pc) override
	{
		set(vm, c, number(vm, a) >= number(vm, b));
		pc += 1;
		return true;
	}
};
//-------------------------------------------------------
// EQ
//-------------------------------------------------------
class EQ : public Command
{
public:
	EQ(Symbol* s1, Symbol* s2, Symbol* d, int line) : Command(line, s1, s2, d) {}
	string name() const override { return "EQ "; }
	bool run(VirtualMachine& vm, int& pc) override
	{
		set(vm, c, *value(vm, a) == *value(vm, b));
		pc += 1;
		return true;
	}
};
//-------------------------------------------------------
// NEQ
//-------------------------------------------------------
class NEQ : public Command
{
public:
	NEQ(Symbol* s1, Symbol* s2, Symbol* d, int line) : Command(line, s1, s2, d) {}
	string name() const override { return "EQ "; }
	bool run(VirtualMachine& vm, int& pc) override
	{
		set(vm, c, *value(vm, a) != *value(vm, b));
		return true;
	}
};
//-------------------------------------------------------
// AND
//-------------------------------------------------------
class AND : public Command
{
public:
	AND(Symbol* s1, Symbol* s2, Symbol* d, int line) : Command(line, s1, s2, d) {}
	string name() const override { return "AND"; }
	bool run(VirtualMachine& vm, int& pc) override
	{
		set(vm, c, boolean(vm,a) && boolean(vm, b));
		pc += 1;
		return true;
	}
};
//-------------------------------------------------------
// OR
//-------------------------------------------------------
class OR : public Command
{
public:
	OR(Symbol* s1, Symbol* s2, Symbol* d, int line) : Command(line, s1, s2, d) {}
	string name() const override { return "OR "; }
	bool run(VirtualMachine& vm, int& pc) override
	{
		set(vm, c, boolean(vm, a) || boolean(vm, b));
		pc += 1;
		return true;
	}
};
//-------------------------------------------------------
// NOT
//-------------------------------------------------------
class NOT : public Command
{
public:
	NOT(Symbol* s, Symbol* d, int line) : Command(line, s, d) {}
	string name() const override { return "NOT"; }
	bool run(VirtualMachine& vm, int& pc) override
	{
		set(vm, c, ! boolean(vm, a));
		pc += 1;
		return true;
	}
};
