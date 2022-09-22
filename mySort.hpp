#include <QList>
#include <QVector>

template <class T>
void mySort(typename QList<T>::iterator first, typename QList<T>::iterator last)
{
    typedef  typename QList<T>::iterator iter;
    QVector<iter&> array;

    for(auto elem {first}; elem != last; ++elem){
        array.append(elem);
    }
    for (int k = array.size()/2; k >= 1; k /= 2)
            for (int i = k; i < array.size(); i++)
                for (int j = i; j >= k && *array[j-k] > *array[j]; j -= k)
                {
                    T temp {*array[j]};
                    *array[j] = *array[j-k];
                    *array[j-k] = temp;
                }
}
