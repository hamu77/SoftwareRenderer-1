#include "matrix.h"
#include <math.h>

Vector3 Matrix4::matMultVec(Vector3 &vec, float w){
    Vector3 newVec(0,0,0);
    newVec.x = vec.x*(*this)(0,0)+
               vec.y*(*this)(0,1)+
               vec.z*(*this)(0,2)+
               w*(*this)(0,3);

    newVec.y = vec.x*(*this)(1,0)+
               vec.y*(*this)(1,1)+
               vec.z*(*this)(1,2)+
               w*(*this)(1,3);

    newVec.z = vec.x*(*this)(2,0)+
               vec.y*(*this)(2,1)+
               vec.z*(*this)(2,2)+
               w*(*this)(2,3);

    return newVec;
}

Matrix4 Matrix4::makeFullRotMat(float alpha, float beta, float gamma){
    Matrix4 rotMat;
    float cosA = std::cos(alpha);
    float sinA = std::sin(alpha);

    float cosB = std::cos(beta);
    float sinB = std::sin(beta);

    float cosG = std::cos(gamma);
    float sinG = std::sin(gamma);

    //First row
    rotMat(0,0) = cosB*cosG;
    rotMat(0,1) = -cosA*sinG + sinA*sinB*cosG;
    rotMat(0,2) = sinA*sinG + cosA*sinB*cosG;

    //Second row
    rotMat(1,0) = cosB*sinG;
    rotMat(1,1) = cosA*cosG + sinA*sinB*sinG;
    rotMat(1,2) = -sinA*cosG + cosA*sinB*sinG;

    //Third row
    rotMat(2,0) = -sinB;
    rotMat(2,1) = sinA*cosB;
    rotMat(2,2) = cosA*cosB;

    //Fourth row
    rotMat(3,3) = 1;

    return rotMat;
}

Matrix4 Matrix4::makeScaleMat(float scaleX, float scaleY, float scaleZ){
    Matrix4 scaleMat;
    scaleMat(0,0) = scaleX;
    scaleMat(1,1) = scaleY;
    scaleMat(2,2) = scaleZ;
    scaleMat(3,3) = 1;
    return scaleMat;
}

Matrix4 Matrix4::makeTranslateMat(float dx, float dy, float dz){
    Matrix4 transMat;
    transMat(0,0) = 1;
    transMat(1,1) = 1;
    transMat(2,2) = 1;
    transMat(0,3) = dx;
    transMat(1,3) = dy;
    transMat(2,3) = dz;
    transMat(3,3) = 1;

    return transMat;
}

Matrix4 Matrix4::makeTestMat(){
    Matrix4 testMat;
    int n = 4;
    int val = 1;
    for(int rows = 0; rows < n; ++rows){
        for(int cols = 0; cols < n; ++cols){
            testMat(rows,cols) = val;
            ++val;
        }
    }
    return testMat;
}

void Matrix4::printMat(){
    int n = 4;
    for(int rows = 0; rows < n; ++rows){
        for(int cols = 0; cols < n; ++cols){
            float val = (*this)(rows,cols) ;
            printf("%f\t",val);
        }
        printf("\n");
    }
    printf("\n");
}


//Way too general, should probably change in the future since I think
//I'll only need 4x4 stuff and this technically allows for any n matrix.
//Traverse the matrix cell by cell and find the final value through a step of 
//sub multiplications that are then added together
Matrix4 Matrix4::operator*(Matrix4 rhs){
    //Matrix dimensions
    Matrix4 results;
    int n = 4;

    for(int rows = 0; rows < n; ++rows){
        for(int cols = 0; cols < n; ++cols){
            float total = 0;
            //total value of multiplication with all submultiplications added together

            //sub represents submultiplications in the actual matrix multiplication
            //For a nxn matrix you have n submultiplications

            for(int sub = 1; sub < n+1; ++sub ){
                int rowLhs = rows; //row ind left matrix
                int colLhs = sub - 1; //col ind left matrix

                int rowRhs = sub -1; //row ind right matrix
                int colRhs = cols; //col ind right matrix

                total += (*this)(rowLhs,colLhs) * rhs(rowRhs,colRhs);
                
            }

            //Setting the specific row and column to the total value of the subm-
            //multiplications for that specifc cell of the matrix
            results(rows,cols) = total;
        }
    }
    return results;
}

Matrix4 Matrix4::modelMatrix(Vector3 pos, Vector3 rot, Vector3 scale){
    Matrix4 rotMatrix = Matrix4::makeFullRotMat(rot.x, rot.y, rot.z);
    Matrix4 scaleMatrix = Matrix4::makeScaleMat(scale.x, scale.y, scale.z);
    Matrix4 translationMatrix = Matrix4::makeTranslateMat(pos.x, pos.y, pos.z);

    return  translationMatrix*(rotMatrix*scaleMatrix);
}