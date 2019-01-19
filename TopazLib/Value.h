#pragma once
#include <iostream>
using namespace std;
class Object;
class String;
class Instance;
class Tuple;
class List;

#pragma warning(push)
#pragma warning(disable: 26495)

//-------------------------------------------------------
// this class represents a data Value
//-------------------------------------------------------
class __declspec(dllexport) Value
{
public:
	enum Type { INDEX, NIL, BOOL, NUMBER, STRING, TUPLE, LIST };
	Type mType;
	union
	{
		bool    mBool;
		double  mNumber;
		int     mIndex;
		Object* mObject;
		String* mString;
		Tuple*  mTuple;
		List*   mList;
	};
	Value(bool value) : mType(BOOL), mBool(value) {}
	Value(double value) : mType(NUMBER), mNumber(value) {}
	Value(String* value) : mType(STRING), mString(value) {}
	Value(Tuple* value) : mType(TUPLE), mTuple(value) {}
	Value(List* value) : mType(LIST), mList(value) {}
	Value() : mType(NIL), mObject(nullptr) {}
	Value(int index) : mType(INDEX), mIndex(index) {}
	~Value();
	Value& operator = (const Value& value);
};

#pragma warning(pop)

//-------------------------------------------------------
ostream& operator << (ostream& out, const Value& v);
//-------------------------------------------------------
