#ifndef INTERVAL_H
#define INTERVAL_H

class interval {
public:
    double min, max;

    interval() 
    {
        min = -INFINITY;
        max = INFINITY;
    } // Default interval is empty

    interval(double _min, double _max) : min(_min), max(_max) {}

    double size() const {
        return max - min;
    }

    interval(const interval& a, const interval& b)
        : min(fmin(a.min, b.min)), max(fmax(a.max, b.max)) {}

    interval expand(double delta) const {
        auto padding = delta / 2;
        return interval(min - padding, max + padding);
    }

    bool contains(double x) const {
        return min <= x && x <= max;
    }

    bool surrounds(double x) const {
        return min < x&& x < max;
    }

    double clamp(double x) const {
        if (x < min) return min;
        if (x > max) return max;
        return x;
    }

    static const interval empty, universe;
};


const static interval empty(+INFINITY, -INFINITY);
const static interval universe(-INFINITY, +INFINITY);

#endif