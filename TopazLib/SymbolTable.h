#pragma once
#include <string>
#include <vector>
using namespace std;
#include "Symbol.h"
class Class;
class Constant;

//-------------------------------------------------------
// this class represents the symbol table for the Topaz language
// compiler to keep track of symbol properties.  The symbol
// table is represented as a hierarchy of symbol types with
// the symbol table itself being the root symbol (SymbolTable
// has a list of constant symbols, and a list of class symbols.
// Each class symbol has a list of class and instance
// variables, and a list of class and instance methods.  Each
// Method has a list of parameters, locals, and temporary
// variables.  Current scope is represented as a pointer
// to a symbol in the symbol table hierarchy.  Each symbol keeps
// a map of child symbols.  To lookup a symbol by name, the current
// scope symbol child list is searched first, and then the
// parent symbol is searched and so forth.  The list of
// classes and constants are shared with the virtual machine
// and is used at run time to lookup constant values, and to
// run methods.
//-------------------------------------------------------
class SymbolTable : public Symbol // the symbol table will represent the global symbol
{
public:
	//---------------------------------------------
	SymbolTable(vector<Constant*> constants, vector<Class*>& classes);

	Symbol* addSymbol(const string& name, Kind kind, Access access = PROTECTED, bool isStatic = false)
	{
		return mCurScope->add(name, kind, access, isStatic);
	}

	Symbol* lookupSymbol(const string& name)
	{
		return mCurScope->lookup(name);
	}

	Symbol* create(const string& name, Kind kind, Access access = PROTECTED, bool isStatic = false) override;

private:
	Symbol* mCurScope = nullptr;
	vector<Constant*>& mConstants;
	vector<Class*>& mClasses;
};
//-------------------------------------------------------