#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QEvent>
#include <QPropertyAnimation>
#include <QLabel>
#include <QPixmap>
#include <QSvgRenderer>
#include <QPainter>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    bool eventFilter(QObject *watched, QEvent *event);

private:
    void animationFinishedSlot();

    QPixmap loadSvg(const QString &path, const QString color, int size = 16);
    QPixmap drawSymbolicColoredPixmap(const QPixmap &source, QString cgColor);

private:
    Ui::Widget *ui;

    QPropertyAnimation *m_animation;
    QWidget           *m_queryWid   = nullptr;
    QLabel            *m_queryIcon;
    QLabel            *m_queryText  = nullptr;

    bool m_isSearching = false;
};
#endif // WIDGET_H
