#include <cmath>
#include <cstdlib>
//#include "random.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

template<typename T>
void swap(T* x, T* y)
{
    T tmp = *x;
    *x = *y;
    *y = tmp;
}

//low and high both are positive
int getRandomInt(int low, int high)
{
    srand((unsigned)time(0));
    int tmp = 0;
    while((tmp = rand()%high + 1) < low);
    return tmp;
}

double frandom()
{
    int tmp = 0, max = 100;
    double flag = 1.0;
    //srand((unsigned)time(0));
    flag = rand()%100 > 49 ? 1.0 : -1.0;
    return flag * (1.0*rand()/RAND_MAX);
}

template<typename T>
class Matrix
{
    private:
        int rows;
        int columns; 
        T* element;

    public:
        Matrix(int r, int v):rows(r),columns(v)
        {
            //rows = h;
            //columns = v;
            element = new T[rows * columns];
            for(int i=0; i<rows*columns; i++)
                element[i] = 0;
        }

        Matrix(Matrix<T>& m)
        {
            rows = m.rows;
            columns = m.columns;
            element = new T[rows * columns];
            for(int i=0; i<rows*columns; i++)
                element[i] = m.element[i];
        }

        //m is a column vector.
        /*Matrix(Matrix<T>& m, int r, int v):rows(r), columns(v)
        {
            element = new T[rows * columns];
            for(int i=0; i<rows; i++)
                for(int j=0; j<columns; j++)
                {
                    element[i*columns+j] == m.element[i];
                }
        }*/

        ~Matrix()
        {
            delete []element;
            //cout<<"free the memory!"<<endl;
        }

        //assignment a value ranged in (0, 1)
        Matrix<T>& getRandomValues(int max)
        {
            srand((unsigned)time(0));
            for(int i=0; i<rows*columns; i++)
                element[i] = rand()%(max*10)/10.0;
            return *this;
        }

        Matrix<T>& getRandomValues()
        {
            srand((unsigned)time(0));
            for(int i=0; i<rows*columns; i++)
                element[i] = frandom();
            return *this;
        }

        Matrix<T>& operator=(Matrix<T>& x)
        {
            //cout<<"copy object"<<endl;
            rows = x.getrows();
            columns = x.getcolumns();
            for(int i=0; i<rows; i++)
                for(int j=0; j<columns; j++)
                    element[i*columns + j] = x.element[i*columns+j];
            return *this;
        }
        
        //a point to array
        Matrix<T>& operator=(T* ptr)
        {
            for(int i=0; i<rows*columns; i++)
                element[i] = ptr[i];
        }

        Matrix<T>& operator+=(Matrix<T>& y)
        {
            for(int i=0; i<rows*columns; i++)
                element[i] += y.element[i];
            return *this;
        }

        Matrix<T>& operator-=(Matrix<T>& y)
        {
            for(int i=0; i<rows*columns; i++)
                element[i] -= y.element[i];
            return *this;
        }

        Matrix<T>* operator*(Matrix<T>& y)
        {
            Matrix<T>* re = new Matrix<T>(rows, y.columns); 
            for(int i=0; i<rows; i++)
                for(int j=0; j<y.columns; j++)
                    for(int k=0; k<columns; k++)
                        re->element[i*re->columns+j] += element[i*columns+k] * y.element[k*y.columns+j];
            return re;
        }

        Matrix<T>& multiple(const Matrix<T>& y, Matrix<T>& res) const
        {
            for(int i=0; i<rows; i++)
                for(int j=0; j<y.columns; j++)
                {
                    T tmp = 0;
                    for(int k=0; k<columns; k++)
                    {
                        tmp += element[i*columns+k] * y.element[k*y.columns+j];
                    }
                    res.element[i*res.columns+j] = tmp;
                }
            return res;    
        }

        void printMatrix()
        {
            for(int i=0; i<rows; i++)
            {
                for(int j=0; j<columns; j++)
                {
                    cout<<element[i*columns+j]<<'\t';        
                }
                cout<<endl;
            }
        }

        void writeCSV(const string& filename="output")
        {
            fstream fs;
            string fname = filename+".csv";
            fs.open(fname.c_str(), fstream::out|fstream::trunc);
            if(!fs)
            {
                cout<<"create file failure: "<<filename<<endl;
                return;
            }
            int i, j;
            for(i=0; i<rows; i++)
            {
                for(j=0; j<columns-1; j++)
                {
                    fs<<getElement(i, j)<<",";
                }
                fs<<getElement(i, j)<<endl;
            }
            fs.close();
            cout<<"create file successfully: "<<filename<<endl;
        }

        /*****************************************************
         *Matrix's zhuanzhi
         *
         *
         * **************************************************/
        Matrix<T>& Matrix_T(Matrix<T>& re)
        {
            //Matrix<T> re(columns, rows);
            for(int i=0; i<re.rows; i++)
            {
                for(int j=0; j<re.columns; j++)
                {
                    re.element[i*re.columns+j] = element[j*columns+i];
                }
            }
            return re;
        }
        
        /********************************************************
         *get the element of coordinate(x,y)
         *
         *
         * *****************************************************/
        T getElement(int x, int y)
        {
            return element[(x-1)*columns+y-1];
        }

        T getElement(int x)
        {
            return element[x-1];
        }
        
        //get all of Matrix's elements
        T* getElement(T* ptr)
        {
            for(int i=0; i<rows*columns; i++)
                ptr[i] = element[i];
        }

        void setElement(int x, int y, T value)
        {
            element[(x-1)*columns+y-1] = value; 
        }

        void setElement(int x, T value)
        {
            element[x-1] = value;
        }

        int getrows(){ return rows; }//get row numbers
        int getcolumns(){ return columns; }//get columns numbers

        /******************************************
         *get row vectors
         *begin: the begin row number
         *end  : the end end number
         * ***************************************/
        Matrix<T>* getRowVectors(int begin, int end)
        {
            Matrix<T>* re = new Matrix<T>(end-begin+1, columns);                   
            for(int i=begin-1; i<end; i++)
                for(int j=0; j<columns; j++)
                    re->element[(i-re->rows+1)*columns+j] = element[i*columns+j];
            return re;
        }

        Matrix<T>& getRowVectors(Matrix<T>& rVec, int begin, int end)
        {
            for(int i=begin-1; i<end; i++)
                for(int j=0; j<columns; j++)
                    rVec.element[(i-rVec.rows+1)*columns+j] = element[i*columns+j];
            return rVec;
        }

        Matrix<T>& getRowVectors(Matrix<T>& rVec, int rnum)
        {
            int k=0;
            for(int i=(rnum-1)*columns; i<rnum*columns; i++)
                rVec.element[k++] = element[i];
            return rVec;
        }
        
        /******************************************
         *get cloumn vectors
         *begin: the begin columns number
         *end  : the end columns number
         * ***************************************/
        Matrix<T>* getColVectors(int begin, int end)
        {
            Matrix<T>* re = new Matrix<T>(rows, end-begin+1);
            for(int i=0; i<rows; i++)
                for(int j=begin-1; j<end; j++)
                    re->element[i*re->columns+j-re->columns+1] = element[i*columns+j];
            return re;
        }

        Matrix<T>& getColVectors(Matrix<T>& vVec, int begin, int end)
        {
            for(int i=0; i<rows; i++)
                for(int j=begin-1; j<end; j++)
                    vVec.element[i*vVec.columns+j-vVec.columns+1] = element[i*columns+j];
            return vVec;
        }

        Matrix<T>& getColVectors(Matrix<T>& vVec, int vnum)
        {
            int k=0;
            for(int i=vnum-1; i<rows*columns; i+=columns)
                vVec.element[k++] = element[i];
            return vVec;
        }

        /**********************************************************
         *h->horizon
         *v->columns
         *b->begin
         *e->end
         * ********************************************************/
        Matrix<T>* getChildMatrix(int hb, int he, int vb, int ve)
        {
            int k=0;
            Matrix<T>* re = new Matrix<T>(he-hb+1, ve-vb+1);
            for(int i=hb-1; i<he; i++)
                for(int j=vb-1; j<ve; j++)
                {
                    re->element[k++] = element[i*columns+j];
                }
            return re;
        }

        Matrix<T>& getChildMatrix(Matrix<T>& child, int hb, int he, int vb, int ve)
        {
            int k=0;
            for(int i=hb-1; i<he; i++)
                for(int j=vb-1; j<ve; j++)
                {
                    child.element[k++] = element[i*columns+j];
                }
            return child;
        }
};
