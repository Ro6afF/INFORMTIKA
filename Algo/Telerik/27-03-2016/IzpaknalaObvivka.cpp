#include <algorithm>
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

typedef double coord_t;         
typedef double coord2_t;

struct Point {
	coord_t x, y;

	Point(coord_t x = 0, coord_t y = 0)
	{
	    this->x = x;
	    this->y = y;
	}

	static double CrossProduct(const Point &a, const Point &b)
    {
        return a.x * b.y - a.y * b.x;
    }

    Point operator + (const Point &other) const
    {
        return Point(this->x + other.x, this->y + other.y);
    }

    Point operator - (const Point &other) const
    {
        return Point(this->x - other.x, this->y - other.y);
    }

	bool operator <(const Point &p) const {
		return x < p.x || (x == p.x && y < p.y);
	}
};

coord2_t cross(const Point &O, const Point &A, const Point &B)
{
	return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

vector<Point> convex_hull(vector<Point> P)
{
	int n = P.size(), k = 0;
	vector<Point> H(2*n);

	sort(P.begin(), P.end());

	for (int i = 0; i < n; ++i) {
		while (k >= 2 && cross(H[k-2], H[k-1], P[i]) <= 0) k--;
		H[k++] = P[i];
	}

	for (int i = n-2, t = k+1; i >= 0; i--) {
		while (k >= t && cross(H[k-2], H[k-1], P[i]) <= 0) k--;
		H[k++] = P[i];
	}

	H.resize(k);
	return H;
}

void PrintVector2Container(vector<Point> c)
{
    for(int i=0; i<(int)c.size(); i++)
    {
        cout<<c[i].x<<" "<<c[i].y<<endl;
    }
}

int main()
{
    int n;
    cin>>n;

    vector<Point> poly;

    for(int i=0; i<n; i++)
    {
        double x, y;
        cin>>x>>y;

        poly.push_back(Point(x,y));
    }
    cout<<"------------------"<<endl;
    PrintVector2Container((convex_hull(poly)));
}
