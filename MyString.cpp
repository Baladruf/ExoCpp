#include "MyString.h"

MyString::MyString(char* p_str, int p_length)
{
    phrase = p_str;
    length = p_length;
}

MyString::~MyString()
{
    delete phrase;
}
