#include <stdio.h>
#include <fstream>
#include <string>
#include <sstream>
#include "list_lexer.h"
#include "list_parser.h"
#include "my_except.h"

void usage(const char *name) {

	fprintf(stderr, 
"\nusage : %s <file>\n",
	name);

}

void test_parser(const char *s) {
	ListLexer lexer(s);
	ListParser parser(&lexer);
	parser.Parse();
}

void test_lexer(const char *s) {

	ListLexer lexer(s);

	try {
		Token token = lexer.GetNextToken();
		while (token.type != TOKEN_EOF && token.type != TOKEN_INVALID) {
			printf("%s  %s\n", lexer.GetTokenName(token.type), token.name.c_str());
			token = lexer.GetNextToken();
		}

	} catch (const InvalidCharException &e) {
		printf("invalid token found %s\n", e.what());
	}

}


int main(int argc, char *argv[]) {

	if (argc < 2) {
		usage(argv[0]);
		exit(-1);
	}
	
	std::ifstream in(argv[1]);
	std::stringstream ss;

	if (!in.is_open()) {
		printf("file open failed!\n");
		usage(argv[0]);
		exit(-1);
	}

	ss << in.rdbuf();
	std::string s = ss.str();

//	test_lexer(s.c_str());
	test_parser(s.c_str());
	
	return 0;
}
