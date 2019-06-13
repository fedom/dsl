#ifndef __MY_EXCEPT_H__
#define __MY_EXCEPT_H__
#include <string>
#include <cstdlib>

class MyBaseException {
public:
	MyBaseException(const char *s, const char *file, int line) : s_(s), file_(file), line_(line), exception_name_("MyBaseException") {}
	virtual const char *what() const throw () {
		static std::string s;
		s.clear();
		s = exception_name_ + ":" + s_ + ", " + file_ + ", " + std::to_string(line_);
		return s.c_str();
	}

protected:
	std::string s_;
	std::string file_;
	int line_;
	std::string exception_name_;
};


class InvalidCharException : public MyBaseException { 
public:
	InvalidCharException(const char *s, const char *file, int line) : MyBaseException(s, file, line){ exception_name_ = "InvalidCharException"; }
};

class ParserUnwantedTokenException : public MyBaseException { 
public:
	ParserUnwantedTokenException(const char *s, const char *file, int line) 
			: MyBaseException(s, file, line) { exception_name_ = "ParserUnwantedTokenException";}
};


class LookAheadStepBeyondCapacity : public MyBaseException { 
public:
	LookAheadStepBeyondCapacity(const char *s, const char *file, int line) 
			: MyBaseException(s, file, line) { exception_name_ = "LookAheadStepBeyondCapacity";}
};


#endif//__MY_EXCEPT_H__
