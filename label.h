#ifndef LABEL_H
#define LABEL_H

#include <QtWidgets>

class label : public QGraphicsItem
{

    double m_width;
    double m_height;
    QString m_text;
    QFont m_font;
public:
    label();
    label(const QString &text);
    label(double x, double y, double w, double h, const QString &text);
    void setText(const QString &text);
};

#endif // LABEL_H
