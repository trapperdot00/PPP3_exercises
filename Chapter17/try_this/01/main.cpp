class Vector
{
public:
	Vector(int n) : sz{n}, elem{new double[n]} {}
	~Vector() { delete[] elem; }
	int size() const { return sz; }
	double get(int n) const { return elem[n]; }
	double operator[](int n) { return elem[n]; }
	void set(int n, double v) { elem[n] = v; }
private:
	int sz;
	double* elem;
};

int main()
{
	Vector v{10};
	v[3] = 3.14; // error: lvalue required as left operand of assignment
}
