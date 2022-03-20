#pragma once

#include <map>

template<   typename T,
            size_t matrix_size,
            T defaultValue>
class matrix //: public std::map<int, std::conditional_t<matrix_size == 1, T, matrix<T, matrix_size - 1, defaultValue>>>
{
    typedef std::conditional_t<matrix_size == 1, T, matrix<T, matrix_size - 1, defaultValue>> mT;

    //using _Mybase = std::map<int, mT>;

    std::map<int, mT> m_matrixMap;

    int m_lazy_key;

public:
    mT m_lazyMatrix;

    matrix() { reset_lazy_value(m_lazyMatrix); }

    void reset_lazy_value(T& value) { value = defaultValue; }

    void reset_lazy_value(matrix<T, matrix_size - 1, defaultValue>& matrix) { matrix = mT(); }
  
    bool update_lazy_matrix(T& value)
    {
        bool status = false;

        if (value != defaultValue)
        {
            m_matrixMap[m_lazy_key] = value;
            reset_lazy_value(value);
            status = true;
        }
        else
        {
            if (m_matrixMap.contains(m_lazy_key))
            {
                if (m_matrixMap[m_lazy_key] == defaultValue)
                    m_matrixMap.erase(m_lazy_key);
            }
        }

        return status;
    }
   
    bool update_lazy_matrix(matrix<T, matrix_size - 1, defaultValue>& matrix)
    {
        bool status = false;

        //make cycle for???
        if (matrix.update_lazy_matrix(matrix.m_lazyMatrix))
        {
            m_matrixMap[m_lazy_key] = matrix;
            reset_lazy_value(matrix);
            status = true;
        }
        else
        {
            if (m_matrixMap.contains(m_lazy_key))
            {
                if (m_matrixMap[m_lazy_key].child_size() == 0)
                {
                    m_matrixMap.erase(m_lazy_key);
                }
            }
        }

        return status;
    }

    mT& operator[](int key)
    {
        update_lazy_matrix(m_lazyMatrix);
        m_lazy_key = key;

        if (m_matrixMap.contains(key))
        {
            return m_matrixMap[key];
        }

        return m_lazyMatrix;
    }

    //For type matrix
    size_t child_size()
    {
        return m_matrixMap.size();
    }

    //For type T
    /*
    size_t child_size()
    {

    }
    */
    size_t size()
    {
        update_lazy_matrix(m_lazyMatrix);

        int key = 0;
        mT child;
        size_t size = 0;

        for (auto c : m_matrixMap)
        {
            std::tie(key, child) = c;

            size += child.child_size();
        }

        return size;
    }
};