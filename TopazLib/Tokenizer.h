#pragma 
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <regex>
using namespace std;
#include "Token.h"

//-------------------------------------------------------
// this class implements a tokenizer for the Zoom language
//-------------------------------------------------------
class Tokenizer
{
public:
	Tokenizer(const string& input);
	~Tokenizer();

	void begin();
	Token* getToken();
	Token* peekToken();
	void nextToken();
	vector<string> getLastLines();

private:
	string mInput;
	stringstream mInputStream;
	Token* mCurrent;
	Token* mNext;
	string mLineBuf;
	int mLineNum;
	string mLexeme;

	struct LineRec { int line; string text; LineRec(int line, string text) { this->line = line; this->text = text; } };
	list<LineRec> mLastLines;
	int mLastTokenLine;

	void removeWhiteSpaceAndComments();
	bool parseNumber();
	bool parseString();
	bool parseID();
	bool parsePunctuation();
	bool parseKeyword();
	bool parseSymbol();
	bool startsWith(regex& re, bool ws=true);
};

