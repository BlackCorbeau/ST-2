// Copyright 2025 UNN-CS Team

#include <gtest/gtest.h>
#include <cmath>

#include "circle.h"
#include "tasks.h"

const double PI = 3.14159265358979323846;
const double EPSILON = 1e-10;
const double EPSILON_LARGER = 1e-9;
const double EPSILON_VSMALL = 1e-9;

TEST(CircleTest, ConstructorPositiveRadius) {
    Circle c(5.0);
    EXPECT_DOUBLE_EQ(c.getRadius(), 5.0);
    EXPECT_DOUBLE_EQ(c.getFerence(), 2 * PI * 5.0);
    EXPECT_DOUBLE_EQ(c.getArea(), PI * 25.0);
}

TEST(CircleTest, ConstructorZeroRadius) {
    EXPECT_THROW(Circle c(0.0), std::invalid_argument);
}

TEST(CircleTest, ConstructorNegativeRadius) {
    EXPECT_THROW(Circle c(-5.0), std::invalid_argument);
}

TEST(CircleTest, SetRadiusValid) {
    Circle c(1.0);
    c.setRadius(3.0);
    EXPECT_DOUBLE_EQ(c.getRadius(), 3.0);
    EXPECT_DOUBLE_EQ(c.getFerence(), 2 * PI * 3.0);
    EXPECT_DOUBLE_EQ(c.getArea(), PI * 9.0);
}

TEST(CircleTest, SetRadiusInvalid) {
    Circle c(1.0);
    EXPECT_THROW(c.setRadius(0.0), std::invalid_argument);
    EXPECT_THROW(c.setRadius(-2.0), std::invalid_argument);
}

TEST(CircleTest, SetFerenceValid) {
    Circle c(1.0);
    double new_ference = 10.0;
    c.setFerence(new_ference);
    double expected_radius = new_ference / (2 * PI);
    EXPECT_NEAR(c.getRadius(), expected_radius, EPSILON);
    EXPECT_DOUBLE_EQ(c.getFerence(), new_ference);
    EXPECT_NEAR(c.getArea(), PI * expected_radius *
        expected_radius, EPSILON);
}

TEST(CircleTest, SetFerenceInvalid) {
    Circle c(1.0);
    EXPECT_THROW(c.setFerence(0.0), std::invalid_argument);
    EXPECT_THROW(c.setFerence(-5.0), std::invalid_argument);
}

TEST(CircleTest, SetAreaValid) {
    Circle c(1.0);
    double new_area = 50.0;
    c.setArea(new_area);
    double expected_radius = std::sqrt(new_area / PI);
    EXPECT_NEAR(c.getRadius(), expected_radius, EPSILON);
    EXPECT_NEAR(c.getArea(), new_area, EPSILON);
    EXPECT_NEAR(c.getFerence(), 2 * PI * expected_radius,
        EPSILON);
}

TEST(CircleTest, SetAreaInvalid) {
    Circle c(1.0);
    EXPECT_THROW(c.setArea(0.0), std::invalid_argument);
    EXPECT_THROW(c.setArea(-10.0), std::invalid_argument);
}

TEST(CircleTest, ConsistencyAfterMultipleSets) {
    Circle c(2.0);
    double original_radius = c.getRadius();
    double original_ference = c.getFerence();
    double original_area = c.getArea();

    c.setFerence(original_ference * 2);
    EXPECT_GT(c.getRadius(), original_radius);

    c.setArea(original_area);
    EXPECT_NEAR(c.getArea(), original_area, EPSILON);
    EXPECT_NEAR(c.getRadius(), original_radius, EPSILON);
    EXPECT_NEAR(c.getFerence(), original_ference, EPSILON);
}

TEST(CircleTest, PrecisionForLargeValues) {
    Circle c(1e6);
    EXPECT_NEAR(c.getFerence(), 2 * PI * 1e6, 1e-6);
    EXPECT_NEAR(c.getArea(), PI * 1e12, 1e-6);
}

TEST(CircleTest, PrecisionForSmallValues) {
    Circle c(1e-6);
    EXPECT_NEAR(c.getFerence(), 2 * PI * 1e-6, 1e-16);
    EXPECT_NEAR(c.getArea(), PI * 1e-12, 1e-22);
}

TEST(EarthRopeTest, StandardEarthRadius) {
    double gap = calculateGap(6378100.0, 1.0);
    EXPECT_NEAR(gap, 1.0 / (2 * PI), EPSILON_LARGER);
}

TEST(EarthRopeTest, DifferentEarthRadius) {
    double radius = 1000.0;
    double gap = calculateGap(radius, 1.0);
    EXPECT_NEAR(gap, 1.0 / (2 * PI), EPSILON_LARGER);
}

TEST(EarthRopeTest, DifferentAddedLength) {
    double radius = 6378100.0;
    double added = 2.0;
    double gap = calculateGap(radius, added);
    EXPECT_NEAR(gap, added / (2 * PI), EPSILON_LARGER);
}

TEST(EarthRopeTest, VeryLargeAddedLength) {
    double gap = calculateGap(6378100.0, 1000.0);
    EXPECT_NEAR(gap, 1000.0 / (2 * PI), EPSILON_LARGER);
}

TEST(EarthRopeTest, VerySmallAddedLength) {
    double gap = calculateGap(6378100.0, 0.001);
    EXPECT_NEAR(gap, 0.001 / (2 * PI), EPSILON_VSMALL);
}

TEST(PoolTest, StandardValues) {
    PoolCost costs = calculatePoolCosts(3.0, 1.0, 1000.0,
        2000.0);

    double expected_walkway_area = PI * 7.0;
    double expected_walkway_cost = expected_walkway_area *
        1000.0;
    double expected_fence_length = 2 * PI * 4.0;
    double expected_fence_cost = expected_fence_length *
        2000.0;

    EXPECT_NEAR(costs.walkway_cost, expected_walkway_cost,
        EPSILON);
    EXPECT_NEAR(costs.fence_cost, expected_fence_cost,
        EPSILON);
}

TEST(PoolTest, ZeroWidthWalkway) {
    PoolCost costs = calculatePoolCosts(3.0, 0.0, 1000.0,
        2000.0);

    EXPECT_NEAR(costs.walkway_cost, 0.0, EPSILON);
    EXPECT_NEAR(costs.fence_cost, 2 * PI * 3.0 * 2000.0,
        EPSILON);
}

TEST(PoolTest, DifferentPoolRadius) {
    double radius = 5.0;
    PoolCost costs = calculatePoolCosts(radius, 1.0, 1000.0,
        2000.0);

    double expected_walkway_area = PI *
        ((radius + 1) * (radius + 1) - radius * radius);
    EXPECT_NEAR(costs.walkway_cost, expected_walkway_area *
        1000.0, EPSILON);
    EXPECT_NEAR(costs.fence_cost, 2 * PI * (radius + 1) *
        2000.0, EPSILON);
}

TEST(PoolTest, DifferentConcretePrice) {
    double concrete_price = 1500.0;
    PoolCost costs = calculatePoolCosts(3.0, 1.0,
        concrete_price, 2000.0);

    double expected_walkway_area = PI * 7.0;
    EXPECT_NEAR(costs.walkway_cost, expected_walkway_area *
        concrete_price, EPSILON);
}

TEST(PoolTest, DifferentFencePrice) {
    double fence_price = 2500.0;
    PoolCost costs = calculatePoolCosts(3.0, 1.0, 1000.0,
        fence_price);

    double expected_fence_length = 2 * PI * 4.0;
    EXPECT_NEAR(costs.fence_cost, expected_fence_length *
        fence_price, EPSILON);
}

TEST(PoolTest, LargeWalkwayWidth) {
    PoolCost costs = calculatePoolCosts(3.0, 10.0, 1000.0,
        2000.0);

    double expected_walkway_area = PI *
        (13.0 * 13.0 - 9.0);
    EXPECT_NEAR(costs.walkway_cost, expected_walkway_area *
        1000.0, EPSILON);
    EXPECT_NEAR(costs.fence_cost, 2 * PI * 13.0 * 2000.0,
        EPSILON);
}

TEST(PoolTest, VerySmallPool) {
    PoolCost costs = calculatePoolCosts(0.1, 1.0, 1000.0,
        2000.0);

    double expected_walkway_area = PI *
        (1.1 * 1.1 - 0.1 * 0.1);
    EXPECT_NEAR(costs.walkway_cost, expected_walkway_area *
        1000.0, EPSILON);
    EXPECT_NEAR(costs.fence_cost, 2 * PI * 1.1 * 2000.0,
        EPSILON);
}

TEST(PoolTest, ZeroPrices) {
    PoolCost costs = calculatePoolCosts(3.0, 1.0, 0.0, 0.0);
    EXPECT_NEAR(costs.walkway_cost, 0.0, EPSILON);
    EXPECT_NEAR(costs.fence_cost, 0.0, EPSILON);
}
