#include "Value.h"
#include "Class.h"

//-------------------------------------------------------
Value* Null::sNull = new Null();
Value* Boolean::sTrue = new Boolean(true);
Value* Boolean::sFalse = new Boolean(true);
//-------------------------------------------------------
Value* Value::boolean(bool v) { return Boolean::value(v);  }
Value* Value::number(double v) { return new Number(v); }
Value* Value::str(const string& v) { return new String(v); }
Value* Value::object(Class* cls) { return cls->createInstance(); }
Value* Value::tuple(const vector<Value*>& v) { return new Tuple(v); }
Value* Value::list(const vector<Value*> v) { return new List(v); }
//-------------------------------------------------------
bool Value::boolean() { if (type() != ValueType::BOOLEAN) throw "boolean expected"; return ((Boolean*)this)->value(); }
double Value::number() { if (type() != ValueType::NUMBER) throw "number expected"; return ((Number*)this)->value(); }
string&Value::str() { if (type() != ValueType::STRING) throw "string expected"; return ((String*)this)->value(); }
string Value::pstr() { return toString(); }
Instance* Value::object() { if (type() != ValueType::OBJECT) throw "object expected"; return (Instance*)this; }
vector<Value*>& Value::tuple() { if (type() != ValueType::TUPLE) throw "tuple expected"; return ((Tuple*)this)->value(); }
Tuple* Value::tuplePtr() { if (type() != ValueType::TUPLE) throw "tuple expected"; return (Tuple*)this; }
vector<Value*>& Value::list() { if (type() != ValueType::LIST) throw "tuple expected"; return ((List*)this)->value(); }
List* Value::listPtr() { if (type() != ValueType::LIST) throw "tuple expected"; return (List*)this; }
//-------------------------------------------------------
bool Value::operator == (const Value& b)
{
	switch (type())
	{
	case ValueType::BOOLEAN:
		return ((Boolean*)this)->value() == ((Boolean*)this)->value();
	case ValueType::NUMBER:
		return ((Number*)this)->value() == ((Number*)this)->value();
	case ValueType::STRING:
		return ((String*)this)->value() == ((String*)this)->value();
	case ValueType::OBJECT:
	case ValueType::NIL:
		return this == &b;
	case ValueType::TUPLE:
		return *(Tuple*)this == *(Tuple*)this;
	case ValueType::LIST:
		return *(List*)this == *(List*)this;
	default:
		return false;
	}
}

//-------------------------------------------------------
Instance::Instance(Class* cls, int size) : mClass(cls), mValue(size)
{
	for (int i = 0; i < size; i++)
		mValue.push_back(Null::value());
}
//-------------------------------------------------------
string Instance::toString()
{
	return "<Object:" + mClass->name + ">";
}
//-------------------------------------------------------
