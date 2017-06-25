#include "stdafx.h"
#include "\Users\Covton\Documents\C++\std_lib_facilities.h"
#include <cmath>

const char number = '8';
const char quit = 'q';
const char print = ';';
const std::string prompt = "> ";
const std::string result = "= ";

class Token
{
public:
	char kind;        // what kind of token
	double value;     // for numbers: a value 
	Token(char ch)    // make a Token from a char
		:kind(ch), value(0) { }
	Token(char ch, double val)     // make a Token from a char and a double
		:kind(ch), value(val) { }
};

class Token_stream
{
public:
	Token_stream();   // make a Token_stream that reads from cin
	Token get();      // get a Token (get() is defined elsewhere)
	void putback(Token t);    // put a Token back
	void ignore(char c);
private:
	bool full;        // is there a Token in the buffer?
	Token buffer;     // here is where we keep a Token put back using putback()
};

Token_stream::Token_stream()
	:full(false), buffer(0)    // no Token in buffer
{
}

// The putback() member function puts its argument back into the Token_stream's buffer:
void Token_stream::putback(Token t)
{
	if (full) error("putback() into a full buffer");
	buffer = t;       // copy t to buffer
	full = true;      // buffer is now full
}

Token Token_stream::get()
{
	if (full) {       // do we already have a Token ready?
					  // remove token from buffer
		full = false;
		return buffer;
	}

	char ch;
	cin >> ch;    // note that >> skips whitespace (space, newline, tab, etc.)

	switch (ch) {
	case print:   
	case quit:    
	case '(': case ')': case '+': case '-': case '*': case '/':
		return Token(ch);        // let each character represent itself
	case '.':
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
	{
		cin.putback(ch);         // put digit back into the input stream
		double val;
		cin >> val;              // read a floating-point number
		return Token('8', val);   // let '8' represent "a number"
	}
	default:
		error("Bad token");
	}
}

void Token_stream::ignore(char c)
{
	if (full == true && c == buffer.kind)
	{
		full = false;
		return;
	}
	full = false;
	char ch = 0;
	while (cin >> ch)
	{
		if (ch = c)
		{
			return;
		}
	}
}

Token_stream ts;        // provides get() and putback() 
double expression();    // declaration so that primary() can call expression()
double primary()
{
	Token t = ts.get();
	switch (t.kind) {
	case '(':    // handle '(' expression ')'
	{
		double d = expression();
		t = ts.get();
		if (t.kind != ')') error("')' expected");
		{
			return d;
		}
		break;
	}
	case number:            // we use '8' to represent a number
		return t.value;  // return the number's value
		break;
	case '-':
		return -primary();
		break;
	case '+':
		return primary();
		break;
	default:
		error("primary expected");
	}
}

//------------------------------------------------------------------------------

// deal with *, /, and %
double term()
{
	double left = primary();
	Token t = ts.get();        // get the next token from token stream

	while (true) {
		switch (t.kind)
		{
			case '*':
				left *= primary();
				t = ts.get();
				break;
			case '/':
			{
				double d = primary();
				if (d == 0) error("divide by zero");
				left /= d;
				t = ts.get();
				break;
			}
			case '%':
			{
				double d = primary();
				if (d == 0)
				{
					error("Divide by zero error");
				}
				left = fmod(left, d);
				t = ts.get();
				break;
			}
			default:
				ts.putback(t);     // put t back into the token stream
				return left;
		}
	}
}

//------------------------------------------------------------------------------

// deal with + and -
double expression()
{
	double left = term();      // read and evaluate a Term
	Token t = ts.get();        // get the next token from token stream

	while (true) {
		switch (t.kind) {
		case '+':
			left += term();    // evaluate Term and add
			t = ts.get();
			break;
		case '-':
			left -= term();    // evaluate Term and subtract
			t = ts.get();
			break;
		default:
			ts.putback(t);     // put t back into the token stream
			return left;       // finally: no more + or -: return the answer
		}
	}
}

void cleanUpStream()
{
	ts.ignore(print);
}

void calculate()
{
	while (cin) {
		try
		{
			std::cout << prompt;
			Token t = ts.get();
			while (t.kind == print)
			{
				t = ts.get();
			}
			if (t.kind == quit)
			{
				return;
			}
			ts.putback(t);
			std::cout << result << expression() << '\n';
		}
		catch (exception& e)
		{
			std::cerr << e.what() << '\n';
			cleanUpStream();
		}
	}
}

int main()
{
	try
	{
		calculate();
		keep_window_open();
		return 0;
	}
	catch (exception& e) {
		cerr << "Error: " << e.what() << '\n';
		keep_window_open("~~");
		return 1;
	}
	catch (...) {
		cerr << "Unknown exception!\n";
		keep_window_open("~~");
		return 2;
	}
}
//------------------------------------------------------------------------------
