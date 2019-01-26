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
			Value::set(value(vm, c), Value::number(number(vm, a) + number(vm, b)));
			break;
		case STRING:
			Value::set(value(vm, c), Value::str(str(vm, a) + pstr(vm, b)));
			break;
		case LIST:
			Value::set(value(vm, c), listPtr(vm, a)->add(listPtr(vm, b)));
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
		Value::set(value(vm, c), Value::number(number(vm, a) - number(vm, b)));		pc += 1;
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
		Value::set(value(vm, c), Value::number(number(vm, a) * number(vm, b)));		pc += 1;
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
		Value::set(value(vm, c), Value::number(number(vm, a) / B));
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
		Value::set(value(vm, c), Value::number(fmod(number(vm, a), B)));
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
		Value::set(value(vm, b), Value::number(floor(number(vm, a))));
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
		double A = number(vm, a);
		Value::set(value(vm, b), Value::number(A - floor(A)));
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
		Value::set(value(vm, b), Value::number(sqrt(number(vm, a))));
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
		Value::set(value(vm, c), Value::number(pow(number(vm, a), number(vm, b))));
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
		Value::set(value(vm, b), Value::number(sin(number(vm, a))));
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
		Value::set(value(vm, b), Value::number(cos(number(vm, a))));
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
		Value::set(value(vm, b), Value::number(tan(number(vm, a))));
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
		Value::set(value(vm, b), Value::number(asin(number(vm, a))));
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
		Value::set(value(vm, b), Value::number(acos(number(vm, a))));
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
		Value::set(value(vm, b), Value::number(atan(number(vm, a))));
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
		Value::set(value(vm, c), Value::number(atan2(number(vm, a), number(vm, b))));
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
		Instance* inst = object(vm, a);
		Symbol* selector = b;
		Method* m = inst->cls()->lookupMethod(selector);
		if (m == nullptr)
			error(string("undefined method: ") + selector->name + string(" class: ") + inst->cls()->name);
		vm.stack().newFrame(inst, m->paramCnt(), m->localCnt());
		m->run(vm);
		Value* result = vm.stack().pop();
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
		Value*& v = value(vm, a);
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
		pc = (int)number(vm, a);
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
			pc = (int)number(vm, b);
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
		Value::set(value(vm, c), Value::boolean(number(vm, a) < number(vm, b)));
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
		Value::set(value(vm, c), Value::boolean(number(vm, a) <= number(vm, b)));
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
		Value::set(value(vm, c), Value::boolean(number(vm, a) > number(vm, b)));
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
		Value::set(value(vm, c), Value::boolean(number(vm, a) <= number(vm, b)));
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
		Value::set(value(vm, c), Value::boolean(*value(vm, a) == *value(vm, b)));
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
		Value::set(value(vm, c), Value::boolean(*value(vm, a) != *value(vm, b)));
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
		Value::set(value(vm, c), Value::boolean(boolean(vm,a) && boolean(vm, b)));
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
		Value::set(value(vm, c), Value::boolean(boolean(vm, a) || boolean(vm, b)));
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
		Value::set(value(vm, b), Value::boolean(!boolean(vm, a)));
		pc += 1;
		return true;
	}
};
