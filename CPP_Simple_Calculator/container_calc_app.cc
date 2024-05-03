#include "container_calc_app.h"

namespace s21 {

ContainerCalcApp::ContainerCalcApp() {
  model_ = new CalcModelFacade;

  graph_controller_ = new GraphController(model_);
  graph_view_ = new GraphView(graph_controller_, model_);

  math_controller_ = new MathController(model_);

  math_view_ = new MathView(math_controller_, model_, graph_view_);

  model_->RegisterObserver(
      static_cast<s21::GraphObserverErrorInterface*>(math_view_));

  credit_controller_ = new s21::CreditController(model_);
  credit_view_ = new CreditView(credit_controller_, model_);

  deposit_controller_ = new s21::DepositController(model_);
  deposit_view_ = new DepositView(deposit_controller_, model_);

  main_view_ = new s21::MainView(math_view_, credit_view_, deposit_view_);
}

ContainerCalcApp::~ContainerCalcApp() {
  model_->RemoveObserver(
      static_cast<s21::GraphObserverErrorInterface*>(math_view_));

  delete main_view_;
  delete deposit_controller_;
  delete credit_controller_;
  delete graph_controller_;
  delete math_controller_;
  delete model_;
}

void ContainerCalcApp::Init() { main_view_->show(); }

}  // namespace s21
