#include "jparsers.h"

#include <algorithm>

#include "jobject.h"
#include "jarray.h"
#include "jnull.h"
#include "jboolean.h"
#include "jnumber.h"
#include "jstring.h"

#include <stdio.h>

namespace jparsers
{

bool is_end_of_stream(std::istream &stream);
char read_to(std::istream &stream, std::vector<char> c, bool exclude = false);
char read_to(std::istream &stream, char c, bool exclude = false);
std::string read_string(std::istream &stream);
void read_name_value_delimiter(std::istream &stream);
jvalue *read_value(std::istream &stream);
char read_next_for_object(std::istream &stream);
char read_next_for_array(std::istream &stream);
std::string expecting(std::vector<char> v);
bool read_true(std::istream &stream);
bool read_false(std::istream &stream);
jnull *read_null(std::istream &stream);
long read_number(std::istream &stream);

bool is_end_of_stream(std::istream &stream)
{
    return stream.peek() == EOF;
}

std::string expecting(std::vector<char> v)
{
    v.push_back(0);
    return v.data();
}

char read_to(std::istream &stream, std::vector<char> c, bool exclude)
{
    while (!is_end_of_stream(stream))
    {
        const char ch = exclude ? stream.peek() : stream.get();
        if (ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t')
        {
            if (exclude)
                stream.get();

            continue;
        }

        if (std::find(c.begin(), c.end(), ch) != c.end())
            return ch;
        else
            throw std::runtime_error("Expecting " + expecting(c));
    }

    throw std::runtime_error("Unexpected end");
}

char read_to(std::istream &stream, char c, bool exclude)
{
    std::vector<char> cv;
    cv.push_back(c);
    return read_to(stream, cv, exclude);
}

bool read_true(std::istream &stream)
{
    std::string str;

    for (int i = 0; i < 4; ++i)
    {
        if (is_end_of_stream(stream))
            throw std::runtime_error("Unexpected end");

        str += stream.get();
    }

    if (str != "true")
        throw std::runtime_error("Expecting true");

    return true;
}

bool read_false(std::istream &stream)
{
    std::string str;

    for (int i = 0; i < 5; ++i)
    {
        if (is_end_of_stream(stream))
            throw std::runtime_error("Unexpected end");

        str += stream.get();
    }

    if (str != "false")
        throw std::runtime_error("Expecting false");

    return false;
}

jnull *read_null(std::istream &stream)
{
    std::string str;

    for (int i = 0; i < 4; ++i)
    {
        if (is_end_of_stream(stream))
            throw std::runtime_error("Unexpected end");

        str += stream.get();
    }

    if (str != "null")
        throw std::runtime_error("Expecting null");

    return new jnull;
}

long read_number(std::istream &stream)
{
    std::string str;
    bool expectingEnd = false;

    while (!is_end_of_stream(stream))
    {
        char d = stream.peek();

        if (d == ' ' || d == '\t' || d == '\n' || d == '\r')
        {
            stream.get();
            expectingEnd = true;
            continue;
        }

        if (d == ',' || d == '}' || d == ']')
            return atol(str.c_str());

        if (!isdigit(d))
            throw std::runtime_error("Expecting digit");

        if (expectingEnd)
            throw std::runtime_error("Expecting end number");

        stream.get();
        str += d;
    }

    throw std::runtime_error("Unexpected end");
}

std::string read_string(std::istream &stream)
{
    read_to(stream, '\"');

    std::string str;
    std::string ustr;
    bool escape = false;

    while (!is_end_of_stream(stream))
    {
        char ch = stream.get();

        if (escape)
        {
            if (ch == '\"')
            {
                str += '\"';
                escape = false;
            }
            else if (ch == '\\')
            {
                str += '\\';
                escape = false;
            }
            else if (ch == 'n')
            {
                str += '\n';
                escape = false;
            }
            else if (ch == 't')
            {
                str += '\t';
                escape = false;
            }
            else if (ch == 'r')
            {
                str += '\r';
                escape = false;
            }
            else if (ch == '/')
            {
                str += '/';
                escape = false;
            }
            else if (ch == 'b')
            {
                str += '\b';
                escape = false;
            }
            else if (isdigit(ch))
            {
                ustr += ch;
                if (ustr.length() == 4)
                {
                    // todo: unicode to str
                    ustr.clear();
                    escape = false;
                }
            }

            continue;
        }

        if (ch == '\\')
        {
            escape = true;
            continue;
        }

        if (ch == '\"')
            return str;

        str += ch;
    }

    throw std::runtime_error("Unexpected end");
}

void read_name_value_delimiter(std::istream &stream)
{
    read_to(stream, ':');
}

jvalue *read_value(std::istream &stream)
{
    // todo: vector as string

    std::vector<char> v;
    v.push_back('\"');
    v.push_back('{');
    v.push_back('[');
    v.push_back('t');
    v.push_back('f');
    v.push_back('n');
    v.push_back('0');
    v.push_back('1');
    v.push_back('2');
    v.push_back('3');
    v.push_back('4');
    v.push_back('5');
    v.push_back('6');
    v.push_back('7');
    v.push_back('8');
    v.push_back('9');

    while (!is_end_of_stream(stream))
    {
        const char ch = read_to(stream, v, true);

        if (ch == '\"')
        {
            std::string str = read_string(stream);
            return new jstring(str);
        }
        else if (ch == '{')
        {
            jobject *object = read_object(stream);
            return object;
        }
        else if (ch == '[')
        {
            jarray *array = read_array(stream);
            return array;
        }
        else if (ch == 't')
        {
            jboolean *boolean = new jboolean(read_true(stream));
            return boolean;
        }
        else if (ch == 'f')
        {
            jboolean *boolean = new jboolean(read_false(stream));
            return boolean;
        }
        else if (ch == 'n')
        {
            jnull *null = read_null(stream);
            return null;
        }
        else if (isdigit(ch))
        {
            jnumber *number = new jnumber(read_number(stream));
            return number;
        }
    }
}

char read_next_for_object(std::istream &stream)
{
    std::vector<char> v;
    v.push_back('}');
    v.push_back(',');
    return read_to(stream, v);
}

char read_next_for_array(std::istream &stream)
{
    std::vector<char> v;
    v.push_back(']');
    v.push_back(',');
    return read_to(stream, v);
}

jobject *read_object(std::istream &stream)
{
    jobject *object = new jobject;

    try
    {
        read_to(stream, '{');

        while (!is_end_of_stream(stream))
        {
            std::string name = read_string(stream);

            read_name_value_delimiter(stream);

            jvalue *value = read_value(stream);

            object->set_value(name, value);

            char next = read_next_for_object(stream);

            if (next == '}')
                return object;
            else if (next == ',')
                continue;
        }

        throw std::runtime_error("Unexpected end");
    }
    catch(const std::runtime_error &e)
    {
        delete object;
        throw e;
    }
}

jarray *read_array(std::istream &stream)
{
    jarray *array = new jarray;

    try {
        read_to(stream, '[');

        while (!is_end_of_stream(stream))
        {
            jvalue *value = read_value(stream);

            array->append_value(value);

            char next = read_next_for_array(stream);

            if (next == ']')
                return array;
            else if (next == ',')
                continue;
        }

        throw std::runtime_error("Unexpected end");
    }
    catch(const std::runtime_error &e)
    {
        delete array;
        throw e;
    }
}

}
