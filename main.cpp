#include <sstream>
#include <iostream>

#include "jparsers.h"
#include "jobject.h"

//-----------------------------------------------------------------



int main()
{
    std::string str = "  {\"name\" : \"\\\"va\\nl\\tue\", \"name1\" : {\"inner\" : \"value1\"}, \"arr\" : [\"a\", null, \"b\", true, 1024, {\"as\" : false}]}  ";
    std::stringstream stream(str);

    try
    {
        jobject *object = jparsers::read_object(stream);
        std::cout << object->value("name")->as_string() << std::endl;
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
