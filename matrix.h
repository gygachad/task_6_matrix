#pragma once

template<   typename T,
            size_t matrix_size,
            T defaultValue>
class matrix
{
    typedef std::conditional_t< matrix_size==1, T, matrix<T, matrix_size - 1, defaultValue>> mT;

    std::map<int, mT> m_matrixMap;

    int m_lazy_key;

public:
    mT m_lazyMatrix;

    matrix() { reset_lazy_matrix(); }

    void reset_lazy_matrix()
    {
        if constexpr (matrix_size != 1)
            m_lazyMatrix = mT();
        else
            m_lazyMatrix = defaultValue;
    }

    bool check_default_value(int key)
    {
        if constexpr (matrix_size != 1)
            return m_matrixMap[key].size() == 0;
        else
            return m_matrixMap[key] == defaultValue;
    }

    bool update_lazy_matrix()
    {
        bool status = false;

        if constexpr (matrix_size != 1)
            status = m_lazyMatrix.update_lazy_matrix();
        else
            status = (m_lazyMatrix != defaultValue);

        if (status)
        {
            m_matrixMap[m_lazy_key] = m_lazyMatrix;
            reset_lazy_matrix();
        }
        else
        {
            if (m_matrixMap.contains(m_lazy_key))
            {
                if (check_default_value(m_lazy_key))
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
    
    /*
    std::tuple<int, mT>& operator=(const std::pair<const int, matrix<T, 1, -1>>& rhs)
    {
        return *this;
    }
    */

    size_t size()
    {
        update_lazy_matrix();

        int key = 0;
        mT child;
        size_t size = 0;

        if constexpr (matrix_size != 1)
        {
            for (auto c : m_matrixMap)
            {
                std::tie(key, child) = c;
                size += child.size();
            }
        }
        else
        {
            size = m_matrixMap.size();
        }

        return size;
    }

    auto begin()
    {
        return m_matrixMap.begin();
    }

    auto end()
    {
        return m_matrixMap.end();
    }
};