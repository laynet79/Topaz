#include "TopazImp.h"
#include "Tokenizer.h"
#include <fstream>

//-------------------------------------------------------
TopazImp::TopazImp()
{
}
//-------------------------------------------------------
TopazImp::~TopazImp()
{
}
//-------------------------------------------------------
void TopazImp::run()
{
	ifstream f("test.txt");
	string input = "";
	getline(f, input, '\0');
	Tokenizer tok(input);
	tok.begin();
	Token* t = tok.getToken();
	while (t->type() != Token::ENDOF)
	{
		cout << *t << endl;
		tok.nextToken();
		t = tok.getToken();
	}
	cout << *t << endl;
}
//-------------------------------------------------------
bool TopazImp::compile(const string & input)
{
	return true;
}
//-------------------------------------------------------
