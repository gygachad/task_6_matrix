#pragma once

template<typename T, size_t matrix_size, T defaultValue>
class matrix
{
    typedef std::conditional_t<matrix_size == 1, T, matrix<T, matrix_size - 1, defaultValue>> mT;
    std::map<int, mT> m_matrixMap;

    int m_lazy_key;

public:

    mT m_lazyMatrix;
  
    matrix() { reset_default_value(); }

    void reset_default_value()
    {
        if constexpr (matrix_size == 1)
            m_lazyMatrix = defaultValue;
        else
            m_lazyMatrix = mT();        
    }

    bool check_default_value()
    {
        if constexpr (matrix_size == 1)
            return m_matrixMap[m_lazy_key] == defaultValue;
        else
            return m_matrixMap[m_lazy_key].size() == 0;
    }

    bool update_lazy_matrix()
    {
        bool status = false;

        if constexpr (matrix_size == 1)
            status = (m_lazyMatrix != defaultValue);
        else
            status = m_lazyMatrix.update_lazy_matrix();

        if (status)
        {
            m_matrixMap[m_lazy_key] = m_lazyMatrix;
            reset_default_value();
        }
        else
        {
            if (m_matrixMap.contains(m_lazy_key))
            {
                if (check_default_value())
                {
                    m_matrixMap.erase(m_lazy_key);
                }
            }
        }

        return status;
    }

    mT& operator[](int key)
    {
        update_lazy_matrix();
        m_lazy_key = key;

        if (m_matrixMap.contains(key))
        {
            return m_matrixMap[key];
        }

        return m_lazyMatrix;
    }

    size_t size()
    {
        update_lazy_matrix();

        size_t size = 0;

        if constexpr (matrix_size == 1)
        {
            size = m_matrixMap.size();
        }
        else
        {
            int key = 0;
            mT child;

            for (auto c : m_matrixMap)
            {
                std::tie(key, child) = c;
                size += child.size();
            }
        }

        return size;
    }

    auto begin()
    {
        update_lazy_matrix();
        return matrix_iterator<T, defaultValue, matrix_size>(m_matrixMap.begin(), m_matrixMap.end());
    }
    
    auto end()
    {
        return matrix_iterator<T, defaultValue, matrix_size>(m_matrixMap.end(), m_matrixMap.end());
    }
};

template<typename T, T defaultValue, size_t matrix_size>
struct matrix_iterator
{
    typedef std::conditional_t<matrix_size == 1, T, matrix<T, matrix_size - 1, defaultValue>> mT;
    std::map<int, mT> m_matrixMap;

    std::map<int, mT>::iterator m_it_begin;
    std::map<int, mT>::iterator m_it_end;

    using mdeepT = matrix_iterator<T, defaultValue, matrix_size - 1>;

    mdeepT m_deepit_begin = mT().begin();
    mdeepT m_deepit_end = mT().end();

    matrix_iterator() {}

    //For end iterator
    matrix_iterator(std::map<int, mT>::iterator ptr_begin, std::map<int, mT>::iterator ptr_end)
    {
        m_it_begin = ptr_begin;
        m_it_end = ptr_end;

        if (ptr_begin != ptr_end)
        {
            m_deepit_begin = ptr_begin->second.begin();
            m_deepit_end = ptr_begin->second.end();
        }
    }

    friend bool operator!= (const matrix_iterator& a, const matrix_iterator& b) { return a.m_it_begin != b.m_it_begin; }
    friend bool operator== (const matrix_iterator& a, const matrix_iterator& b) { return a.m_it_begin == b.m_it_begin; }

    matrix_iterator* operator->()
    {
        return this;
    }

    matrix_iterator& operator++()
    {
        m_deepit_begin.operator++();

        if (m_deepit_begin == m_deepit_end)
        {
            m_it_begin++;
            if (m_it_begin != m_it_end)
            {
                m_deepit_begin = m_it_begin->second.begin();
                m_deepit_end = m_it_begin->second.end();
            }
        }
        
        return *this;
    }

    auto operator*()
    {
        auto t1 = std::tuple_cat(std::make_tuple(m_it_begin->first), *m_deepit_begin);
        return t1;
    }
};

template<typename T, T defaultValue>
struct matrix_iterator<T, defaultValue, 1>
{
    std::map<int, T>::iterator m_it_begin;
    std::map<int, T>::iterator m_it_end;

    matrix_iterator() {}

    matrix_iterator(std::map<int, T>::iterator ptr_begin, std::map<int, T>::iterator ptr_end) { m_it_begin = ptr_begin; m_it_end = ptr_end; }

    matrix_iterator* operator->() { return this; }

    friend bool operator!= (const matrix_iterator& a, const matrix_iterator& b) { return a.m_it_begin != b.m_it_begin; }
    friend bool operator== (const matrix_iterator& a, const matrix_iterator& b) { return a.m_it_begin == b.m_it_begin; }

    matrix_iterator& operator++() { m_it_begin++; return *this; }

    auto operator*() { return std::tuple_cat(*m_it_begin); }
};