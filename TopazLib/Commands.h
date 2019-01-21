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
		Value& s1 = value(vm, 0);
		Value& s2 = value(vm, 1);
		Value& d = value(vm, 2);
		if (s2.type() != Value::STRING && s1.type() != s2.type())
			error("incompatible types");
		switch (s1.type())
		{
		case Value::NUMBER:
			d = s1.number() + s2.number();
			break;
		case Value::STRING:
			d = new String(s1.str()->value() + s2.toString());
			break;
		case Value::LIST:
			d = *s1.list() + *s2.list();
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
		Value& s1 = value(vm, 0, Value::NUMBER);
		Value& s2 = value(vm, 1, Value::NUMBER);
		Value& d = value(vm, 2);
		d = s1.number() - s2.number();
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
		Value& s1 = value(vm, 0, Value::NUMBER);
		Value& s2 = value(vm, 1, Value::NUMBER);
		Value& d = value(vm, 2);
		d = s1.number() * s2.number();
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
		Value& s1 = value(vm, 0, Value::NUMBER);
		Value& s2 = value(vm, 1, Value::NUMBER);
		Value& d = value(vm, 2);
		if (s2.number() == 0.0)
			error("divide by zero");
		d = s1.number() / s2.number();
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
		Value& s1 = value(vm, 0, Value::NUMBER);
		Value& s2 = value(vm, 1, Value::NUMBER);
		Value& d = value(vm, 2);
		if (s2.number() == 0.0)
			error("divide by zero");
		d = fmod(s1.number(), s2.number());
		pc += 1;
		return true;
	}
};
//-------------------------------------------------------
// Int
//-------------------------------------------------------
class Int : public Command
{
public:
	Int(Symbol* s, Symbol* d, int line) : Command(line, s, d) {}
	string name() const override { return "INT"; }
	bool run(VirtualMachine& vm, int& pc) override
	{
		Value& s = value(vm, 0, Value::NUMBER);
		Value& d = value(vm, 1);
		d = floor(s.number());
		pc += 1;
		return true;
	}
};
//-------------------------------------------------------
// Frac
//-------------------------------------------------------
class Frac : public Command
{
public:
	Frac(Symbol* s, Symbol* d, int line) : Command(line, s, d) {}
	string name() const override { return "FRC"; }
	bool run(VirtualMachine& vm, int& pc) override
	{
		Value& s = value(vm, 0, Value::NUMBER);
		Value& d = value(vm, 1);
		d = s.number() - floor(s.number());
		pc += 1;
		return true;
	}
};
//-------------------------------------------------------
// Sqrt
//-------------------------------------------------------
class Sqrt : public Command
{
public:
	Sqrt(Symbol* s, Symbol* d, int line) : Command(line, s, d) {}
	string name() const override { return "SQT"; }
	bool run(VirtualMachine& vm, int& pc) override
	{
		Value& s = value(vm, 0, Value::NUMBER);
		Value& d = value(vm, 1);
		d = sqrt(s.number());
		pc += 1;
		return true;
	}
};
//-------------------------------------------------------
// Pow
//-------------------------------------------------------
class Pow : public Command
{
public:
	Pow(Symbol* s1, Symbol* s2, Symbol* d, int line) : Command(line, s1, s2, d) {}
	string name() const override { return "POW"; }
	bool run(VirtualMachine& vm, int& pc) override
	{
		Value& s1 = value(vm, 0, Value::NUMBER);
		Value& s2 = value(vm, 1, Value::NUMBER);
		Value& d = value(vm, 2);
		d = pow(s1.number(), s2.number());
		pc += 1;
		return true;
	}
};
//-------------------------------------------------------
// Sin
//-------------------------------------------------------
class Sin : public Command
{
public:
	Sin(Symbol* s, Symbol* d, int line) : Command(line, s, d) {}
	string name() const override { return "SIN"; }
	bool run(VirtualMachine& vm, int& pc) override
	{
		Value& s = value(vm, 0, Value::NUMBER);
		Value& d = value(vm, 1);
		d = sin(s.number());
		pc += 1;
		return true;
	}
};
//-------------------------------------------------------
// Cos
//-------------------------------------------------------
class Cos : public Command
{
public:
	Cos(Symbol* s, Symbol* d, int line) : Command(line, s, d) {}
	string name() const override { return "COS"; }
	bool run(VirtualMachine& vm, int& pc) override
	{
		Value& s = value(vm, 0, Value::NUMBER);
		Value& d = value(vm, 1);
		d = cos(s.number());
		pc += 1;
		return true;
	}
};
//-------------------------------------------------------
// Tan
//-------------------------------------------------------
class Tan : public Command
{
public:
	Tan(Symbol* s, Symbol* d, int line) : Command(line, s, d) {}
	string name() const override { return "TAN"; }
	bool run(VirtualMachine& vm, int& pc) override
	{
		Value& s = value(vm, 0, Value::NUMBER);
		Value& d = value(vm, 1);
		d = tan(s.number());
		pc += 1;
		return true;
	}
};
//-------------------------------------------------------
// Asin
//-------------------------------------------------------
class Asin : public Command
{
public:
	Asin(Symbol* s, Symbol* d, int line) : Command(line, s, d) {}
	string name() const override { return "ASN"; }
	bool run(VirtualMachine& vm, int& pc) override
	{
		Value& s = value(vm, 0, Value::NUMBER);
		Value& d = value(vm, 1);
		d = asin(s.number());
		pc += 1;
		return true;
	}
};
//-------------------------------------------------------
// Acos
//-------------------------------------------------------
class Acos : public Command
{
public:
	Acos(Symbol* s, Symbol* d, int line) : Command(line, s, d) {}
	string name() const override { return "ACS"; }
	bool run(VirtualMachine& vm, int& pc) override
	{
		Value& s = value(vm, 0, Value::NUMBER);
		Value& d = value(vm, 1);
		d = acos(s.number());
		pc += 1;
		return true;
	}
};
//-------------------------------------------------------
// Asin
//-------------------------------------------------------
class Atan : public Command
{
public:
	Atan(Symbol* s, Symbol* d, int line) : Command(line, s, d) {}
	string name() const override { return "ATN"; }
	bool run(VirtualMachine& vm, int& pc) override
	{
		Value& s = value(vm, 0, Value::NUMBER);
		Value& d = value(vm, 1);
		d = atan(s.number());
		pc += 1;
		return true;
	}
};
//-------------------------------------------------------
// Atan2
//-------------------------------------------------------
class Atan2 : public Command
{
public:
	Atan2(Symbol* s1, Symbol* s2, Symbol* d, int line) : Command(line, s1, s2, d) {}
	string name() const override { return "AT2"; }
	bool run(VirtualMachine& vm, int& pc) override
	{
		Value& s1 = value(vm, 0, Value::NUMBER);
		Value& s2 = value(vm, 1, Value::NUMBER);
		Value& d = value(vm, 2);
		d = atan2(s1.number(), s2.number());
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
		vm.stack().push(value(vm, 0));
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
		value(vm, 0) = vm.stack().pop();
		return true;
	}
};
//-------------------------------------------------------
// Call
//-------------------------------------------------------
class Call : public Command
{
public:
	Call(Symbol* i, Symbol* m, int line = 0) : Command(line, m) {}
	string name() const override { return "CAL"; }
	bool run(VirtualMachine& vm, int& pc) override
	{
		Instance* inst = (Instance*)value(vm, 0).object();
		Symbol* selector = mArg[1];
		Method* m = inst->type()->lookupMethod(selector);
		if (m == nullptr)
			error(string("undefined method: ") + selector->name + string(" class: ") + inst->type()->name);
		vm.stack().newFrame(inst, m->paramCnt(), m->localCnt());
		m->run(vm);
		Value result = vm.stack().pop();
		vm.stack().pop(m->paramCnt());
		vm.stack().push(result);
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
		Value& v = value(vm, 0);
		vm.stack().popFrame();
		vm.stack().push(v);
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
		pc = value(vm, 0).index();
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
		Value& s = value(vm, 0, Value::BOOL);
		Value& a = value(vm, 1, Value::BOOL);
		if (s.boolean())
			pc += 1;
		else
			pc = a.index();
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
		Value& s1 = value(vm, 0, Value::NUMBER);
		Value& s2 = value(vm, 1, Value::NUMBER);
		Value& d = value(vm, 2);
		d = s1.number() < s2.number();
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
		Value& s1 = value(vm, 0, Value::NUMBER);
		Value& s2 = value(vm, 1, Value::NUMBER);
		Value& d = value(vm, 2);
		d = s1.number() <= s2.number();
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
		Value& s1 = value(vm, 0, Value::NUMBER);
		Value& s2 = value(vm, 1, Value::NUMBER);
		Value& d = value(vm, 2);
		d = s1.number() > s2.number();
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
		Value& s1 = value(vm, 0, Value::NUMBER);
		Value& s2 = value(vm, 1, Value::NUMBER);
		Value& d = value(vm, 2);
		d = s1.number() >= s2.number();
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
		Value& s1 = value(vm, 0);
		Value& s2 = value(vm, 1);
		Value& d = value(vm, 2);
		bool result = false;
		if (s1.type() == s2.type())
		{
			switch (s1.type())
			{
			case Value::BOOL:
				result = s1.boolean() == s2.boolean();
				break;
			case Value::NUMBER:
				result = s1.number() == s2.number();
				break;
			case Value::STRING:
				result = s1.str()->value() == s2.str()->value();
				break;
			default:
				result = false;
				break;
			}
		}
		d = result;
		pc += 1;
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
		Value& s1 = value(vm, 0, Value::BOOL);
		Value& s2 = value(vm, 1, Value::BOOL);
		Value& d = value(vm, 2);
		d = s1.number() && s2.number();
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
		Value& s1 = value(vm, 0, Value::BOOL);
		Value& s2 = value(vm, 1, Value::BOOL);
		Value& d = value(vm, 2);
		d = s1.number() || s2.number();
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
		Value& s = value(vm, 0, Value::BOOL);
		Value& d = value(vm, 1);
		d = !s.boolean();
		pc += 1;
		return true;
	}
};
