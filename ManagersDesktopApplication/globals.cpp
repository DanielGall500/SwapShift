#include "globals.h"

std::string qStr_to_stdStr(QString qs)
{
    return qs.toUtf8().constData();
}
