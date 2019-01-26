#include <fstream>
#include <string>
#include <regex>
using namespace std;
#include "Tokenizer.h"

//-------------------------------------------------------
// Constructor/Destructor
//-------------------------------------------------------
Tokenizer::Tokenizer(const string& input)
{
	mInput = input;
	mCurrent = nullptr;
	mNext = nullptr;
	mLineBuf;
	mLineNum = 0;
	mLexeme = "";
	mLastTokenLine = 0;
}
Tokenizer::~Tokenizer()
{
}

//-------------------------------------------------------
// begin parsing tokens (restart)
//-------------------------------------------------------
void Tokenizer::begin()
{
	mInputStream = stringstream(mInput);
	mCurrent = mNext = nullptr;
	mLineNum = 0;
	mLineBuf = "";
	mLexeme = "";
	mLastLines.clear();
	mLastTokenLine = -1;
	nextToken();
	nextToken();
}
//-------------------------------------------------------
// get pointer to the current token
//-------------------------------------------------------
Token* Tokenizer::getToken()
{
	return mCurrent;
}
//-------------------------------------------------------
// get pointer to the next token
//-------------------------------------------------------
Token* Tokenizer::peekToken()
{
	return mNext;
}
//-------------------------------------------------------
// get all source lines down to current token line number
//-------------------------------------------------------
vector<string> Tokenizer::getLastLines()
{
	// Grab all lines from history buffer, that are associated with
	// already consumed tokens and return them.
	vector<string> lines;
	for (LineRec& r : mLastLines)
	{
		if (r.line >= mLastTokenLine)
			break;
		lines.push_back(r.text);
	}
	for (int i = 0; i < (int)lines.size(); i++)
		mLastLines.pop_front();
	return lines;
}
//-------------------------------------------------------
// consume the current token and generate a new one
//-------------------------------------------------------
void Tokenizer::nextToken()
{
	if (mCurrent)
		mLastTokenLine = mCurrent->line();

	delete mCurrent;
	mCurrent = mNext;

	// make sure that the line buffer has data in it before parsing
	if (mLineBuf == "")
	{
		// keep reading lines until we have a line with something to parse
		while (mLineBuf == "")
		{
			// read the next line from the file.  If that fails,
			// set the next token to EOF and return
			if (!getline(mInputStream, mLineBuf))
			{
				mNext = new Token(Token::ENDOF, mLineNum, "<EOF>");
				return;
			}

			// collect into last lines history buffer
			if (mLineBuf != "")
				mLastLines.push_back(LineRec(mLineNum, mLineBuf));

			// increment the line number and remove leading whitespace
			mLineNum++;
			removeWhiteSpaceAndComments();
		}
	}

	// parse the front of the input line to see what type of token
	// we have.
	if (parseNumber())
	{
		mNext = new Token(Token::NUMBER, mLineNum, mLexeme);
	}
	else if (parseString())
	{
		mLexeme = mLexeme.substr(1, mLexeme.size() - 2);
		mNext = new Token(Token::STRING, mLineNum, mLexeme);
	}
	else if (parseKeyword())
	{
		mNext = new Token(Token::KEYWORD, mLineNum, mLexeme);
	}
	else if (parseID())
	{
		mNext = new Token(Token::ID, mLineNum, mLexeme);
	}
	else if (parseSymbol())
	{
		mNext = new Token(Token::SYMBOL, mLineNum, mLexeme);
	}
	else
	{
		mNext = new Token(Token::UNKNOWN, mLineNum, mLineBuf);
		mLineBuf = ""; // don't know where next token starts so eat whole line
	}
}
//-------------------------------------------------------
// consume white space and comments from front of input line
//-------------------------------------------------------
void Tokenizer::removeWhiteSpaceAndComments()
{
	// first remove white space from front of line
	static regex ws("^(\\s)+"); // white space at front of string
	startsWith(ws, false);

	// now remove comment if it exists
	static regex comment("^//");
	if (startsWith(comment, false))
		mLineBuf = ""; // comment found, consume the rest of the line
}
//-------------------------------------------------------
// attempt to parse an number from the front of the input line
//-------------------------------------------------------
bool Tokenizer::parseNumber()
{
	//regex re("^[0-9]+"); // integer
	static regex re("^\\-?[0-9]+(\\.[0-9]+)?"); // number with optional negative sign
	return startsWith(re);
}
//-------------------------------------------------------
// attempt to parse a character literal from the front of
// the input line
//-------------------------------------------------------
bool Tokenizer::parseString()
{
	static regex re("^\".*\"");
	return startsWith(re);
}
//-------------------------------------------------------
// attempt to parse an ID from the front of the input line
//-------------------------------------------------------
bool Tokenizer::parseID()
{
	static regex re("^[_a-zA-Z][a-zA-Z0-9]*"); // identifier
	return startsWith(re);
}
//-------------------------------------------------------
// attempt to parse a keyword from the front of the input line
//-------------------------------------------------------
bool Tokenizer::parseKeyword()
{
	static regex keywords[]
	{
		regex("^case"), regex("^class"), regex("^else"), regex("^false"), regex("^for"), 
		regex("^if"), regex("^in\\s"), regex("^switch"), regex("^true"), 
		regex("^do"), regex("^this"), regex("^null"), regex("^while"), regex("^return")
	};
	for (regex& re : keywords)
	{
		if (startsWith(re))
			return true;
	}
	return false;
}
//-------------------------------------------------------
// attempt to parse a symbol from the front of the input line
//-------------------------------------------------------
bool Tokenizer::parseSymbol()
{
	static regex symbols[]
	{
		regex("^\\+{2}"), regex("^\\-{2}"), regex("^\\+="), regex("^\\-="), regex("^\\*="), regex("^/="), regex("^\\+"), regex("^\\-"), regex("^\\*"), regex("^/"), regex("^%"), // math
		regex("^<="), regex("^>="), regex("^<"), regex("^>"), regex("^=="), regex("^!="), regex("^!"), // relational
		regex("^&&"), regex("^\\|\\|"), // boolean
		regex("^="), // assignment
		regex("^\\{"), regex("^\\}"), regex("^\\("), regex("^\\)"), regex("^\\["), regex("^\\]"), 
		regex("^\\.{2}<"), regex("^\\.{2}"), regex("^\\,"), regex("^\\;"), regex("^\\:"), regex("^\\."), regex("^\\?"), // punctuation
	};
	for (regex& re : symbols)
	{
		if (startsWith(re))
			return true;
	}
	return false;
}
//-------------------------------------------------------
// checks to see if the input line starts with the token
// specified by the given regular expression.  If so,
// we set the lexeme and remove it from the front of the
// input string.  We also remove whitespace from the front
//-------------------------------------------------------
bool Tokenizer::startsWith(regex& re, bool ws)
{
	smatch match;
	if (regex_search(mLineBuf, match, re))
	{
		if (ws)
			mLexeme = match[0];
		mLineBuf = mLineBuf.substr(match[0].length());
		if (ws)
			removeWhiteSpaceAndComments();
		return true;
	}
	return false;
}
//-------------------------------------------------------
