#include <iostream>
#include <cassert>
#include "matrix.h"
//-----------------------------------------------------------------------------
int main()
{
    //����������� ����� �� �������
    {
        // ����������� ������� int ��������� ���������� -1
        Matrix<int, -1> matrix;
        assert(matrix.size() == 0); // ��� ������ ��������
        auto a = matrix[0][0];
        assert(a == -1);
        assert(matrix.size() == 0);
        matrix[100][100] = 314;
        assert(matrix[100][100] == 314);
        assert(matrix.size() == 1);

        // ��������� ���� ������
        // 100100314
        for (const auto& it : matrix)
        {
            size_t row;
            size_t column;
            int value;
            std::tie(row, column, value) = it;
            std::cout << row << column << value << std::endl;
        }
    }

    //�������� �������
    {
        Matrix<int, 0> m;

        //��������� ���������
        for (int i = 0; i <= 9; ++i)
        {
            m[i][i] = i;
        }

        for (int i = 9; i >= 0; --i)
        {
            m[i][9 - i] = i;
        }

        //����������� �������
        for (int i = 1; i <= 9; ++i)
        {
            for (int j = 1; j <= 9; ++j)
            {
                std::cout << m[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;

        //������� ������
        std::cout << "Non-default cells: " << m.size() << std::endl;
    }

    return EXIT_SUCCESS;
}
//-----------------------------------------------------------------------------
