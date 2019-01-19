#include "Value.h"
#include "Collection.h"

#include <iomanip>
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
ostream& operator << (ostream& out, const Value& v)
{
	switch (v.mType)
	{
	case Value::BOOL:
		out << v.mBool ? "true" : "false";
		break;
	case Value::NUMBER:
		if ((double)(long long)v.mNumber == v.mNumber)
			out << (long long)v.mNumber;
		else
			out << fixed << setprecision(6) << v.mNumber;
		break;
	case Value::INDEX:
		out << "<Index:" << v.mIndex << ">";
		break;
	case Value::NIL:
		out << "nil";
		break;
	default:
		out << v.mObject;
		break;
	}
	return out;
}
//-------------------------------------------------------
