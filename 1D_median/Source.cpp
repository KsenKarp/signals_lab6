#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;
#define N_SECONDS 100

double* read_from_csv(size_t size) {
	double* res = new double[size];
	const char csv_file_name[64] = "data_0.csv";
	std::ifstream csv_file;
	csv_file.open(csv_file_name);
	string str;
	int i = 0;
	for (int i = 0; i < size; i++) {
		csv_file >> str;
		res[i] = stod(str);
	}
	csv_file.close();
	return res;
}

void MedianFilter1D(double* data, int data_size, int kernel_size) {
	double* mid = new double [data_size - kernel_size + 1];
	int h = round(kernel_size / 2);
	for (int num = h; num < data_size - h; num++) {
		vector<double> tmp = vector<double>();
		for (int i = 0; i < kernel_size; i++) tmp.push_back(*(data + num + i - h));
		sort(tmp.begin(), tmp.end());
		if (kernel_size % 2 == 1) *(mid + num - h) = tmp.at(round(kernel_size / 2));
		else *(mid + num - h) = (tmp.at(kernel_size / 2 - 1) + tmp.at(tmp.size() / 2)) / 2;
	}
	for (int k = h; k < data_size - h ; k++) data[k] = mid[k - h];		
	delete[] mid;
	return;
}


int main() {
	double a[5] = { 2, 1, 3, -1, -2 };
	int kernel_size;
	cout << "Enter kernel size: \n";
	cin >> kernel_size;

	double* signal = read_from_csv(100);
	double* copy = read_from_csv(100);

	double F = 10.;
	MedianFilter1D(signal, 100, kernel_size);

	const char csv_file_name[64] = "data.csv";
	std::ofstream csv_file;
	csv_file.open(csv_file_name);
	csv_file << "time, signal, signal filtered" << endl;
	for (size_t i = 0; i < 100; ++i)
	{
		csv_file << i / F << "," << copy[i] << "," << signal[i] << "\n";
	}
	csv_file.close();
	
	return 0;
}
