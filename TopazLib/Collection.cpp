#include "Collection.h"
#include "Class.h"

//-------------------------------------------------------
ostream& operator << (ostream& out, const Object& o)
{
	o.toString(out);
	return out;
}
//-------------------------------------------------------
Instance::Instance(Class* cls) : Array(cls->size()), mClass(cls) {}
//-------------------------------------------------------
void Instance::toString(ostream& out) const
{
	out << "<Object: " << mClass->name << ">";
}
//-------------------------------------------------------
void Tuple::toString(ostream& out) const
{
	out << "(";
	for (int i = 0; i < mSize; i++)
	{
		if (i > 0)
			out << ",";
		out << mValues[i];
	}
	out << ")";
}
//-------------------------------------------------------
void List::append(const Value& value)
{
	if (mSize == mBufSize)
	{
		mBufSize = mSize + mGrowSize;
		Value* newValues = new Value[mBufSize];
		for (int i = 0; i < mSize; i++)
			newValues[i] = mValues[i];
		delete[] mValues;
		mValues = newValues;
	}
	mValues[mSize++] = value;
}
//-------------------------------------------------------
List* List::slice(int start, int end)
{
	int newSize = end - start;
	List* s = new List(newSize);
	for (int i = 0; i < newSize; i++)
		(*s)[i] = mValues[i + start];
	return s;
}
//-------------------------------------------------------
List* List::operator + (const List& b)
{
	int newSize = mSize + b.mSize;
	List* n = new List(newSize);
	for (int i = 0; i < mSize; i++)
		(*n)[i] = (*this)[i];
	for (int i = 0; i < b.mSize; i++)
		(*n)[mSize + i] = b[i];
	return n;
}
//-------------------------------------------------------
void List::toString(ostream& out) const
{
	out << "[";
	for (int i = 0; i < mSize; i++)
	{
		if (i > 0)
			out << ",";
		out << mValues[i];
	}
	out << "]";
}
//-------------------------------------------------------