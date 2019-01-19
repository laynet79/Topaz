#pragma once
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <iomanip>
using namespace std;

#include "Value.h"
class VirtualMachine;

//-------------------------------------------------------
// this class represents symbol 
//-------------------------------------------------------
class Symbol
{
public:
	enum Kind { GLOBAL, CLASS, METHOD, STATIC, INSTANCE, PARAM, LOCAL, TEMP, CONSTANT, NUMBER, BOOL, STRING };
	enum Access { PUBLIC, PROTECTED };

	Symbol(Symbol* parent, const string& name, Kind kind, const string& id, Access access=PROTECTED, bool isStatic=false)
	{
		this->parent = parent;
		this->name = name;
		this->kind = kind;
		this->id = id;
		this->access = access;
		this->address = 0;
		this->isStatic = isStatic;
	}
	virtual ~Symbol()
	{
		for (auto p : mMap)
			delete p.second;
	}

	Symbol* add(const string& name, Kind kind, Access access = PROTECTED, bool isStatic = false)
	{
		if (kind > CONSTANT && parent != nullptr)
			return parent->add(name, kind, access, isStatic);

		Symbol* s = nullptr;
		try
		{
			s = lookup(name);
			if (s->kind == CONSTANT)
				return s;
			throw "redefinition: " + name;
		}
		catch (...) {}
		s = create(name, kind, access, isStatic);
		mMap[name] = s;
		return s;
	}

	virtual Symbol* create(const string& name, Kind kind, Access access = PROTECTED, bool isStatic = false) { return nullptr; }

	Symbol* lookup(const string& name, bool recursive = true)
	{
		Symbol* s = nullptr;
		try
		{
			return mMap.at(name);
		}
		catch (...) {}
		if (parent && recursive)
			return parent->lookup(name); // go to next level of scope
		throw "undefined symbol: " + name;
	}

	Value& value(VirtualMachine& vm);

	Symbol* parent;
	map<string, Symbol*> mMap;
	string name;
	string id;
	Kind   kind;
	Access access;
	int    address;
	bool   isStatic;

	void toString(ostream& out)
	{
		static const char* kindNames[] = { "class", "method", "static", "instance", "param", "local", "temp", "constant" };
		static const char* accessNames[] = { "public", "protected" };
		out << " id=" << id << " kind=" << kindNames[kind]
			<< " address=" << address << " access=" << accessNames[access] << endl;
	}
};
//-------------------------------------------------------
// this class represents a constant
//-------------------------------------------------------
class Constant : public Symbol
{
public:
	Constant(const string& name, const Value& value)
		: Symbol(nullptr, name, CONSTANT, nextId(), PUBLIC), mValue(value) {}
	Value& value() { return mValue; }
	static string nextId(bool reset = false)
	{
		static int nextId = 100;
		string s = "K" + to_string(nextId++);
		if (reset) nextId = 100;
		return s;
	}
protected:
	Value  mValue;
};
//-------------------------------------------------------
// this class represents a variable
//-------------------------------------------------------
class Variable : public Symbol
{
public:
	Variable(Symbol* parent, const string& name, Kind kind, const string& id, Access access=PROTECTED)
		: Symbol(parent, name, kind, id, access) {}
};
//-------------------------------------------------------
// this class represents a static variable
//-------------------------------------------------------
class ClassVar : public Variable
{
public:
	ClassVar(Symbol* parent, const string& name, Access access)
		: Variable(parent, name, STATIC, nextId(), access) {}
	Value& value() { return mValue; }
	static string nextId(bool reset = false)
	{
		static int nextId = 100;
		string s = "S" + to_string(nextId++);
		if (reset) nextId = 100;
		return s;
	}
protected:
	Value  mValue;
};
//-------------------------------------------------------
// this class represents an instance variable
//-------------------------------------------------------
class InstanceVar : public Variable
{
public:
	InstanceVar(Symbol* parent, const string& name, Access access)
		: Variable(parent, name, INSTANCE, nextId(), access) {}
	static string nextId(bool reset = false)
	{
		static int nextId = 100;
		string s = "I" + to_string(nextId++);
		if (reset) nextId = 100;
		return s;
	}
};
//-------------------------------------------------------
// this class represents a method parameter
//-------------------------------------------------------
class Parameter : public Variable
{
public:
	Parameter(Symbol* parent, const string& name)
		: Variable(parent, name, PARAM, nextId()) {}
	static string nextId(bool reset = false)
	{
		static int nextId = 100;
		string s = "P" + to_string(nextId++);
		if (reset) nextId = 100;
		return s;
	}
};
//-------------------------------------------------------
// this class represents a local variable
//-------------------------------------------------------
class Local : public Variable
{
public:
	Local(Symbol* parent, const string& name)
		: Variable(parent, name, LOCAL, nextId()) {}
	static string nextId(bool reset = false)
	{
		static int nextId = 100;
		string s = "L" + to_string(nextId++);
		if (reset) nextId = 100;
		return s;
	}
};
//-------------------------------------------------------
// this class represents a temporary variable
//-------------------------------------------------------
class Temporary : public Variable
{
public:
	Temporary(Symbol* parent, const string& name)
		: Variable(parent, name, TEMP, nextId()) {}
	static string nextId(bool reset = false)
	{
		static int nextId = 100;
		string s = "T" + to_string(nextId++);
		if (reset) nextId = 100;
		return s;
	}
};
//-------------------------------------------------------
