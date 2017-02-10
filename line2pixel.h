#include <vector>
#include <fstream>
#include <cmath>
#include <iostream>

using namespace std;

#define POLYGON_SIZE 5

void line2pixel(long int inpoint[2][2], vector<vector<long int> >& outpoint);
//needs to read data from sample_1tilesskipbroken.txt

//long int round(double r)
//{
//	return (r > 0.0) ? floor(r + 0.5) : ceil(r - 0.5);
//
//}

void polygonRaster(vector<vector<long int>> inpoint, vector<vector<long int> >& outpoint){
	for(int i = 0; i < inpoint.size() - 1; i++){
		long int two_end[2][2];
		two_end[0][0] = inpoint[i][0];
		two_end[0][1] = inpoint[i][1];
		two_end[1][0] = inpoint[i+1][0];
		two_end[1][1] = inpoint[i+1][1];
		line2pixel(two_end, outpoint);
	}
}

void line2pixel(long int inpoint[2][2], vector<vector<long int> >& outpoint){
	long int xlo = inpoint[0][0];
	long int ylo = inpoint[0][1];

	long int xhi = inpoint[1][0];
	long int yhi = inpoint[1][1];
	//cout << xlo << " " << ylo << " " << xhi << " " << yhi << endl;
	vector<long int> single_point;

	//parallel to y direction, y is changing
	if(xhi == xlo){
		if(yhi < ylo){
			long int temp = ylo;
			while(yhi < temp){
				single_point.push_back(xlo);
				single_point.push_back(temp);
				outpoint.push_back(single_point);
				single_point.clear();
				temp--;
			}
		}
		else {
			long int temp = ylo;
			while(yhi > temp){
				single_point.push_back(xlo);
				single_point.push_back(temp);
				outpoint.push_back(single_point);
				single_point.clear();
				temp++;
			}
		}
		return;
	}

	//parallel to x direction, x is changing
	if(yhi == ylo){
		if(xhi < xlo){
			long int temp = xlo;
			while(xhi < temp){
				single_point.push_back(temp);
				single_point.push_back(ylo);
				outpoint.push_back(single_point);
				single_point.clear();
				temp--;
			}
		}
		else {
			long int temp = xlo;
			while(xhi > temp){
				single_point.push_back(temp);
				single_point.push_back(ylo);
				outpoint.push_back(single_point);
				single_point.clear();
				temp++;
			}
		}
		return;
	}

	double a = (double)(yhi - ylo) / (double)(xhi - xlo);

	if(a > 0) {

		long int x = xlo;
		double y = ylo;

		long int prevx = xlo;
		long int prevy = ylo;

		if(xhi > xlo) {
			for(; x <= xhi; x++){
				long int tempy = round(y);
				if(x > prevx && tempy > prevy) {
					//extra point needs to be added in between
					while(tempy > prevy) {
					single_point.push_back(x);
					single_point.push_back(prevy);
					outpoint.push_back(single_point);
					single_point.clear();
					prevy++;
					}
				}
				single_point.push_back(x);
				single_point.push_back(tempy);
				outpoint.push_back(single_point);
				single_point.clear();
				prevx = x;
				prevy = tempy;
				y = y + a;
			}
		}
		else {
			for(; x >= xhi; x--){
				long int tempy = round(y);
				if(x < prevx && tempy < prevy) {
					//extra point needs to be added in between
					while(tempy < prevy){
						single_point.push_back(x);
						single_point.push_back(prevy);
						outpoint.push_back(single_point);
						single_point.clear();
						prevy--;
					}
				}
				single_point.push_back(x);
				single_point.push_back(tempy);
				outpoint.push_back(single_point);
				single_point.clear();
				prevx = x;
				prevy = tempy;
				y = y - a;
			}
		}
	}
	else {
		long int x = xlo;
		double y = ylo;

		long int prevx = xlo;
		long int prevy = ylo;

		if(xhi > xlo) {
			for(; x <= xhi; x++){
				long int tempy = round(y);
				if(x > prevx && tempy < prevy) {
					//extra point needs to be added in between
					while(tempy < prevy){
						single_point.push_back(x);
						single_point.push_back(prevy);
						outpoint.push_back(single_point);
						single_point.clear();
						prevy--;
					}
				}
				single_point.push_back(x);
				single_point.push_back(tempy);
				outpoint.push_back(single_point);
				single_point.clear();
				prevx = x;
				prevy = tempy;
				y = y + a;
			}
		}
		else {
			for(; x >= xhi; x--){
				long int tempy = round(y);
				if(x < prevx && tempy > prevy) {
					//extra point needs to be added in between
					while(tempy > prevy){
						single_point.push_back(x);
						single_point.push_back(prevy);
						outpoint.push_back(single_point);
						single_point.clear();
						prevy++;
					}
				}
				single_point.push_back(x);
				single_point.push_back(tempy);
				outpoint.push_back(single_point);
				single_point.clear();
				prevx = x;
				prevy = tempy;
				y = y - a;
			}
		}
	}
}
