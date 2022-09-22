#include "exceptions.h"

Error::Error(const QString& msg)
    :m_msg(msg)
{

}

QString Error::data()
{
    return m_msg;
}


ErrorOpeningDataFile::ErrorOpeningDataFile(const QString &filename)
    :Error("Cannot open datafile: " + filename)
{

}

ErrorSavingDataFile::ErrorSavingDataFile(const QString &filename)
    :Error("Cannot save data to file: " + filename)
{

}

ErrorSavingMediaData::ErrorSavingMediaData(const QString &filename)
    :Error("Cannot open mediafile: " + filename + " to save metadata")
{

}

ErrorReadingMediaData::ErrorReadingMediaData(const QString &filename)
    :Error("Cannot open mediafile: " + filename + " to read metadata")
{

}
