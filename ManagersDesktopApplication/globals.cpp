#include "globals.h"

std::string qStr_to_stdStr(QString qs)
{
    //Converts a QString to an STD String
    return qs.toUtf8().constData();
}
