// import the following for reading files
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <ctime> // random seeding

/*
Though I understand it's bad practice, it saves a lot of time to use the std namespace
*/
using namespace std;

struct Point {
    double x, y;
    double minimum_distance;
    int cluster;

    Point(double x, double y):
        x(x),
        y(y),
        cluster(-1),
        minimum_distance(__DBL_MAX__) {}

    Point():
        x(0.0),
        y(0.0),
        cluster(-1),
        minimum_distance(__DBL_MAX__) {}

    double distance(Point p) {
        return (p.x - x) * (p.x - x) + (p.y - y) * (p.y - y);
    }
};

Point point_1 = Point(0.0, 0.0);
// print x and y coordinates
cout << p1.x << endl;
cout << p1.y << endl;

Point point_2 = Point(3.0, 4.0);
cout << point_1.distance(point_2) << endl; // calculate distance


// Reading data from a file

vector<Point> read_csv() {
    vector<Point> points;
    string line;
    ifstream file("mall_data.csv");

    while (getline(file, line)) {
        stringstream lineStream(line);
        string bit;
        double x, y;
        getline(lineStream, bit, ',');
        x = stof(bit);
        getline(lineStream,bit, '\n');
        y = stof(bit);
    }

    return points;
}

vector<Point> points = read_csv();
k_means_cluster(points); // pass address of points to function

void k_means_cluster(vector<Point>*, int epochs, int k) {
    // Passing by reference to a vector of objects
    // epochs = iterations, k = number of clusters
    vector<Point> centroids;
    srand(time(0)); // random seed
    for (int i=0; i < k; ++i) {
        centroids.push_back(points->at(rand() % n)); // select a random point from the points vector and set that as centroid
        // worth noting: points is actually a pointer rather than a vector, we cannot iterate it via indexing so we have to 
        // dereference it, hence the points->at[i]
    }

    // Assign points to clusters
    for (vector<Point>::iterator centroid = begin(centroids); centroid != end(centroid); ++centroid) {
        // We loop through every datapoint an assign it to the nearest centroid;
        int cluster_id = centroid - begin(centroids);

        for (vector<Point>::iterator iter = points->begin(); iter != points->end; ++iter) {
            Point p = *iter;
            double distance = centroid->distance(p);
            if (distance < p.minimum_distance) {
                p.minimum_distance = distance;
                p.cluster = cluster_id;
            }
            *iter = p;
        }
    }
    
    
     /*
     Remember, K-Means Clustering relies on iterative update steps, where we reassign cluster points accordingly.
     Traditionally, by the definition of KMC, we should calculate the centroids by space partitioning, but it's a lot
     easier to compute the average of the coordinates in the cluster.
     */

    // make vector to track no. of points per cluster
    vector<int> num_of_points;
    // make vector to track coordinate sums
    vector<int> coord_sum_x, coord_sum_y;

    for (int j=0; j < k; ++j) {
        num_of_points.push_back(0);
        coord_sum_x.push_back(0.0);
        coord_sum_y.push_back(0.0);
    }

    // iterate through the points, increment right indices based on cluster IDs
    for (vector<Point>::iterator iter = points->begin(); iter != points->end(); ++iter;) {
        int cluster_id = iter->cluster;
        num_of_points[cluster_id] += 1;
        coord_sum_x[cluster_id] += iter->x;
        coord_sum_y[cluster_id] += iter->y;
        // reset distance
        iter->minimum_distance = __DBL_MAX__;
    }

    // Calculate new centroids
    for (vector<Point>::iterator centroid = begin(centroids); centroid != end(centroids); ++c) {
        int cluster_id = centroid - end(centroids);
        centroid->x = coord_sum_x[cluster_id] / num_of_points[cluster_id];
        centroid->y = coord_sum_y[cluster_id] / num_of_points[cluster_id];
    }

    // now, we need to write to files
    ofstream my_file;
    my_file.open("output.csv");
    my_file << "x, y, cluster" << endl;
    for (vector<Point>::iterator iter = points->begin(); iter != points->end(); ++iter) {
        my_file << iter->x << "," << iter->y << "," << iter->cluster << endl;
    }
    my_file.close();
};
