#include <iostream>
#include <vector>
#include <time.h>
#include <chrono>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <algorithm>

using namespace std;

template <typename K, typename V>
class CartesianCoord{  
public:  
    typedef K value_t;
    value_t x;  
    value_t y;  

    typedef V value_d;
    value_d dist_to_point;
public:  
    CartesianCoord(value_t _x = 0, value_t _y = 0) : x(_x),y(_y) {}
    ~CartesianCoord(void) {}

    template<typename _K, typename _V> friend ostream& operator <<(ostream &out, const CartesianCoord<_K, _V> c) {
        out << "(" << c.x << "," << c.y << ")";
        return out; 
    }
};

typedef CartesianCoord<int, double> coord_t;

bool operator <(coord_t x, coord_t y) {
    return x.dist_to_point < y.dist_to_point ? true : false;
}

vector<coord_t> knn (int k, vector<coord_t> &points, const coord_t &q) {
    for (int i = 0; i < points.size(); i++) {
        points[i].dist_to_point = sqrt((points[i].x - q.x) * (points[i].x - q.x) + (points[i].y - q.y) * (points[i].y - q.y));
    }

    sort(points.begin(), points.end());

    return vector<coord_t>(points.begin(), points.begin() + k);
}

int main() {
    srand (time(NULL));
    vector<coord_t> points;
    for (int i=0; i< 1000; i++)
        points.push_back(coord_t(rand()%1000,rand()%1000));

    vector<coord_t>::iterator it = points.begin();
        
    for (; it != points.end(); it++) {
        fflush(stdout);
        cout << "\r" << *it;
        usleep(2000);
    }
        
    cout << endl;

    vector<coord_t> knns;

    auto start = chrono::high_resolution_clock::now();
    knns = knn(3, points, coord_t(100,200));
    auto stop = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    
    cout << "Time: " << endl;
    cout << duration.count() << endl;
    cout << "knns" << endl;

    vector<coord_t>::iterator kit = knns.begin();

    for (; kit != knns.end(); kit++)
        cout << *kit << endl;
}
