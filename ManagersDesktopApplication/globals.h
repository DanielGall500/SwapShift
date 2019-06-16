#ifndef GLOBALS_H
#define GLOBALS_H

#include <QString>

extern const QString ssTitleStr;


/* Our inputs are read as QStrings, however we need to
*  input STD strings to many of our classes.
*
*  To solve this, 'toUtf8()' and 'constData()'
*  functions are called. */

extern std::string qStr_to_stdStr(QString qs);

#endif // GLOBALS_H
