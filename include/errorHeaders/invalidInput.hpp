#ifndef __INVALID_INPUT_HPP__
#define __INVALID_INPUT_HPP__

#include "exception"

using std::exception;

/*
Custom exception class for invalid inputs
*/

class invalid_input: public exception 
{
    const char * error;
public:
    invalid_input(const char * e): error(e) {}
    virtual ~invalid_input() throw() {}
    virtual const char * what() const throw() {return error;}
};

#endif
