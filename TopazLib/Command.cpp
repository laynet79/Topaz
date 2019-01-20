#include "Command.h"

//-------------------------------------------------------
Value& Command::value(VirtualMachine& vm, int arg, Value::Type type)
{
	Value& v = mArg[arg]->value(vm);
	if ((type & v.type()) == 0)
		error("expected type: " + v.typeName());
	return v;
}
//-------------------------------------------------------
ostream& operator << (ostream& out, const Command& c)
{
	out << c.name() << " ";
	for (int i = 0; i < 3; i++)
		if (c.arg(i))
			out << " " << c.arg(i)->id;
	return out;
}
//-------------------------------------------------------