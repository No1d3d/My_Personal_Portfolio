#ifndef S21_SMART_CALC_V20_VIEW_DEPOSIT_VIEW_H_
#define S21_SMART_CALC_V20_VIEW_DEPOSIT_VIEW_H_

#include <QBoxLayout>
#include <QWidget>

#include "../interfaces/deposit_controller_interface.h"
#include "../interfaces/deposit_model_public_interface.h"
#include "../interfaces/observer/observer_deposit_interfaces.h"

namespace Ui {
class DepositView;
}

namespace s21 {

class DepositView final : public QWidget,
                          public DepositObserverUpdateInterface,
                          public DepositObserverErrorInterface {
  Q_OBJECT

 public:
  explicit DepositView(DepositControllerInterface* controller,
                       DepositModelPublicInterface* model,
                       QWidget* parent = nullptr);
  DepositView(const DepositView& other) = delete;
  DepositView(DepositView&& other) = delete;
  DepositView& operator=(const DepositView& other) = delete;
  DepositView& operator=(DepositView&& other) = delete;
  ~DepositView();

  void OnUpdate() override;
  void OnError(const std::pair<std::string, std::string>& error) override;

 private:
  void SetupDepositButtons();
  void UpdateInputFieldsFromModel();
  void UpdateResultFromModel();
  void ResetResult();
  bool OperationsReplenishmentHandle();
  bool OperationsWithdrawalHandle();
  void AddOperationLine(QBoxLayout* layout);

  void SetDepositSumError(const QString& error_text);
  void SetDepositMonthsError(const QString& error_text);
  void SetDepositInterestError(const QString& error_text);
  void SetDepositTaxError(const QString& error_text);
  void SetDepositDateStartError(const QString& error_text);
  void SetDepositAddMoneyError(const QString& error_text);
  void SetDepositSubMoneyError(const QString& error_text);

  void ResetDepositSumError();
  void ResetDepositMonthsError();
  void ResetDepositInterestError();
  void ResetDepositTaxError();
  void ResetDepositDateStartError();
  void ResetAllErrors();

  Ui::DepositView* ui_;
  DepositControllerInterface* controller_;
  DepositModelPublicInterface* model_;

 private slots:
  void HandleDepositButton();
  void AddOperationReplenishment();
  void AddOperationWithdrawal();
  void DeleteOperationLine();

  void HandleDepositSumChanged();
  void HandleDepositMonthsChanged();
  void HandleDepositInterestChanged();
  void HandleDepositTaxChanged();
  void HandleDepositDateStartChanged();
};

}  // namespace s21

#endif  // S21_SMART_CALC_V20_VIEW_DEPOSIT_VIEW_H_
