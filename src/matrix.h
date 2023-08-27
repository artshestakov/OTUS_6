#pragma once
#ifndef _MATRIX_H_INCLUDED
#define _MATRIX_H_INCLUDED
//-----------------------------------------------------------------------------
#include <vector>
//-----------------------------------------------------------------------------
template <typename T, typename T default_value = T()>
class Matrix
{
private:
    struct Row
    {
    private:
        struct Column
        {
            Column(unsigned int column_number)
                : ColumnNumber(column_number),
                Value(default_value)
            {

            }

            void operator=(T value)
            {
                Value = value;
            }
            
            unsigned int ColumnNumber;
            T Value;
        };

    public:
        Row(unsigned int row_number)
            : RowNumber(row_number)
        {

        }

        Column& operator[](unsigned int column)
        {
            for (Column& c : m_Columns)
            {
                if (c.ColumnNumber == column)
                {
                    return c;
                }
            }
            return m_Columns.emplace_back(Column(column));
        }

        unsigned int RowNumber;

    private:
        std::vector<Column> m_Columns;
    };

public:
    Matrix()
    {

    }

    ~Matrix()
    {

    }

    //! Получить размер матрицы
    //! \return возвращает размер матрицы
    size_t size() const
    {
        return m_Rows.size();
    }

    //! Проверить матрицу на пустоту
    //! \return возвращает true если матрица пустая, иначе - false
    bool empty() const
    {
        return size() == 0;
    }

    Row& operator[](unsigned int row)
    {
        for (Row& r : m_Rows)
        {
            if (r.RowNumber == row)
            {
                return r;
            }
        }
        return m_Rows.emplace_back(Row(row));
    }

private:
    std::vector<Row> m_Rows;
};
//-----------------------------------------------------------------------------
#endif
