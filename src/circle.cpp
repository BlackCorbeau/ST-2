// Copyright 2022 UNN-CS
#include "circle.h"
#include <cmath>
#include <stdexcept>

const double PI = 3.14159265358979323846;

Circle::Circle(double radius) {
  if (radius <= 0) {
    throw std::invalid_argument("Radius must be positive");
  }
  radius_ = radius;
  updateFromRadius();
}

void Circle::setRadius(double radius) {
  if (radius <= 0) {
    throw std::invalid_argument("Radius must be positive");
  }
  radius_ = radius;
  updateFromRadius();
}

void Circle::setFerence(double ference) {
  if (ference <= 0) {
    throw std::invalid_argument("Circumference must be positive");
  }
  ference_ = ference;
  updateFromFerence();
}

void Circle::setArea(double area) {
  if (area <= 0) {
    throw std::invalid_argument("Area must be positive");
  }
  area_ = area;
  updateFromArea();
}

double Circle::getRadius() const { return radius_; }

double Circle::getFerence() const { return ference_; }

double Circle::getArea() const { return area_; }

void Circle::updateFromRadius() {
  ference_ = 2 * PI * radius_;
  area_ = PI * radius_ * radius_;
}

void Circle::updateFromFerence() {
  radius_ = ference_ / (2 * PI);
  area_ = PI * radius_ * radius_;
}

void Circle::updateFromArea() {
  radius_ = std::sqrt(area_ / PI);
  ference_ = 2 * PI * radius_;
}
