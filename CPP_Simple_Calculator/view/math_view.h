#ifndef S21_SMART_CALC_V20_VIEW_MATH_VIEW_H_
#define S21_SMART_CALC_V20_VIEW_MATH_VIEW_H_

#include <QWidget>

#include "../interfaces/math_controller_interface.h"
#include "../interfaces/math_model_public_interface.h"
#include "../interfaces/observer/observer_math_interfaces.h"
#include "graph_view.h"

namespace Ui {
class MathView;
}

namespace s21 {

class MathView final : public QWidget,
                       public MathObserverUpdateInterface,
                       public MathObserverErrorInterface,
                       public GraphObserverErrorInterface {
  Q_OBJECT

 public:
  explicit MathView(MathControllerInterface* controller,
                    MathModelPublicInterface* model, GraphView* graph_view,
                    QWidget* parent = nullptr);
  MathView(const MathView& other) = delete;
  MathView(MathView&& other) = delete;
  MathView& operator=(const MathView& other) = delete;
  MathView& operator=(MathView&& other) = delete;
  ~MathView();

  void OnUpdate() override;
  void OnError(const std::pair<std::string, std::string>& error) override;

 private:
  void SetupButtons();
  QString GetViewMathExpression();
  void SetCalcResult(double result);
  void SetCalcResult(const QString& result);
  void SetXValueError(const QString& error_text);
  void SetInputValueError(const QString& error_text);
  void ResetXValueError();
  void ResetInputValueError();
  void ResetAllErrors();

  Ui::MathView* ui_;
  MathControllerInterface* controller_;
  MathModelPublicInterface* model_;
  GraphView* graph_view_;

 private slots:
  void HandleCalcButton();
  void HandleGraphButton();

  void HandleClearButton();
  void HandlePointButton();
  void HandleBackspaceButton();
  void HandleButtonMod();
  void HandleButtonDiv();
  void HandleButtonMul();
  void HandleButtonSub();
  void HandleButtonAdd();
  void HandleButtonLBracket();
  void HandleButtonRBracket();
  void HandleButtonPow();
  void HandleButtonCos();
  void HandleButtonSin();
  void HandleButtonTan();
  void HandleButtonSqrt();
  void HandleButtonAcos();
  void HandleButtonAtan();
  void HandleButtonAsin();
  void HandleButtonLn();
  void HandleButtonPi();
  void HandleButtonE();
  void HandleButtonX();
  void HandleButtonLog();
  void HandleButtonNum0();
  void HandleButtonNum1();
  void HandleButtonNum2();
  void HandleButtonNum3();
  void HandleButtonNum4();
  void HandleButtonNum5();
  void HandleButtonNum6();
  void HandleButtonNum7();
  void HandleButtonNum8();
  void HandleButtonNum9();
  void HandleButtonUnaryMinus();

  void HandleXEditChanged();
  void HandleInputChanged();
};

}  // namespace s21

#endif  // S21_SMART_CALC_V20_VIEW_MATH_VIEW_H_
