#pragma once

template<   typename T,
            size_t matrix_size,
            T defaultValue>
class matrix
{
    typedef matrix<T, matrix_size - 1, defaultValue> mT;

    std::map<int, mT> m_matrixMap;

    int m_lazy_key;

public:
    mT m_lazyMatrix = mT();
  
    bool update_lazy_matrix()
    {
        bool status = false;

        if (m_lazyMatrix.update_lazy_matrix())
        {
            m_matrixMap[m_lazy_key] = m_lazyMatrix;
            m_lazyMatrix = mT();
            status = true;
        }
        else
        {
            if (m_matrixMap.contains(m_lazy_key))
            {
                if (m_matrixMap[m_lazy_key].size() == 0)
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

        int key = 0;
        mT child;
        size_t size = 0;

        for (auto c : m_matrixMap)
        {
            std::tie(key, child) = c;

            size += child.size();
        }

        return size;
    }
};

template<   typename T,
            T defaultValue>
class matrix<T, 1, defaultValue>
{
    std::map<int, T> m_matrixMap;

    int m_lazy_key;

public:
    T m_lazyMatrix = defaultValue;

    bool update_lazy_matrix()
    {
        bool status = false;

        if (m_lazyMatrix != defaultValue)
        {
            m_matrixMap[m_lazy_key] = m_lazyMatrix;
            m_lazyMatrix = defaultValue;
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

    T& operator[](int key)
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

        return m_matrixMap.size();
    }
};