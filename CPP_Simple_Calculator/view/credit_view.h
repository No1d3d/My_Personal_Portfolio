#ifndef S21_SMART_CALC_V20_VIEW_CREDIT_VIEW_H_
#define S21_SMART_CALC_V20_VIEW_CREDIT_VIEW_H_

#include <QWidget>

#include "../interfaces/credit_controller_interface.h"
#include "../interfaces/credit_model_public_interface.h"
#include "../interfaces/observer/observer_credit_interfaces.h"

namespace Ui {
class CreditView;
}

namespace s21 {

class CreditView final : public QWidget,
                         public CreditObserverUpdateInterface,
                         public CreditObserverErrorInterface {
  Q_OBJECT

 public:
  explicit CreditView(CreditControllerInterface* controller,
                      CreditModelPublicInterface* model,
                      QWidget* parent = nullptr);
  CreditView(const CreditView& other) = delete;
  CreditView(CreditView&& other) = delete;
  CreditView& operator=(const CreditView& other) = delete;
  CreditView& operator=(CreditView&& other) = delete;
  ~CreditView();

  void OnUpdate() override;
  void OnError(const std::pair<std::string, std::string>& error) override;

 private:
  void SetupCreditButtons();
  void UpdateInputFieldsFromModel();
  void UpdateResultFromModel();
  void ResetResult();
  void SetCreditSumError(const QString& error_text);
  void SetCreditMonthsError(const QString& error_text);
  void SetCreditInterestError(const QString& error_text);

  void ResetCreditSumError();
  void ResetCreditMonthsError();
  void ResetCreditInterestError();
  void ResetAllErrors();

  Ui::CreditView* ui_;
  CreditControllerInterface* controller_;
  CreditModelPublicInterface* model_;

 private slots:
  void HandleCreditButton();
  void HandleCreditSumChanged();
  void HandleCreditMonthsChanged();
  void HandleCreditInterestChanged();
};

}  // namespace s21

#endif  // S21_SMART_CALC_V20_VIEW_CREDIT_VIEW_H_
