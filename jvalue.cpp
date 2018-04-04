#include "jvalue.h"

#include "jnull.h"
#include "jboolean.h"
#include "jnumber.h"
#include "jstring.h"
#include "jobject.h"
#include "jarray.h"

bool jvalue::is_null() const
{
    return dynamic_cast<const jnull *>(this) != 0;
}

long jvalue::as_number() const
{
    return static_cast<const jnumber *>(this)->value();
}

bool jvalue::as_boolean() const
{
    return static_cast<const jboolean *>(this)->value();
}

std::string jvalue::as_string() const
{
    return static_cast<const jstring *>(this)->value();
}

const jobject *jvalue::as_object() const
{
    return static_cast<const jobject *>(this);
}

const jarray *jvalue::as_array() const
{
    return static_cast<const jarray *>(this);
}
