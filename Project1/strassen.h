#include <bits/stdc++.h>
using namespace std;
/**
 * implement strassen divid and conquer algorithm for matrix multiplication
 * 
 * @param
 *  a --> a 2d vector
 *  b --> a 2d vector
 * 
 * @return
 * the result of a*b "matrix multiplcation"
*/


	
//size at which the sequential multiplication is used instead of recursive Strassen
int thresholdSize = 128;

void initMat(vector< vector<int> >& a, vector< vector<int> >& b, int n)
{
	// initialize matrices and fill them with random values
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			a[i][j] = (int)rand() / RAND_MAX * 10;
			b[i][j] = (int)rand() / RAND_MAX * 10;
		}
	}
}

vector<vector<int>> multiplyMatStandard(vector< vector<int> >& a,
	vector< vector<int> >& b, vector< vector<int> >& c, int n)
{
	// standard matrix multiplication: C <- C + A x B
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			int temp = 0;
			for (int k = 0; k < n; ++k) {
				temp += a[i][k] * b[k][j];
			}
			c[i][j] = temp;
		}
	}
	return c;
}

int getNextPowerOfTwo(int n)
{
	return pow(2, int(ceil(log2(n))));
}

void fillZeros(vector< vector<int> >& newA, vector< vector<int> >& newB,
	vector< vector<int> >& a, vector< vector<int> >& b, int n)
{
	//pad matrix with zeros
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			newA[i][j] = a[i][j];
			newB[i][j] = b[i][j];
		}
	}
}

void add(vector< vector<int> >& a, vector< vector<int> >& b,
	vector< vector<int> >& resultMatrix, int n)
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			resultMatrix[i][j] = a[i][j] + b[i][j];
		}
	}
}

void subtract(vector< vector<int> >& a, vector< vector<int> >& b,
	vector< vector<int> >& resultMatrix, int n)
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			resultMatrix[i][j] = a[i][j] - b[i][j];
		}
	}
}

vector<vector<int>>  multiplyStrassen(vector< vector<int> >& a,vector< vector<int> >& b, vector< vector<int> >& c, int n){
	if (n <= thresholdSize) {
		multiplyMatStandard(a, b, c, n);
	}
	else {
		//expand and fill with zeros if matrix size is not a power of two
		int newSize = getNextPowerOfTwo(n);
		vector< vector<int> >
			newA(newSize, vector<int>(newSize)),
			newB(newSize, vector<int>(newSize)),
			newC(newSize, vector<int>(newSize));
		if (n == newSize) {   //matrix size is already a power of two
			newA = a;
			newB = b;
		}
		else {
			fillZeros(newA, newB, a, b, n);
		}

		//initialize submatrices
		int blockSize = newSize / 2;  //size for a partition matrix
		vector<int> block(blockSize);
		vector< vector<int> >
			/*partitions of newA*/
			a11(blockSize, block), a12(blockSize, block),
			a21(blockSize, block), a22(blockSize, block),
			/*partitions of newB*/
			b11(blockSize, block), b12(blockSize, block),
			b21(blockSize, block), b22(blockSize, block),
			/*partitions of newC*/
			c11(blockSize, block), c12(blockSize, block),
			c21(blockSize, block), c22(blockSize, block),
			/*matrices storing intermediate results*/
			aBlock(blockSize, block), bBlock(blockSize, block),
			/*set of submatrices derived from partitions*/
			m1(blockSize, block), m2(blockSize, block),
			m3(blockSize, block), m4(blockSize, block),
			m5(blockSize, block), m6(blockSize, block),
			m7(blockSize, block);

		//partition matrices
		for (int i = 0; i < blockSize; i++) {
			for (int j = 0; j < blockSize; j++) {
				a11[i][j] = newA[i][j];
				a12[i][j] = newA[i][j + blockSize];
				a21[i][j] = newA[i + blockSize][j];
				a22[i][j] = newA[i + blockSize][j + blockSize];
				b11[i][j] = newB[i][j];
				b12[i][j] = newB[i][j + blockSize];
				b21[i][j] = newB[i + blockSize][j];
				b22[i][j] = newB[i + blockSize][j + blockSize];
			}
		}

		//compute submatrices
		//m1 = (a11+a22)(b11+b22)
		add(a11, a22, aBlock, blockSize);
		add(b11, b22, bBlock, blockSize);
		multiplyStrassen(aBlock, bBlock, m1, blockSize);

		//m2 = (a21+a22)b11
		add(a21, a22, aBlock, blockSize);
		multiplyStrassen(aBlock, b11, m2, blockSize);

		//m3 = a11(b12-b22)
		subtract(b12, b22, bBlock, blockSize);
		multiplyStrassen(a11, bBlock, m3, blockSize);

		//m4 = a22(b21-b11)
		subtract(b21, b11, bBlock, blockSize);
		multiplyStrassen(a22, bBlock, m4, blockSize);

		//m5 = (a11+a12)b22
		add(a11, a12, aBlock, blockSize);
		multiplyStrassen(aBlock, b22, m5, blockSize);

		//m6 = (a21-a11)(b11+b12)
		subtract(a21, a11, aBlock, blockSize);
		add(b11, b12, bBlock, blockSize);
		multiplyStrassen(aBlock, bBlock, m6, blockSize);

		//m7 = (a12-a22)(b12+b22)
		subtract(a12, a22, aBlock, blockSize);
		add(b12, b22, bBlock, blockSize);
		multiplyStrassen(aBlock, bBlock, m7, blockSize);

		//calculate result submatrices
		//c11 = m1+m4-m5+m7
		add(m1, m4, aBlock, blockSize);
		subtract(aBlock, m5, bBlock, blockSize);
		add(bBlock, m7, c11, blockSize);

		//c12 = m3+m5
		add(m3, m5, c12, blockSize);

		//c21 = m2+m4
		add(m2, m4, c12, blockSize);

		//c22 = m1-m2+m3+m6
		subtract(m1, m2, aBlock, blockSize);
		add(aBlock, m3, bBlock, blockSize);
		add(bBlock, m6, c22, blockSize);

		//calculate final result matrix
		for (int i = 0; i < blockSize; i++) {
			for (int j = 0; j < blockSize; j++) {
				newC[i][j] = c11[i][j];
				newC[i][blockSize + j] = c12[i][j];
				newC[blockSize + i][j] = c21[i][j];
				newC[blockSize + i][blockSize + j] = c22[i][j];
			}
		}

		//remove additional values from expanded matrix
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				c[i][j] = newC[i][j];
			}
		}
	}
	return c;
}

int calculateMean(vector<int> data, int size)
{
	int sum = 0.0, mean = 0.0;
	for (int i = 0; i < size; ++i) {
		sum += data[i];
	}

	mean = sum / size;
	return mean;
}