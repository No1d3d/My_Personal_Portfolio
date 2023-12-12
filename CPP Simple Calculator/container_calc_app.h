#ifndef S21_SMART_CALC_V20_CONTAINER_CALC_APP_H_
#define S21_SMART_CALC_V20_CONTAINER_CALC_APP_H_

#include "calc_model_facade.h"
#include "controller/credit_controller.h"
#include "controller/deposit_controller.h"
#include "controller/graph_controller.h"
#include "controller/math_controller.h"
#include "interfaces/observer/observer_graph_interfaces.h"
#include "view/credit_view.h"
#include "view/deposit_view.h"
#include "view/graph_view.h"
#include "view/main_view.h"
#include "view/math_view.h"

namespace s21 {

class ContainerCalcApp final {
 public:
  ContainerCalcApp();
  ContainerCalcApp(const ContainerCalcApp& other) = delete;
  ContainerCalcApp(ContainerCalcApp&& other) = delete;
  ContainerCalcApp& operator=(const ContainerCalcApp& other) = delete;
  ContainerCalcApp& operator=(ContainerCalcApp&& other) = delete;
  ~ContainerCalcApp();

  void Init();

 private:
  CalcModelFacade* model_;
  GraphController* graph_controller_;
  GraphView* graph_view_;
  MathController* math_controller_;
  MathView* math_view_;
  CreditController* credit_controller_;
  CreditView* credit_view_;
  DepositController* deposit_controller_;
  DepositView* deposit_view_;
  MainView* main_view_;
};

}  // namespace s21

#endif  // S21_SMART_CALC_V20_CONTAINER_CALC_APP_H_