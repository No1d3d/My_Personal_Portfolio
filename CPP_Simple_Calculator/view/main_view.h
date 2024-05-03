#ifndef S21_SMART_CALC_V20_VIEW_MAIN_VIEW_H_
#define S21_SMART_CALC_V20_VIEW_MAIN_VIEW_H_

#include <QMainWindow>

#include "credit_view.h"
#include "deposit_view.h"
#include "math_view.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainView;
}
QT_END_NAMESPACE

namespace s21 {

class MainView final : public QMainWindow {
  Q_OBJECT

 public:
  MainView(MathView* math_view, CreditView* credit_view,
           DepositView* deposit_view, QWidget* parent = nullptr);
  ~MainView();
  // void closeEvent(QCloseEvent* event);

 private:
  Ui::MainView* ui_;
};

}  // namespace s21

#endif  // S21_SMART_CALC_V20_VIEW_MAIN_VIEW_H_
