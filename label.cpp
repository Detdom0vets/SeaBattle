#include "label.h"
#include "utilities.h"

label::label()
{

}

label::label(double x, double y, double w, double h, const QString &text)
    : m_width(w),
      m_height(h),
      m_text(text)
{
    m_font = computeFontForText(boundingRect().toRect(), Qt::AlignCenter, m_text, 0.95);
    setPos(x, y);
}

void label::setText(const QString &text)
{
    m_text = text;
    m_font = computeFontForText(boundingRect().toRect(), Qt::AlignCenter, m_text, 0.95);
    update();
}
