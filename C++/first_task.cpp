#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <algorithm>

#define DX 0.1

using namespace std;

template<typename T>
ostream& operator<<(ostream& os, vector<T> out) {
    os << fixed << setprecision(4);
    for (int i = 0; i < out.size() ; i++) {
    	os << setw(8) << out[i];
        if ((i + 1) % 10 == 0) cout << endl;
    }

    return os;
}

vector<float> solveCircle(const float& dx, float xStart, const int& xEnd) {
    vector<float> y;

    for (; xStart < xEnd; xStart += dx) {
        y.push_back(sqrt(4 - pow((xStart + 8), 2)) - 2);
    }

    return y;
}

vector<float> solveLine(const float& dx, float xStart, const int& xEnd) {
	vector<float> y;

    for (; xStart < xEnd; xStart += dx) {
        y.push_back(0.5 * (xStart + 2));
    }

    return y;
}

vector<float> solveFlatLine(const float& dx, float xStart, const int& xEnd) {
	vector<float> y;

    for (; xStart < xEnd; xStart += dx) {
        y.push_back(0);
    }

    return y;
}

vector<float> solveParabola(const float& dx, float xStart, const int& xEnd) {
	vector<float> y;

    for (; xStart < xEnd; xStart += dx) {
        y.push_back(pow((xStart - 6), 2));
    }

    return y;
}

int main() {

	vector<float> out;
	
	cout << "y:" << endl;
	
	out = solveCircle(DX , -10, -6);
	cout << out << endl;
	
	cout << endl;
	
	out = solveLine(DX, -6,  2);
	cout << out << endl;
	
	cout << endl;
	
	out = solveFlatLine(DX, 2,  6);
	cout << out << endl;
	
	cout << endl;
	
	out = solveParabola(DX, 6, 8+DX);
	cout << out << endl;

    return 0;
}