#include "Value.h"
#include "Collection.h"

#include <iomanip>
#include <sstream>
using namespace std;

//-------------------------------------------------------
Value::~Value()
{
	if (mType >= STRING)
		mObject->deref();
}
//-------------------------------------------------------
Value& Value::operator = (const Value& value)
{
	if (mType >= STRING)
		mObject->deref();
	this->mType = value.mType;
	this->mObject = value.mObject;
	if (mType >= STRING)
		mObject->ref();
	return *this;
}
//-------------------------------------------------------
string Value::toString()
{
	ostringstream s;
	s << *this;
	return s.str();
}
//-------------------------------------------------------
ostream& operator << (ostream& out, const Value& v)
{
	switch (v.type())
	{
	case Value::BOOL:
		out << v.boolean() ? "true" : "false";
		break;
	case Value::NUMBER:
		if ((double)(long long)v.number() == v.number())
			out << (long long)v.number();
		else
			out << fixed << setprecision(6) << v.number();
		break;
	case Value::INDEX:
		out << "<Index:" << v.index() << ">";
		break;
	case Value::NIL:
		out << "nil";
		break;
	default:
		out << v.object();
		break;
	}
	return out;
}
//-------------------------------------------------------
