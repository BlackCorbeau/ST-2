// Copyright 2022 UNN-CS
#ifndef INCLUDE_TASKS_H_
#define INCLUDE_TASKS_H_

struct PoolCost {
  double walkway_cost;
  double fence_cost;
};

double calculateGap(double earth_radius = 6378100.0, double added_length = 1.0);

PoolCost calculatePoolCosts(double pool_radius = 3.0,
                            double walkway_width = 1.0,
                            double concrete_price = 1000.0,
                            double fence_price = 2000.0);

#endif // INCLUDE_TASKS_H_
