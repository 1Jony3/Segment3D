#include <iostream>
#include <optional>

class Vector3D {
public:
    double X, Y, Z;

    Vector3D(double x = 0, double y = 0, double z = 0) : X(x), Y(y), Z(z) {}

    Vector3D operator-(const Vector3D& other) const {
        return Vector3D(X - other.X, Y - other.Y, Z - other.Z);
    }

    Vector3D operator+(const Vector3D& other) const {
        return Vector3D(X + other.X, Y + other.Y, Z + other.Z);
    }

    Vector3D operator*(double scalar) const {
        return Vector3D(X * scalar, Y * scalar, Z * scalar);
    }

    Vector3D cross(const Vector3D& other) const {
        return Vector3D(
            Y * other.Z - Z * other.Y,
            Z * other.X - X * other.Z,
            X * other.Y - Y * other.X
        );
    }

    double dot(const Vector3D& other) const {
        return X * other.X + Y * other.Y + Z * other.Z;
    }
};

class Segment3D {
public:
    Vector3D start, end;

    Segment3D(const Vector3D& s, const Vector3D& e) : start(s), end(e) {}
};

std::optional<Vector3D> Intersect(const Segment3D& seg1, const Segment3D& seg2) {
    Vector3D u = seg1.end - seg1.start;
    Vector3D v = seg2.end - seg2.start;
    Vector3D w = seg1.start - seg2.start;

    double a = u.dot(u);
    double b = u.dot(v);
    double c = v.dot(v);
    double d = u.dot(w);
    double e = v.dot(w);

    double denominator = a * c - b * b;

    if (denominator == 0.0) {
        return std::nullopt; 
    }

    double s = (b * e - c * d) / denominator;
    double t = (a * e - b * d) / denominator;

    if (s < 0.0 || s > 1.0 || t < 0.0 || t > 1.0) {
        return std::nullopt; 
    }

    Vector3D intersection = seg1.start + u * s;
    return intersection;
}

int main() {
    Vector3D p1, p2, p3, p4;

    std::cout << "Enter the coordinates of the first vector (x y z): ";
    std::cin >> p1.X >> p1.Y >> p1.Z;

    std::cout << "Enter the coordinates of the second vector (x y z): ";
    std::cin >> p2.X >> p2.Y >> p2.Z;

    std::cout << "Enter the coordinates of the third vector (x y z): ";
    std::cin >> p3.X >> p3.Y >> p3.Z;

    std::cout << "Enter the coordinates of the fourth vector (x y z): ";
    std::cin >> p4.X >> p4.Y >> p4.Z;


    Segment3D seg1(p1, p2);
    Segment3D seg2(p3, p4);

    auto result = Intersect(seg1, seg2);

    if (result) {
        std::cout << "Intersection at: (" << result->X << ", " << result->Y << ", " << result->Z << ")\n";
    }
    else {
        std::cout << "No intersection\n";
    }

    return 0;
}
