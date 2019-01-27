#include "SymbolTable.h"
#include "Class.h"
#include "Method.h"

//-------------------------------------------------------
SymbolTable::SymbolTable(vector<Constant*>& constants)
	: Symbol(nullptr, "global", STRING, "G100", PUBLIC), mConstants(constants)
{
	// reset symbol ID numbering
	Class::resetId();
	Method::resetId();
	Constant::resetId();
	Variable::resetId();

	mCurScope = this;

	// add default constants
	addSymbol("0", NUMBER);
	addSymbol("1", NUMBER);
	addSymbol("true", BOOL);
	addSymbol("false", BOOL);
	addSymbol("null", NUMBER);
}
//-------------------------------------------------------
Symbol* SymbolTable::create(const string& name, Kind kind)
{
	switch (kind)
	{
	case CLASS:
	{
		Class* s = new Class(this, name);
		mClasses[name] = s;
		return s;
	}
	default:
	{
		try
		{
			Symbol* s = lookup(name, false);
			if (s->kind == kind)
				return s;
		}
		catch (...) {}
		switch (kind)
		{
		case NUMBER:
		{
			Value* value = Value::number(atof(name.c_str()));
			Constant* s = new Constant(name, value);
			s->address = (int)mConstants.size();
			mConstants.push_back(s);
			return s;
		}
		case BOOL:
		{
			Value* value = Value::boolean((name == "true") ? true : false);
			Constant* s = new Constant(name, value);
			s->address = (int)mConstants.size();
			mConstants.push_back(s);
			return s;
		}
		case STRING:
		{
			Value* value = Value::str(name);
			Constant* s = new Constant(name, value);
			s->address = (int)mConstants.size();
			mConstants.push_back(s);
			return s;
		}
		default:
			return nullptr;
		}

		break;
	}
	}
}
//-------------------------------------------------------
Class* SymbolTable::addClass(const string& name)
{
	return (Class*)add(name, Symbol::Kind::CLASS);
}
void SymbolTable::removeClass(const string& name)
{
	try
	{
		Class* c = mClasses.at(name);
		delete c;
		mClasses.erase(name);
	}
	catch (...) {}
}
