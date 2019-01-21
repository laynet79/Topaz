#include "SymbolTable.h"
#include "Class.h"
#include "Method.h"
#include "Collection.h"

SymbolTable::SymbolTable(vector<Constant*> constants, vector<Class*>& classes)
	: Symbol(nullptr, "global", GLOBAL, "G100"), mConstants(constants), mClasses(classes)
{
	// reset symbol ID numbering
	Class::nextId(true);
	Method::nextId(true);
	Constant::nextId(true);
	ClassVar::nextId(true);
	InstanceVar::nextId(true);
	Parameter::nextId(true);
	Local::nextId(true);
	Temporary::nextId(true);

	// clear out the constants and class lists
	mConstants.clear();
	mClasses.clear();
	mCurScope = this;

	// add default constants
	addSymbol("0", NUMBER, PUBLIC);
	addSymbol("1", NUMBER, PUBLIC);
	addSymbol("true", BOOL, PUBLIC);
	addSymbol("false", BOOL, PUBLIC);
	addSymbol("null", NUMBER, PUBLIC);
}
//-------------------------------------------------------
Symbol* SymbolTable::create(const string& name, Kind kind, Access access, bool isStatic)
{
	switch (kind)
	{
	case NUMBER:
	{
		Value value = atof(name.c_str());
		Constant* s = new Constant(name, value);
		s->address = (int)mConstants.size();
		mConstants.push_back(s);
		return s;
	}
	case BOOL:
	{
		Value value = (name == "true") ? true : false;
		Constant* s = new Constant(name, value);
		s->address = (int)mConstants.size();
		mConstants.push_back(s);
		return s;
	}
	case STRING:
	{
		Value value = new String(name);
		Constant* s = new Constant(name, value);
		s->address = (int)mConstants.size();
		mConstants.push_back(s);
		return s;
	}
	case CLASS:
	{
		Class* s = new Class(this, name);
		s->address = (int)mClasses.size();
		mClasses.push_back(s);
		return s;
	}
	default:
		return nullptr;
	}
}
//-------------------------------------------------------
