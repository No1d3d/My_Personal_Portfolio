#include "view_helpers.h"

#include <QCalendarWidget>

#include "../helpers/math_helpers.h"

namespace s21 {
namespace view_helpers {

void SetupDateEdit(QDateEdit *date_edit) {
  date_edit->setDisplayFormat("dd.MM.yyyy");
  date_edit->setCalendarPopup(true);
  date_edit->calendarWidget()->setLocale(QLocale("ru_RU"));
  QDate date = QDate::currentDate();
  date_edit->setDate(date);
}

QLayout *FindParentLayout(QWidget *widget, QLayout *parent_layout) {
  for (QObject *object : parent_layout->children()) {
    QLayout *layout = qobject_cast<QLayout *>(object);
    if (layout != nullptr) {
      if (layout->indexOf(widget) > -1) {
        return layout;
      } else if (!layout->children().isEmpty()) {
        layout = FindParentLayout(widget, layout);
        if (layout != nullptr) {
          return layout;
        }
      }
    }
  }
  return nullptr;
}

QLayout *FindParentLayout(QWidget *widget) {
  if (widget->parentWidget() != nullptr)
    if (widget->parentWidget()->layout() != nullptr)
      return FindParentLayout(widget, widget->parentWidget()->layout());
  return nullptr;
}

QString DoubleToQString(double number, double precision) {
  return QString::fromStdString(math_helpers::RemoveTrailingZeros(
      QString::number(number, 'f', precision).toStdString()));
}

}  // namespace view_helpers
}  // namespace s21
