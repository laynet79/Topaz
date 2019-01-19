#pragma once
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

//-------------------------------------------------------
// this class represents a parse token in the Zoom language
//-------------------------------------------------------
class Token
{
public:
	enum Type { NUMBER, STRING, ID, PUNC, KEYWORD, SYMBOL, ENDOF, UNKNOWN };
	enum Group { GENERAL, MATHOP, RELOP, BOOLOP, ASSIGN, LP, RP, LB, RB, LS, RS };
	enum PuncType { PERIOD, COMMA, SEMI, COLON };

	Token(Type type, int line, string lexeme="", Group group = GENERAL, int value = 0)
	{
		mType = type;
		mLexeme = lexeme;
		mGroup = group;
		mValue = value;
		mLine = line;
	}

	Type type()		const { return mType;   }
	Group group()   const { return mGroup;  }
	string lexeme() const { return mLexeme; }
	int value()		const { return mValue;  }
	int line()      const { return mLine;   }

private:
	Type mType;
	string mLexeme;
	Group mGroup;
	int mLine;
	int mValue;
};
//-------------------------------------------------------
// Token stream output
//-------------------------------------------------------
inline
ostream& operator << (ostream& out, const Token& t)
{
	const char* typeNames[] = { "NUMBER", "STRING", "ID", "PUNCTUATION", "KEYWORD", "SYMBOL", "EOF", "UNKNOWN" };
	out << setw(10) << left << t.lexeme() << setw(15) << left << typeNames[t.type()] << t.line();
	return out;
}
//-------------------------------------------------------

