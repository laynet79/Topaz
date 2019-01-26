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
		if (mRefCnt > 0)
			mRefCnt++;
		return this;
	}

	Value* deref()
	{
		if (mRefCnt > 0)
			mRefCnt--;
		if (mRefCnt == 0)
		{
			delete this;
			return nullptr;
		}
		return this;
	}

	virtual ValueType type() = 0;
	virtual string toString() = 0;

	string typeName()
	{
		static string names[] = { "object", "bool", "number", "string", "tuple", "list", "null" };
		return names[type()];
	}

	static Value* boolean(bool v);
	static Value* number(double v);
	static Value* str(const string& v);
	static Value* object(Class* cls);
	static Value* tuple(const vector<Value*>& v);
	static Value* list(const vector<Value*> v);

	bool boolean();
	double number();
	string& str();
	string pstr();
	Instance* object();
	vector<Value*>& tuple();
	vector<Value*>& list();
	Tuple* tuplePtr();
	List* listPtr();

	bool operator == (const Value& b);
	bool operator != (const Value& b) { return !(*this == b); }

protected:
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
	ValueType type() override { return ValueType::BOOLEAN; }
	string toString() override { return mValue ? "true" : "false"; }
private:
	bool mValue;
	static Value* sTrue;
	static Value* sFalse;
};

//-------------------------------------------------------
// This class represents the null value
//-------------------------------------------------------
class Null : public Value
{
public:
	Null() { mRefCnt = -1; }
	static Value*& value() { return sNull; }
	ValueType type() override { return NIL; }
	string toString() override { return "null"; }
private:
	static Value* sNull;
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
	ValueType type() override { return NUMBER; }
	string toString() override { char buf[32]; sprintf(buf, "%g", mValue); return string(buf); }
private:
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
	ValueType type() override { return STRING; }
	string toString() override { return mValue; }
private:
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
	ValueType type() override { return TUPLE; }
	string toString() override
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

private:
	vector<Value*> mValue;
};
//-------------------------------------------------------
// This class represents the list data type
//-------------------------------------------------------
class List : public Value
{
public:
	List(const vector<Value*>& v) : mValue(v) {}
	vector<Value*>& value() { return mValue; }
	ValueType type() override { return LIST; }

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

	string toString() override
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

	bool operator == (const List& b)
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

private:
	vector<Value*> mValue;
};
//-------------------------------------------------------
// This class represents an instant object
//-------------------------------------------------------
class Instance : public Value
{
public:
	Instance(Class* cls, int size);
	Value*& operator[](int index) { return mValue[index]; }
	ValueType type() override { return OBJECT; }
	Class* cls() { return mClass; }
	string toString() override;
private:
	Class* mClass;
	vector<Value*> mValue;
};
//-------------------------------------------------------
