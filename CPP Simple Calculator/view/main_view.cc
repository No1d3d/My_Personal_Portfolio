#include "main_view.h"

#include "../ui/ui_main_view.h"

namespace s21 {

MainView::MainView(MathView* math_view, CreditView* credit_view,
                   DepositView* deposit_view, QWidget* parent)
    : QMainWindow(parent), ui_(new Ui::MainView) {
  ui_->setupUi(this);

  if (math_view) {
    math_view->setObjectName(QString::fromUtf8("math_view"));
    ui_->verticalLayout_6->addWidget(math_view);
  }

  if (credit_view) {
    credit_view->setObjectName(QString::fromUtf8("credit_view"));
    ui_->verticalLayout_7->addWidget(credit_view);
  }

  if (deposit_view) {
    deposit_view->setObjectName(QString::fromUtf8("deposit_view"));
    ui_->verticalLayout_8->addWidget(deposit_view);
  }
}

MainView::~MainView() { delete ui_; }

}  // namespace s21
