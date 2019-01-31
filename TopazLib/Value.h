#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <stdio.h>
using namespace std;
#include "ValueType.h"
class Class;
class Tuple;
class List;
class Instance;

//-------------------------------------------------------
// This class is the base class for all Topaz data types
//-------------------------------------------------------
class Value
{
public:
	Value() : mRefCnt(0) {}
	virtual ~Value() {}

	static void set(Value*& v, Value* w)
	{
		if (w)
			w->ref();
		if (v)
			v->deref();
		v = w;
	}

	Value* ref()
	{
		if (mRefCnt >= 0)
			mRefCnt++;
		return this;
	}

	Value* deref()
	{
		mRefCnt--;
		if (mRefCnt == 0)
		{
			delete this;
			return nullptr;
		}
		return this;
	}

	ValueType type() { return this ? getType() : NIL; }
	string toString() { return this ? getString() : "null"; }
	string typeName() { return this ? getName() : "null"; };

	static Value* boolean(bool v);
	static Value* number(double v);
	static Value* str(const string& v);
	static Value* object(Class* cls);
	static Value* tuple(const vector<Value*>& v);
	static Value* list(const vector<Value*>& v);

	bool boolean();
	double number();
	int integer();
	string& str();
	Instance* inst();
	vector<Value*>& tuple();
	vector<Value*>& list();
	Tuple* tuplePtr();
	List* listPtr();

	bool operator == (const Value& b);
	bool operator != (const Value& b) { return !(*this == b); }

protected:
	virtual ValueType getType() = 0;
	virtual string getString() = 0;
	string getName()
	{
		static string names[] = { "object", "bool", "number", "string", "tuple", "list" };
		return names[type()];
	}
	int mRefCnt;
};
//-------------------------------------------------------
inline
ostream& operator << (ostream& out, Value& v)
{
	out << v.toString();
	return out;
}
//-------------------------------------------------------
// This class represents a Topaz boolean value
//-------------------------------------------------------
class Boolean : public Value
{
public:
	static Value*& value(bool b) { return b ? sTrue : sFalse; }
	Boolean(bool v) : mValue(v) { mRefCnt = -1; }
	bool value() { return mValue; }
protected:
	ValueType getType() override { return ValueType::BOOLEAN; }
	string getString() override { return mValue ? "true" : "false"; }
	bool mValue;
	static Value* sTrue;
	static Value* sFalse;
};

//-------------------------------------------------------
// This class represents the number data type
//-------------------------------------------------------
class Number : public Value
{
public:
	Number(double v) : mValue(v) {}
	double value() { return mValue; }
	int intValue() { return (int)mValue; }
protected:
	ValueType getType() override { return NUMBER; }
	string getString() override { char buf[32]; sprintf(buf, "%g", mValue); return string(buf); }
	double mValue;
};
//-------------------------------------------------------
// This class represents the string data type
//-------------------------------------------------------
class String : public Value
{
public:
	String(const string& v) : mValue(v) {}
	string& value() { return mValue; }
protected:
	ValueType getType() override { return STRING; }
	string getString() override { return "\"" + mValue + "\""; }
	string mValue;
};
//-------------------------------------------------------
// This class represents the tuple data type
//-------------------------------------------------------
class Tuple : public Value
{
public:
	Tuple(const vector<Value*>& v) : mValue(v) {}

	vector<Value*>& value() { return mValue; }

	bool operator == (const Tuple& b)
	{
		if (mValue.size() != b.mValue.size())
			return false;
		for (int i = 0; i < mValue.size(); i++)
		{
			if (*mValue[i] != *b.mValue[i])
				return false;
		}
		return true;
	}

protected:
	ValueType getType() override { return TUPLE; }

	string getString() override
	{
		string n = "(";
		for (int i = 0; i < mValue.size(); i++)
		{
			if (i > 0)
				n += ",";
			n += mValue[i]->toString();
		}
		n += ")";
		return n;
	}

	vector<Value*> mValue;
};
//-------------------------------------------------------
// This class represents the list data type
//-------------------------------------------------------
class List : public Tuple
{
public:
	List(const vector<Value*>& v) : Tuple(v) {}
	vector<Value*>& value() { return mValue; }

	List* add(List* b)
	{
		vector<Value*> n(mValue.size() + b->mValue.size());
		for (Value* v : mValue)
			n.push_back(v);
		for (Value* v : b->mValue)
			n.push_back(v);
		return new List(n);
	}

	List* slice(int start, int end)
	{
		if (start < 0 || start >= mValue.size() || end < start || end >= mValue.size())
			throw "invalid slice detected";
		vector<Value*> n;
		for (int i = start; i < end; i++)
			n.push_back(mValue[i]);
		return new List(n);
	}

protected:
	ValueType getType() override { return LIST; }

	string getString() override
	{
		string n = "[";
		for (int i = 0; i < mValue.size(); i++)
		{
			if (i > 0)
				n += ",";
			n += mValue[i]->toString();
		}
		n += "]";
		return n;
	}
};
//-------------------------------------------------------
// This class represents an instant object
//-------------------------------------------------------
class Instance : public Value
{
public:
	Instance(Class* cls, int size);
	Value*& operator[](int index) { return mValue[index]; }
	Class* cls() { return mClass; }
protected:
	ValueType getType() override { return OBJECT; }
	string getString() override;
	Class* mClass;
	vector<Value*> mValue;
};
//-------------------------------------------------------
