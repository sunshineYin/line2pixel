#include "line2pixel.h"
#include <fstream>
#include <string>
#include <sstream>
#include "stdlib.h"
using namespace std;

//define a struct to save each polygon
typedef struct polygon{
    int globalidx;
    int localidx;
    int nv;
    int bbx[2][2];
    int bby[2][2];
    vector<vector<long int>> vertices;
    polygon(){
    }
} POLYGON;

vector<string> split(const string &s, char delim){
    stringstream ss(s);
    string item;
    vector<string> tokens;
    while(getline(ss, item, delim)){
        tokens.push_back(item);
    }
    return tokens;
}


int main(){

	//int polygon[12][2] = {{52,30},{74,43},{60,60},{38,60},{30,50},{10,50},{10,28},{22,41},{33,10},{50,10},{39,30},{52,30}};
//	double polygon[11][2] = {{10,10}, {13.8196,10},{15,13.6326},{16.1802,10},{20,10},{16.9097,7.7548},{18.09,4.1221},\
//	{14.9999,6.3672},{11.9097,4.1221},{13.0901,7.7548},{10,10}};
    //go through the data file, read polygon one after another
    ifstream input_file("sample_1tilesskipbroken.txt");
    string single_line;
    ofstream output("output.txt", ofstream::out);

    while(getline(input_file,single_line)){
        POLYGON *py = new POLYGON();
        cout << single_line << endl;
        //do stuff for each polygon
        single_line.erase(0,8); // remove "BSP162  "
        size_t pos = single_line.find("POLYGON((");
        string polygon_bbx = single_line.substr(0,pos);
        string polygon_vt = single_line.substr(pos+9);
        polygon_vt.replace(polygon_vt.find("))"),2,",");
        //cout << polygon_bbx << endl;
        //cout << polygon_vt << endl;
        vector<string> bbx_split = split(polygon_bbx, ',');
        vector<string> vt_split = split(polygon_vt, ',');
        for(int i = 0; i < bbx_split.size(); i++){
            //cout << bbx_split[i] << endl;
        }
        for(int i = 0; i < vt_split.size(); i++){
            //cout << vt_split[i] << endl;
            vector<string> number = split(vt_split[i], ' ');
            vector<long int> temp;
            for(int j = 0; j < number.size(); j++){
                //cout << number[j].c_str() << " ";
                temp.push_back((long int)atoi(number[j].c_str()));
            }
            //cout << endl;
            py->vertices.push_back(temp);
            temp.clear();
        }
        for(int i = 0; i < py->vertices.size(); i++){
            vector<long int> temp = py->vertices[i];
            //for(int j = 0; j < temp.size(); j++)
                //cout << temp[j] << " ";
            //cout << endl;
        }
        vector<vector<long int> > outpoint;
        polygonRaster(py->vertices, outpoint);
        for(int i = 0; i < outpoint.size(); i++){
            output << outpoint[i][0] << " " << outpoint[i][1] << endl;
        }
        delete(py);
    }
    output.close();

//	double polygon[POLYGON_SIZE][2] = {{27579,95540},{27666,95540},{27719,95535},{27633,95535},{27579,95540}};
//	long int round_polygon[POLYGON_SIZE][2];
//	double factor = 1;
//	for(int i = 0; i < POLYGON_SIZE; i++){
//		for(int j = 0; j < 2; j++){
//			polygon[i][j] *= factor;
//			round_polygon[i][j] = round(polygon[i][j]);
//		}
//	}
//	vector<vector<long int> > outpoint;
//	polygonRaster(round_polygon, outpoint);
//	ofstream output("output.txt", ofstream::out);
//	for(int i = 0; i < outpoint.size(); i++){
//		output << outpoint[i][0] << " " << outpoint[i][1] << endl;
//	}
//	output.close();
}
