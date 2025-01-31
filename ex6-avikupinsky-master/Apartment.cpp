//
// Created by aviku on 19/12/2021.
//

#include "Apartment.h"
#include <cmath>

/**
 * this is the destructor
 * @param Coordinates
 */
Apartment::Apartment(const std::pair<double, double> &Coordinates):_x(Coordinates.first),_y(Coordinates.second) {
}

/**
 * getting the first element x
 * @return -x
 */
double Apartment::get_x() const {
    return _x ;
}

/**
 * getting the second element y
 * @return _y
 */
double Apartment::get_y() const {
    return _y;
}

/**
 * operator <: checking if the Apartment we have is smaller then then other Apartment
 * @param other
 * @return true or false
 */
bool Apartment::operator<(const Apartment &other) const {
    double check1, check2;
    check1 = sqrt((pow(get_x()-X_FEEL_BOX,2)) + (pow(get_y() - Y_FEEL_BOX,2)));
    check2 = sqrt((pow(other.get_x() - X_FEEL_BOX ,2)) + (pow(other.get_y() -Y_FEEL_BOX ,2)));
    return check1 < check2;
}


/**
 * operator >: checking if the Apartment we have is bigger then then other Apartment
 * @param other
 * @return true or false
 */
bool Apartment::operator>(const Apartment &other) const {
    double check1, check2;
    check1 = sqrt((pow(get_x()-X_FEEL_BOX,2)) + (pow(get_y() - Y_FEEL_BOX,2)));
    check2 = sqrt((pow(other.get_x() - X_FEEL_BOX ,2)) + (pow(other.get_y() -Y_FEEL_BOX ,2)));
    return check1 > check2;
}

/**
 * operator =: checking if the Apartment we have is even then then other Apartment
 * @param other
 * @return true or false
 */
bool Apartment::operator==(const Apartment &other) const {
    double check1, check2;
    bool last = false;
    check1 = std::fabs(this->get_x() - other.get_x());
    check2 = std::fabs(this->get_y() - other.get_y());
    if (check1 < EPSILON && check2 < EPSILON) {
        last = true;
    }
    return last;
}

/**
 * printing the Apartment
 * @param os
 * @param apartment
 * @return os
 */
std::ostream &operator<<(std::ostream &os, const Apartment &apartment) {
    os << "(" << apartment._x << "," << apartment._y << ")" << std::endl;
    return os;
}