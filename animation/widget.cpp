#include "widget.h"
#include "ui_widget.h"

#include <QWidget>
#include <QDebug>
#include <QPixmap>
#include <QHBoxLayout>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->installEventFilter(this);
    ui->lineEdit->installEventFilter(this);

    m_queryWid = new QWidget(ui->lineEdit);
    m_queryWid->setFocusPolicy(Qt::NoFocus);

    m_queryIcon = new QLabel(m_queryWid);
    QPixmap pixmap = loadSvg(QString(":/search.svg"),"blue");
    m_queryIcon->setPixmap(pixmap);
    m_queryIcon->setStyleSheet("background:transparent");
    m_queryIcon->setFixedSize(pixmap.size());

    m_queryText = new QLabel(m_queryWid);
    m_queryText->setText(tr("Search"));
    m_queryText->setStyleSheet("background:transparent;color:#626c6e;");


    QHBoxLayout* queryWidLayout = new QHBoxLayout;
    queryWidLayout->setContentsMargins(4,4,0,0);
    queryWidLayout->setAlignment(Qt::AlignJustify);
    queryWidLayout->setSpacing(0);
    m_queryWid->setLayout(queryWidLayout);

    queryWidLayout->addWidget(m_queryIcon);
    queryWidLayout->addWidget(m_queryText);

    m_queryWid->setGeometry(QRect((ui->lineEdit->width() - (m_queryIcon->width()+m_queryText->width()+10))/2,0,
                                        m_queryIcon->width()+m_queryText->width()+10,(ui->lineEdit->height()+36)/2));
    m_queryWid->show();

    m_animation= new QPropertyAnimation(m_queryWid, "geometry", this);
    m_animation->setDuration(100);
    connect(m_animation,&QPropertyAnimation::finished,this,&Widget::animationFinishedSlot);
}

Widget::~Widget()
{
    delete ui;
}

bool Widget::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui->lineEdit) {
        if (event->type() == QEvent::FocusIn) {
            if (ui->lineEdit->text().isEmpty()) {
                m_animation->stop();
                m_animation->setStartValue(QRect((ui->lineEdit->width()-(m_queryIcon->width()+m_queryText->width()+10))/2,0,
                                                 m_queryIcon->width()+m_queryText->width()+30,(ui->lineEdit->height()+36)/2));
                m_animation->setEndValue(QRect(0,0,
                                               m_queryIcon->width()+5,(ui->lineEdit->height()+36)/2));
                m_animation->setEasingCurve(QEasingCurve::OutQuad);
                m_animation->start();
                ui->lineEdit->setTextMargins(30,1,0,1);
            }
            m_isSearching=true;

        } else if (event->type() == QEvent::FocusOut) {
            if (ui->lineEdit->text().isEmpty()) {
                if (m_isSearching) {
                    m_queryText->adjustSize();
                    m_animation->setStartValue(QRect(0,0,
                                                     m_queryIcon->width()+5,(ui->lineEdit->height()+36)/2));
                    m_animation->setEndValue(QRect((ui->lineEdit->width() - (m_queryIcon->width()+m_queryText->width()+10))/2,0,
                                                   m_queryIcon->width()+m_queryText->width()+30,(ui->lineEdit->height()+36)/2));
                    m_animation->setEasingCurve(QEasingCurve::InQuad);
                    m_animation->start();
                }
            }
            m_isSearching=false;
        }
    }
    return QObject::eventFilter(watched, event);
}

void Widget::animationFinishedSlot()
{
    if(m_isSearching) {
        m_queryWid->layout()->removeWidget(m_queryText);
        m_queryText->setParent(nullptr);
        ui->lineEdit->setTextMargins(30,1,0,1);
    } else {
        m_queryWid->layout()->addWidget(m_queryText);
    }
}

QPixmap Widget::loadSvg(const QString &path, const QString color, int size)
{
    int origSize = size;
    const auto ratio = qApp->devicePixelRatio();
    if ( 2 == ratio) {
        size += origSize;
    } else if (3 == ratio) {
        size += origSize;
    }
    QPixmap pixmap(size, size);
    QSvgRenderer renderer(path);
    pixmap.fill(Qt::transparent);

    QPainter painter;
    painter.begin(&pixmap);
    renderer.render(&painter);
    painter.end();

    pixmap.setDevicePixelRatio(ratio);
    return drawSymbolicColoredPixmap(pixmap, color);
}

QPixmap Widget::drawSymbolicColoredPixmap(const QPixmap &source, QString cgColor)
{
    QImage img = source.toImage();
    for (int x = 0; x < img.width(); x++) {
        for (int y = 0; y < img.height(); y++) {
            auto color = img.pixelColor(x, y);
            if (color.alpha() > 0) {
                if ( "white" == cgColor) {
                    color.setRed(255);
                    color.setGreen(255);
                    color.setBlue(255);
                    img.setPixelColor(x, y, color);
                } else if( "black" == cgColor) {
                    color.setRed(0);
                    color.setGreen(0);
                    color.setBlue(0);
                    img.setPixelColor(x, y, color);
                } else if ("gray"== cgColor) {
                    color.setRed(152);
                    color.setGreen(163);
                    color.setBlue(164);
                    img.setPixelColor(x, y, color);
                } else if ("blue" == cgColor){
                    color.setRed(61);
                    color.setGreen(107);
                    color.setBlue(229);
                    img.setPixelColor(x, y, color);
                } else {
                    return source;
                }
            }
        }
    }
    return QPixmap::fromImage(img);
}


