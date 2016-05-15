#include "matrix.h"
#include <ctime>

int main(int argc, char* args[])
{
    cout << "init matrix" << endl;
    Matrix<double> m(3, 4);
    m.getRandomValues();
    m.printMatrix();
    cout<<endl<<endl;
    //double ele[4] = {1, 2, 3, 4};
    //m = ele;
    //m.getRandomValues();
    //m.printMatrix();
    cout<<"assign matrix to a point"<<endl;
    double *ptr = new double[12];
    m.getElement(ptr);
    for(int i=0; i<12; i++)
        cout<<ptr[i]<<'\t';
    cout<<endl<<endl;

    cout<<"construct matrix"<<endl;
    Matrix<double> m2(m);
    m2.printMatrix();
    cout<<endl<<endl;

    cout<<"copy matrix"<<endl;
    Matrix<double> m1(3, 4);
    m1 = m;
    m1.printMatrix();
    cout<<endl<<endl;

    cout<<"matrix plus matrix"<<endl;
    m1 += m;
    m1.printMatrix();
    cout<<endl<<endl;

    cout<<"zhuanzhi"<<endl;
    Matrix<double> m_T(4,3);
    m_T = m.Matrix_T(m_T);
    m_T.printMatrix();
    cout<<endl<<endl;

    cout<<"matrix multiple matrix"<<endl;
    Matrix<double>* mre = m*m_T;
    mre->printMatrix();
    cout<<endl<<endl;

    cout<<"Matrix multiple Matrix point"<<endl;
    Matrix<double>* mp = m * (*mre);
    mp->printMatrix();
    cout<<endl<<endl;

    cout<<"Matrix point plus Matrix"<<endl;
    *mre += m;
    mre->printMatrix();

    cout<<endl<<endl;

    cout<<"get row vector(2-3 rows)"<<endl;
    Matrix<double>* hlines = m.getRowVectors(2,3);
    hlines->printMatrix();
    cout<<endl<<endl;

    cout<<"vlines"<<endl;
    Matrix<double>* vlines = m.getColVectors(2,3);
    vlines->printMatrix();
    cout<<endl<<endl;
    Matrix<double> vline(1, 4);
    m.getRowVectors(vline, 2);
    vline.printMatrix();
    Matrix<double> vline2(3, 1);
    m.getColVectors(vline2, 2);
    vline2.printMatrix();
    cout<<"vline end"<<endl<<endl;
    //cout<<RAND_MAX<<endl;

    cout<<"childMatrix(row(2-3), col(3-4))"<<endl;
    Matrix<double> child(2, 2);
    child = m.getChildMatrix(child, 2, 3, 3, 4);
    child.printMatrix();
    cout<<endl<<endl;

    Matrix<double>* child1 = m.getChildMatrix(2, 3, 3, 4);
    child1->printMatrix();
    cout<<endl<<endl;

    cout<<"mul test"<<endl;
    Matrix<double> mulres(3, 3);
    mulres = m.multiple(m_T, mulres);
    mulres.printMatrix();

    mulres.writeCSV("haha");

    return 0;
}
