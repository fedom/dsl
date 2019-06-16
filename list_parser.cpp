#include "list_parser.h"
#include "list_lexer.h"
#include "my_except.h"

ListParser::ListParser(ListLexer *lexer) : Parser(lexer) {
	
}

ListParser::~ListParser() {

}

void ListParser::Parse() {

	try {
		Stat();
	} catch (const ParserUnwantedTokenException &e) {
		printf("Parse token error: %s\n", e.what());
	} catch (const InvalidCharException &e) {
		printf("InvalidCharException error: %s\n", e.what());
	}
}

void ListParser::Stat() {
	if (SpeculateStatAlt1()) {
		List();
		Match(TOKEN_EOF);

	} else if (SpeculateStatAlt2()) {
		Assign();
		Match(TOKEN_EOF);
	
	} else {
		throw UnregcognizeStatPattern("", __FILE__, __LINE__);
	}	
}

bool ListParser::SpeculateStatAlt1() {
	bool success = false;

	MarkBase();

	try {
		List();
		Match(TOKEN_EOF);
		success = true;
	} catch (const ParserUnwantedTokenException &e) {
		success = false;	
	}
	
	RestoreBase();
	return success;
}

bool ListParser::SpeculateStatAlt2() {
	bool success = false;
	MarkBase();

	try {
		List();
		Match(TOKEN_ASSIGN);
		success = true;
	
	} catch (const ParserUnwantedTokenException &e) {
		success = false;
	}

	RestoreBase();
	return success;
}

void ListParser::Assign() {
	List();
	Match(TOKEN_ASSIGN);
	List();
}


void ListParser::_List() {
	if (LT(1) == TOKEN_EOF)
		return;

	Match(TOKEN_LSBRACK);
	Elements();
	Match(TOKEN_RSBRACK);
}

void ListParser::List() {

	if (!IsSpeculating()) {
		_List();
		return;
	}

	int start_pos = CurPos();	
	int end_pos = 0;
	auto iter = list_speculate_cache_.find(start_pos);

	if (iter != list_speculate_cache_.end()) {
		end_pos = iter->second;
	}
	// On failing, throw to notify caller fail
	if (end_pos < 0) {
		throw ParserUnwantedTokenException("cached fail.", __FILE__, __LINE__);
	} else if (end_pos > 0) {
		SetPos(end_pos);	
		printf("cached hit end_pos:%d %s\n", end_pos, lookahead_tokens_[end_pos].name.c_str());
		return;
	}

	// Intercept the inner rule call incase they throw exception on failure, so we can
	// update the list_speculate_cache_.	
	try {
		_List();	
	} catch (const ParserUnwantedTokenException &e) {
		// On failure, we get here.
		list_speculate_cache_[start_pos] = -1;			
		throw;
	}

	list_speculate_cache_[start_pos] = CurPos();	
}

void ListParser::Elements() {
	// empty list
	if (LT(1) == TOKEN_RSBRACK)
		return;

	Element();
	while (LT(1) == TOKEN_COMMA) {
		Match(TOKEN_COMMA);
		Element();	
	}
}

void ListParser::Element() {
	if (LT(1) == TOKEN_NAME && LT(2) == TOKEN_ASSIGN) {
		Match(TOKEN_NAME);
		Match(TOKEN_ASSIGN);
		Match(TOKEN_NAME);
	} else if (LT(1) == TOKEN_NAME) {
		Match(TOKEN_NAME);	
	} else if (LT(1) == TOKEN_NUMBER) {
		Match(TOKEN_NUMBER);	
	} else if (LT(1) == TOKEN_LSBRACK) {
		List();	
	} else {
		throw ParserUnwantedTokenException(LA(1).name.c_str(), __FILE__, __LINE__);
	}

}

