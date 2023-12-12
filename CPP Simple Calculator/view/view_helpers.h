#ifndef S21_SMART_CALC_V20_VIEW_VIEW_QT_HELPERS_H_
#define S21_SMART_CALC_V20_VIEW_VIEW_QT_HELPERS_H_

// #include <QWidget>
#include <QDateEdit>
#include <QLayout>
#include <QString>

namespace s21 {
namespace view_helpers {

void SetupDateEdit(QDateEdit *date_edit);
QLayout *FindParentLayout(QWidget *widget, QLayout *parent_layout);
QLayout *FindParentLayout(QWidget *widget);
QString DoubleToQString(double number, double precision);

}  // namespace view_helpers
}  // namespace s21

#endif  // S21_SMART_CALC_V20_VIEW_VIEW_QT_HELPERS_H_
