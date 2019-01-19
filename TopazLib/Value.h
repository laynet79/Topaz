#pragma once
#include <iostream>
#include <string>
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
	enum Type { INDEX=1, NIL=2, BOOL=4, NUMBER=8, STRING=16, TUPLE=32, LIST=64, ANY=0xFF  };

	Value(bool value) : mType(BOOL), mBool(value) {}
	Value(double value) : mType(NUMBER), mNumber(value) {}
	Value(String* value) : mType(STRING), mString(value) {}
	Value(Tuple* value) : mType(TUPLE), mTuple(value) {}
	Value(List* value) : mType(LIST), mList(value) {}
	Value() : mType(NIL), mObject(nullptr) {}
	Value(int index) : mType(INDEX), mIndex(index) {}

	~Value();
	Value& operator = (const Value& value);

	int index() const		{ return mIndex;  }
	Type type() const		{ return mType;   }
	bool boolean() const	{ return mBool;   }
	double number() const	{ return mNumber; }
	Object* object() const  { return mObject; }
	String* str() const	{ return mString; }
	Tuple* tuple() const	{ return mTuple;  }
	List* list() const		{ return mList;   }

	string typeName()
	{
		static const string typeNames[] = { "INDEX", "NIL", "BOOL", "NUMBER", "STRING", "TUPLE", "LIST", "ANY" };
		return typeNames[mType];
	}

	string toString();
private:
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
};

#pragma warning(pop)

//-------------------------------------------------------
ostream& operator << (ostream& out, const Value& v);
//-------------------------------------------------------
