#ifndef MYSORT_H
#define MYSORT_H
#include <QList>

template <class T>
void mySort(typename QList<T>::iterator first, typename QList<T>::iterator last);

#include "mySort.hpp"
#endif // MYSORT_H
