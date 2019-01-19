#pragma once
#include <iostream>
#include <string>
using namespace std;
#include "Value.h"

class Class;

//-------------------------------------------------------
// this class serves as the base class for all reference
// types and implements reference counting
//-------------------------------------------------------
class Object
{
public:
	Object() : mRefCnt(1) {}
	virtual ~Object() {}
	void ref()   { mRefCnt++; }
	void deref() { if (--mRefCnt == 0) delete this; }
	virtual void toString(ostream& out) const = 0;
protected:
	int mRefCnt;
};
//-------------------------------------------------------
ostream& operator << (ostream& out, const Object& o);

//-------------------------------------------------------
// This class wrappers a C++ string
//-------------------------------------------------------
class  String : public Object
{
public:
	String(const string& value) { mString = value; }
	string& value() { return mString; }
	String* operator + (const String& b) { return new String(mString + b.mString); }
	virtual void toString(ostream& out) const { out << "\"" << mString << "\""; }
protected:
	string mString;
};

//-------------------------------------------------------
// This class serves as the base class for all collection
// Collection types
//-------------------------------------------------------
class Collection : public Object
{
public:
	Collection() {}
};

//-------------------------------------------------------
// This class serves as the base class for all array based
// Collection types
//-------------------------------------------------------
class  Array : public Collection
{
public:
	Array(int size) : mSize(size), mValues(new Value[size]) {}
	~Array()   { delete[] mValues; }
	int size() { return mSize; }
	Value& operator [] (int i) const { return mValues[i]; }
protected:
	int mSize;
	Value* mValues;
};

//-------------------------------------------------------
// this class represents a class instance
//-------------------------------------------------------
class Instance : public Array
{
public:
	Instance(Class* cls);
	Class* type() { return mClass; }
	void toString(ostream& out) const override;
protected:
	Class* mClass;
};

//-------------------------------------------------------
// this class represents a Tuple
//-------------------------------------------------------
class Tuple : public Array
{
public:
	Tuple(int size) : Array(size) {}
	void toString(ostream& out) const override;
};

//-------------------------------------------------------
// this class represents an array based List
//-------------------------------------------------------
class List : public Array
{
public:
	List(int size, int growSize=10) : Array(size), mGrowSize(growSize), mBufSize(size) {}
	void append(const Value& value);
	List* operator + (const List& b);
	List* slice(int start, int end);
	void toString(ostream& out) const override;
protected:
	int mGrowSize;
	int mBufSize;
};
//-------------------------------------------------------
