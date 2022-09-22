#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <QString>

// basic classs of exceptions
class Error
{
protected:
    QString m_msg;
public:
    Error(const QString& msg);
    QString data();
};

class ErrorOpeningDataFile: public Error
{
public:
    ErrorOpeningDataFile(const QString &filename);
};

class ErrorSavingDataFile: public Error
{
public:
    ErrorSavingDataFile(const QString &filename);
};

class ErrorSavingMediaData: public Error
{
public:
    ErrorSavingMediaData(const QString &filename);
};

class ErrorReadingMediaData: public Error
{
public:
    ErrorReadingMediaData(const QString &filename);
};

#endif // EXCEPTIONS_H
