/*
 * @file sparse_matrix_test.cpp 
 * @brief Test the SparseMatrix class. when you want to use the test file to test the SparseMatrix class,
 * the best way is to use the cmd to excute the PhysikaTestDebug.exe
 * @author Liyou Xu
 * 
 * This file is part of Physika, a versatile physics simulation library.
 * Copyright (C) 2013 Physika Group.
 *
 * This Source Code Form is subject to the terms of the GNU General Public License v2.0. 
 * If a copy of the GPL was not distributed with this file, you can obtain one at:
 * http://www.gnu.org/licenses/gpl-2.0.html
 *
 */

#include <iostream>
#include <vector>
#include <ctime>
#include "Physika_Dependency/Eigen/Eigen"
#include "Physika_Core/Matrices/sparse_matrix.h"
#include "Physika_Core/Vectors/vector_Nd.h"
#include "Physika_Core/Timer/timer.h"
#include "Physika_Core/Matrices/sparse_matrix_iterator.h"
#include "Physika_Core/Matrices/matrix_MxN.h"

#define Max1 1000
#define Max2 2000
#define Max  10000

#define Max3 500
#define Maxv 10
#define mytype double

using namespace std;
using std::cout;

template <class Scalar>
void print(vector<Scalar> &v)
{
    for(int i=0; i<v.size();++i)
        cout<<v[i]<<" ";
    cout<<endl;
}
void compare(const Physika::SparseMatrix<mytype> &a, const Eigen::SparseMatrix<mytype> &b)
{
    /*if (a.nonZeros() != b.nonZeros())
    {
        cout<<"a.nonzeros:"<<a.nonZeros()<<endl;
        cout << "b.nonZeros:" << b.nonZeros() << endl;
        cout << "correctness bad!" << endl;
        return;
    }*/
        std::vector<Physika::Trituple<mytype>> v;
        bool correctness = true;
        for(unsigned int i = 0;i<a.rows();++i)
        {
            v = a.getRowElements(i);
            for(unsigned int j=0;j<v.size();++j)
            {
                int row = v[j].row(), col = v[j].col();
                mytype value = v[j].value();
                if(b.coeff(row,col) != value)
                {
                    cout<<"eror: "<<row<<' '<<col<<" value: psm "<<value<<" "<<b.coeff(row,col)<<endl;
                    correctness = false;
                    break;
                }
            }
        }
		for (unsigned int i = 0; i < b.outerSize();++i)
           for (Eigen::SparseMatrix<mytype>::InnerIterator it(b, i); it; ++it)
            {
                if (it.value() != a(it.row(), it.col()))
                {
                    cout << "eror: " << it.row() << ' ' << it.col() << " value: psm " << a(it.row(),it.col()) << " " << it.value() << endl;
                    correctness = false;
                    break;
                }
            }
        if(correctness) cout<<"correctness OK!"<<endl;
        else cout<<"correctness bad!"<<endl;
}
void compare(const Physika::VectorND<mytype> &a, const Eigen::SparseVector<mytype> &b)
{
    for (unsigned int i = 0; i < a.dims(); ++i)
    {
        if (a[i] != b.coeff(i))
        {
            cout << "uncorrectly vector multiply a sparsematrix" << endl;
            return;
        }
    }
    cout << "correctness OK!" << endl;
    return ;
}
template<class T>
void compare(const vector<T> &a, const vector<T> &b){
	for (unsigned int i = 0; i < a.size(); ++i){
		if (a[i] != b[i])
		{
			cout << "uncorrectness!!!!!!! " << endl;
			return;
		}
	}
	cout << "correctness OK!" << endl;
	return;
}
int main()
{
    Physika::SparseMatrix<mytype> ps1(Max1, Max2, Physika::ROW_MAJOR);
    Eigen::SparseMatrix<mytype> es1(Max1, Max2);
    cout << "correctness of insert operation tests:";
    for (unsigned int i = 0; i<Max; ++i)
    {
        unsigned int row = rand() % Max1;
        unsigned int col = rand() % Max2;
        mytype v = rand() % Max + 1;
        ps1.setEntry(row, col, v);
        es1.coeffRef(row, col) = v;
    }
    compare(ps1, es1);

    Physika::SparseMatrix<mytype> ps2(ps1);
	Eigen::SparseMatrix<mytype> es2(es1);
    cout << "correctness of operator=:";
    compare(ps2, es2);

	cout << "correctness of operation remove:";
	for (unsigned int i = 0; i < Max; ++i)
	{
		unsigned int row = rand() % Max1;
		unsigned int col = rand() % Max2;
		ps2.remove(row, col);
		es2.coeffRef(row, col) = 0;
	}
	compare(ps2, es2);

	cout << "correctness of operation transpose:";
	compare(ps2.transpose(), es2.transpose());


    //get rowElements and colElements function test
    //iterator test
	cout << "correctness of iterator and getRowElements ";
	vector<Physika::Trituple<mytype>> iterator_v;
    for (Physika::SparseMatrixIterator<mytype> it(ps2, Max1 / 2); it; ++it)
    {
        it.row();
        it.value();
        it.col();
		iterator_v.push_back(Physika::Trituple<mytype>(it.row(), it.col(), it.value()));
        /*cout <<"<"<< it.row();
        cout << ", " << it.col();
        cout << ", " << it.value() <<"> ";*/
    }
   // print(ps2.getRowElements(Max1 / 2));
	compare(iterator_v, ps2.getRowElements(Max1 / 2));
 
	Physika::SparseMatrix<mytype> ps3(Max1, Max2, Physika::ROW_MAJOR);
	Eigen::SparseMatrix<mytype> es3(Max1, Max2);
	for (unsigned int i = 0; i<Max; ++i)
	{
		unsigned int row = rand() % Max1;
		unsigned int col = rand() % Max2;
		mytype v = rand() % Max + 1;
		ps3.setEntry(row, col, v);
		es3.coeffRef(row, col) = v;
	}
	cout << "correctness of +:";
	compare(ps1 + ps3, es1 + es3);

	cout << "correctness of +=:";
	compare(ps1 += ps3, es1 += es3);

	cout << "correctness of -:";
	compare(ps1 - ps3, es1 - es3);

	cout << "correctness of -=:";
	compare(ps1 -= ps3, es1 -= es3);

	cout << "correctness of * scalar:";
	compare(ps1*3, es1*3);

	cout << "correctness of *= scalar:";
	compare(ps1*=3, es1*=3);

	cout << "correctness of / scalar:";
	compare(ps1 / 3, es1 / 3);

	cout << "correctness of /= scalar:";
	compare(ps1 /= 3, es1 /= 3);

	cout << "correctness of * matrix:";
	Physika::SparseMatrix<mytype> ps4(Max2, Max3);
	Eigen::SparseMatrix<mytype> es4(Max2, Max3);
	for (unsigned int i = 0; i<Max; ++i)
	{
		unsigned int row = rand() % Max2;
		unsigned int col = rand() % Max3;
		mytype v = rand() % Max + 1;
		ps4.setEntry(row, col, v);
		es4.coeffRef(row, col) = v;
	}
	compare(ps1*ps4, es1*es4);
	
	cout << "correctness of * vectorND:";
	Eigen::SparseVector<mytype> ev1(Max2);
	Physika::VectorND<mytype> pv1(Max2, 0);
	for (unsigned int i = 0; i<Max2; ++i)
	{
		mytype v = rand() % Max + 1;
		pv1[i] = v;
		ev1.coeffRef(i) = v;
	}
	compare(ps1*pv1, es1*ev1);

	cout << "correct of leftMultiply:";
	Eigen::SparseVector<mytype> ev2(Max1);
	Physika::VectorND<mytype> pv2(Max1, 0);
	for (unsigned int i = 0; i<Max1; ++i)
	{
		mytype v = rand() % Max + 1;
		pv2[i] = v;
		ev2.coeffRef(i) = v;
	}
	compare(pv2*ps1, (es1.transpose())*ev2);

    return 0;
}