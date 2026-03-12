// Copyright 2022 UNN-CS
#include "tasks.h"

#include <cmath>

#include "circle.h"

double calculateGap(double earth_radius, double added_length) {
    Circle earth(earth_radius);
    double earth_ference = earth.getFerence();
    double new_ference = earth_ference + added_length;
    Circle new_circle(earth_radius);
    new_circle.setFerence(new_ference);
    return new_circle.getRadius() - earth_radius;
}

PoolCost calculatePoolCosts(double pool_radius,
                           double walkway_width,
                           double concrete_price,
                           double fence_price) {
    PoolCost costs;
    Circle pool(pool_radius);
    Circle pool_with_walkway(pool_radius + walkway_width);
    double walkway_area = pool_with_walkway.getArea() - pool.getArea();
    costs.walkway_cost = walkway_area * concrete_price;
    double fence_length = pool_with_walkway.getFerence();
    costs.fence_cost = fence_length * fence_price;
    return costs;
}
