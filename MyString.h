#ifndef MYSTRING_H
#define MYSTRING_H


class MyString
{
    public:
        MyString(char* p_str, int p_length);
        virtual ~MyString();

        char* phrase;
        int length;
    protected:

    private:
};

#endif // MYSTRING_H
