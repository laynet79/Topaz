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
	enum Kind { GLOBAL, CLASS, METHOD, MEMBER, STATIC, INSTANCE, PARAM, LOCAL, TEMP, CONSTANT, NUMBER, BOOL, STRING };
	enum Access { PUBLIC, PROTECTED };

	Symbol(Symbol* parent, const string& name, Kind kind, const string& id, Access access)
	{
		this->parent = parent;
		this->name = name;
		this->kind = kind;
		this->id = id;
		this->access = access;
		this->address = 0;
	}
	virtual ~Symbol()
	{
		for (auto p : mMap)
			delete p.second;
	}

	Symbol* add(const string& name, Kind kind)
	{
		if (kind > CONSTANT && parent != nullptr)
			return parent->add(name, kind);

		Symbol* s = nullptr;
		try
		{
			s = lookup(name);
			if (s->kind == CONSTANT)
				return s;
			throw "redefinition: " + name;
		}
		catch (...) {}
		s = create(name, kind);
		mMap[name] = s;
		return s;
	}

	virtual Symbol* create(const string& name, Kind kind) { return nullptr; }

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

	Value*& value(VirtualMachine& vm);

	Symbol* parent;
	map<string, Symbol*> mMap;
	string name;
	string id;
	Kind   kind;
	Access access;
	int    address;

	bool operator == (const Symbol& s) { return name == s.name; }

	void toString(ostream& out)
	{
		static const char* kindNames[] = { "class", "method", "static", "instance", "param", "local", "temp", "constant" };
		static const char* accessNames[] = { "public", "protected" };
		out << " id=" << id << " kind=" << kindNames[kind] << " address=" << address 
			<< " access=" << accessNames[access] << endl;
	}
};
//-------------------------------------------------------
// this class represents a constant
//-------------------------------------------------------
class Constant : public Symbol
{
public:
	Constant(const string& name, Value* value)
		: Symbol(nullptr, name, CONSTANT, nextId(), PUBLIC), mValue(value) {}
	Value*& value() { return mValue; }

	static void resetId() { sNextId = 100; }
protected:
	Value*  mValue;

	static int sNextId;
	static string nextId()
	{
		string s = "K" + to_string(sNextId++);
		return s;
	}
};
//-------------------------------------------------------
// this class represents a variable
//-------------------------------------------------------
class Variable : public Symbol
{
public:
	Variable(Symbol* parent, const string& name, Kind kind)
		: Symbol(parent, name, getKind(name, kind), nextId(name, kind), name[0] == '_' ? PROTECTED : PUBLIC),
		mValue(Null::value()) {}

	Value*& value() { return mValue; }

	static void resetId() { sNextClassId = sNextInstId = sNextParamId = sNextLocalId = sNextTempId = 100; }

	//bool operator == (const Variable& b) { return name == b.name; }

protected:
	static Kind getKind(const string& name, Kind kind)
	{
		if (kind == MEMBER)
			return (isupper(name[0]) || (name[0] == '_' && name.size() > 1 && isupper(name[1]))) ? STATIC : INSTANCE;
		return kind;
	}

	Value*  mValue;

	static int sNextClassId;
	static int sNextInstId;
	static int sNextParamId;
	static int sNextLocalId;
	static int sNextTempId;
	static string nextId(const string& name, Kind kind)
	{
		string s;
		switch (kind)
		{
		case MEMBER:
		{
			if (getKind(name, kind) == STATIC)
				s = "S" + to_string(sNextClassId++);
			else
				s = "I" + to_string(sNextInstId++);
			break;
		}
		case PARAM:
			s = "P" + to_string(sNextParamId++);
			break;
		case LOCAL:
			s = "L" + to_string(sNextLocalId++);
			break;
		case TEMP:
			s = "T" + to_string(sNextTempId++);
			break;
		default:
			break;
		}
		return s;
	}
};
//-------------------------------------------------------
