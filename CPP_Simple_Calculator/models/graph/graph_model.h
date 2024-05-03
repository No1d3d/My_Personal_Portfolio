#ifndef S21_SMART_CALC_V20_MODELS_GRAPH_GRAPH_MODEL_H_
#define S21_SMART_CALC_V20_MODELS_GRAPH_GRAPH_MODEL_H_

#include <vector>

#include "../calc_exception.h"
#include "./../math/math_model.h"

namespace s21 {

class GraphCalcModel final {
 public:
  const double kMinX = -1000000;
  const double kMaxX = 1000000;
  const double kMinY = -1000000;
  const double kMaxY = 1000000;

  GraphCalcModel();
  GraphCalcModel(const GraphCalcModel& other) = delete;
  GraphCalcModel(GraphCalcModel&& other) = delete;
  GraphCalcModel& operator=(const GraphCalcModel& other) = delete;
  GraphCalcModel& operator=(GraphCalcModel&& other) = delete;
  ~GraphCalcModel();

  void set_x_begin(double new_x) noexcept { x_begin_ = new_x; }
  void set_x_end(double new_x) noexcept { x_end_ = new_x; }
  void set_y_begin(double new_y) noexcept { y_begin_ = new_y; }
  void set_y_end(double new_y) noexcept { y_end_ = new_y; }
  void set_math_expression(const std::string& new_expression) {
    math_calc_model_->set_math_expression(new_expression);
  }
  void set_y_scale_auto(bool flag) noexcept { y_scale_auto_ = flag; }

  double get_x_begin() const noexcept { return x_begin_; }
  double get_x_end() const noexcept { return x_end_; }
  double get_y_begin() const noexcept { return y_begin_; }
  double get_y_end() const noexcept { return y_end_; }
  bool get_y_scale_auto() const noexcept { return y_scale_auto_; }
  const std::vector<std::pair<double, double>>& get_points() { return points_; }

  void CalculateGraph();

 private:
  const int kNumPointsAll = 20000;
  const int kNumPointsPre = 100;
  const int kNumOfCalc = 3;

  void ResetModelResults() noexcept;
  void NormalizeXRange() noexcept;
  void NormalizeYRange() noexcept;
  void CheckModelData() const;
  void CalculateHandle();
  void CalculatePoints(double x_begin, double x_end, double num_points,
                       double& y_min, double& y_max, int num_of_calc_points);
  bool IsFunctionBreakPoint(double last, double current) const noexcept;
  void SetYRange(double y_min, double y_max) noexcept;

  MathCalcModel* math_calc_model_;
  double x_begin_;
  double x_end_;
  double y_begin_;
  double y_end_;
  bool y_scale_auto_;

  std::vector<std::pair<double, double>> points_;
};

}  // namespace s21

#endif  // S21_SMART_CALC_V20_MODELS_GRAPH_GRAPH_MODEL_H_