#pragma once
//-----------------------------------------------------------------------------
#include <map>
//-----------------------------------------------------------------------------
template <typename T, typename T default_value = T()>
class Matrix
{
private:
    class Storage
    {
    private:
        struct Key
        {
            Key(size_t row, size_t column) : Row(row), Column(column) { }

            bool operator<(const Key& k) const
            {
                return std::tie(Row, Column) < std::tie(k.Row, k.Column);
            }

            size_t Row;
            size_t Column;
        };

    public:
        using MatrixIterator = typename std::map<Key, T>::iterator;
        
        Storage() : m_RowTemp(0), m_ColumnTemp(0) { };
        ~Storage() = default;

        Storage& operator()(size_t row, size_t column)
        {
            m_RowTemp = row;
            m_ColumnTemp = column;
            return *this;
        }

        void operator=(T value)
        {
            m_Map[Key(m_RowTemp, m_ColumnTemp)] = value;
        }

        bool operator==(T value)
        {
            return get() == value;
        }

        operator T()
        {
            return get();
        }

        size_t size() const
        {
            return m_Map.size();
        }

        MatrixIterator begin()
        {
            return m_Map.begin();
        }

        MatrixIterator end()
        {
            return m_Map.end();
        }

    private:
        T get()
        {
            auto it = m_Map.find(Key(m_RowTemp, m_ColumnTemp));
            return it == m_Map.end() ?
                default_value : it->second;
        }

    private:
        size_t m_RowTemp;
        size_t m_ColumnTemp;
        std::map<Key, int> m_Map;
    };

    class Wrapper
    {
    public:
        Wrapper() : m_RowTemp(0) { };
        ~Wrapper() = default;

        Wrapper& operator()(size_t row)
        {
            m_RowTemp = row;
            return *this;
        }

        Storage& operator[](size_t column)
        {
            return m_Storage(m_RowTemp, column);
        }

        size_t size() const
        {
            return m_Storage.size();
        }

        auto begin()
        {
            return m_Storage.begin();
        }

        auto end()
        {
            return m_Storage.end();
        }

    private:
        size_t m_RowTemp;
        Storage m_Storage;
    };

    class Iterator
    {
    public:
        Iterator(typename Storage::MatrixIterator iter)
            : m_Iterator(iter)
        {

        }

        std::tuple<size_t, size_t, T> operator*()
        {
            return std::make_tuple(m_Iterator->first.Row, m_Iterator->first.Column, m_Iterator->second);
        }

        Iterator& operator++()
        {
            ++m_Iterator;
            return *this;
        }

        bool operator==(const Iterator& other)
        {
            return (m_Iterator == other.m_Iterator);
        }

        bool operator!=(const Iterator& other)
        {
            return !(*this == other);
        }

    private:
        typename Storage::MatrixIterator m_Iterator;
    };

public:
    Matrix() = default;
    ~Matrix() = default;

    Wrapper& operator[](size_t row)
    {
        return m_Wrapper(row);
    }

    size_t size() const
    {
        return m_Wrapper.size();
    }

    Iterator begin()
    {
        return Iterator(m_Wrapper.begin());
    }

    Iterator end()
    {
        return Iterator(m_Wrapper.end());
    }

private:
    Wrapper m_Wrapper;
};
//-----------------------------------------------------------------------------
