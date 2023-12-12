#include "graph_model.h"

#include <cmath>    // isinf | isnan | abs
#include <limits>   // quiet_NaN
#include <utility>  // swap | make_pair

#include "../../helpers/math_helpers.h"

namespace s21 {

GraphCalcModel::GraphCalcModel()
    : math_calc_model_(new MathCalcModel),
      x_begin_(-100),
      x_end_(100),
      y_begin_(0),
      y_end_(0),
      y_scale_auto_(true),
      points_({}) {}

GraphCalcModel::~GraphCalcModel() { delete math_calc_model_; }

void GraphCalcModel::CalculateGraph() {
  ResetModelResults();
  NormalizeXRange();
  NormalizeYRange();
  CheckModelData();
  CalculateHandle();
}

void GraphCalcModel::ResetModelResults() noexcept { points_.clear(); }

void GraphCalcModel::NormalizeXRange() noexcept {
  if (y_begin_ > y_end_) {
    std::swap(y_begin_, y_end_);
  }
}

void GraphCalcModel::NormalizeYRange() noexcept {
  if (x_begin_ > x_end_) {
    std::swap(x_begin_, x_end_);
  }
}

void GraphCalcModel::CheckModelData() const {
  if (x_begin_ == x_end_ || x_begin_ < kMinX || x_end_ > kMaxX) {
    throw S21WrongXGraphException("Incorrect XStart - XEnd");
  }

  if (y_scale_auto_ == false && (y_begin_ < kMinY || y_end_ > kMaxY)) {
    throw S21WrongYGraphException("Incorrect YStart - YEnd");
  }
}

void GraphCalcModel::CalculateHandle() {
  double y_min = 0.0, y_max = 0.0;

  CalculatePoints(x_begin_, x_end_, kNumPointsAll, y_min, y_max, kNumOfCalc);
  SetYRange(y_min, y_max);
}

void GraphCalcModel::CalculatePoints(double x_begin, double x_end,
                                     double num_points, double &y_min,
                                     double &y_max, int num_of_calc_points) {
  double shift = (x_end - x_begin) / num_points;
  int points = num_points;
  bool first_iteration = true;
  double y_last_value = 0.0;
  double x_last_value = 0.0;

  for (double x_value_it = x_begin; points >= 0; x_value_it += shift) {
    double x_value;

    if (x_end - x_begin > 1 || std::abs(x_value_it) < (1e-7 / kNumPointsAll)) {
      x_value = math_helpers::Round(x_value_it, 7);
    } else {
      x_value = x_value_it;
    }

    math_calc_model_->set_x_value(x_value);
    math_calc_model_->Calculate();
    double y_value = math_calc_model_->get_result();

    if (std::isinf(y_value)) {
      y_value = std::numeric_limits<double>::quiet_NaN();
    }

    if (!first_iteration && IsFunctionBreakPoint(y_last_value, y_value)) {
      if (num_of_calc_points > 0) {
        CalculatePoints(x_last_value, x_value, kNumPointsPre, y_min, y_max,
                        num_of_calc_points - 1);
      } else {
        (*(--points_.end())).second = std::numeric_limits<double>::quiet_NaN();
      }
    }

    points_.push_back(std::make_pair(x_value, y_value));
    --points;

    if (y_value < y_min && !std::isinf(y_value) && !std::isnan(y_value)) {
      y_min = y_value;
    }

    if (y_value > y_max && !std::isinf(y_value) && !std::isnan(y_value)) {
      y_max = y_value;
    }

    first_iteration = false;
    y_last_value = y_value;
    x_last_value = x_value;
  }
}

bool GraphCalcModel::IsFunctionBreakPoint(double last,
                                          double current) const noexcept {
  return (std::isnan(last) && !std::isnan(current)) ||
         (std::isnan(current) && !std::isnan(last)) ||
         (((last < 0 && current > 0) || (last > 0 && current < 0)) &&
          (std::abs(last - current) > 40)) ||
         (!std::isinf(last / current) && std::abs(last / current) > 1e20);
}

void GraphCalcModel::SetYRange(double y_min, double y_max) noexcept {
  if (y_scale_auto_ == true) {
    if (y_min == 0.0 && y_max == 0.0) {
      y_min = -5.0;
      y_max = 5.0;
    } else {
      if (y_min < -1e6) {
        y_min = -1e6;
      } else {
        y_min *= 1.05;
      }
      if (y_max > 1e6) {
        y_max = 1e6;
      } else {
        y_max *= 1.05;
      }
    }

    y_begin_ = y_min;
    y_end_ = y_max;
  }
}

}  // namespace s21
