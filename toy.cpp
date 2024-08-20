#include <algorithm>
#include <cctype>
#include <cstdio>
#include <ios>
#include <iostream>
#include <memory>
#include <string>
#include <vector>




// Lexer
enum Token {
	tok_eof = -1,

	//comands
	tok_def = -2,
	tok_extern= -3,

	// primary
	tok_identifier = -4,
	tok_number = -5,
};


static std::string IdentifierStr; // será preenchido se tok_identifier
static double NumVal; // será preenchido se tok_number


// essa função retorna o proximo token do input
static int getToken() {
	static int LastChar = ' ';

	// esse loop pula/ignora todo espaço branco
	while(isspace(LastChar)) {
		LastChar = getchar();
	}

	if (isalpha(LastChar)) { // identificadores: [a-zA-Z][a-zA-Z0-9]*
		IdentifierStr = LastChar;
		while (isalnum((LastChar = getchar()))) {
			IdentifierStr += LastChar;
			if (IdentifierStr == "def") {
				return tok_def;
			}

			if (IdentifierStr == "extern") {
				return tok_extern;
			}
			return tok_identifier;
		}
	}

	if (isdigit(LastChar) || LastChar == '.') { // number: [0-9.]+
		std::string NumStr;
		do {
			NumStr += LastChar;
			LastChar = getchar();

		} while (isdigit(LastChar) || LastChar == '.');
		NumVal = strtod(NumStr.c_str(), 0);
		return tok_number;
	}

	if (LastChar == '#') {
		// comment até o fim da lina
		do {
			LastChar = getchar();
		} while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');

		if (LastChar != EOF) {
			return getToken();
		}
	}

	if (LastChar == EOF) {
		return tok_eof;
	}

	int ThisChar = LastChar;
	LastChar = getchar();
	return ThisChar;
}


class ExprAST {
public:
	virtual ~ExprAST() = default;
};

// expression class para referenciar um numerico literal, tipo 1.0
class NumberExprAST : ExprAST {
	double Val;

public:
	NumberExprAST(double Val) : Val(Val) {}
};

// expression class para referenciar uma variavel, tipo "a"
class VariableExprAST : public ExprAST {
	std::string Name;

public:
	VariableExprAST(const std::string &Name) : Name(Name) {}
};


// expression class para referenciar um operatory binary
class BinaryExprAST : public ExprAST {
	char Op;
	std::unique_ptr<ExprAST> LHS, RHS;

public:
	BinaryExprAST(char Op, std::unique_ptr<ExprAST> LHS,
	       std::unique_ptr<ExprAST> RHS) : Op(Op), LHS(std::move(LHS)), RHS(std::move(RHS)) {}
};


// expression class para chamada de funções
class CallExprAST : public ExprAST {
	std::string Callee;
	std::vector<std::unique_ptr<ExprAST>> Args;

public:
	CallExprAST(const std::string &Callee,
	     std::vector<std::unique_ptr<ExprAST>> Args
	     ) : Callee(Callee),
		Args(std::move(Args)
       ) {}
};


class PrototypeAST {
	std::string Name;
	std::vector<std::string> Args;
public:
	PrototypeAST(const std::string &Name, std::vector<std::string> Args) : Name(Name), Args(std::move(Args)) {}
	const std::string &getName() const { return Name; }
};


// a definição da função por si só
class FunctionAST {
	std::unique_ptr<PrototypeAST> Proto;
	std::unique_ptr<ExprAST> Body;
public:
	FunctionAST(
	std::unique_ptr<PrototypeAST> Proto,
	std::unique_ptr<ExprAST> Body
	) : Proto(std::move(Proto)), Body(std::move(Body)) {}
};
