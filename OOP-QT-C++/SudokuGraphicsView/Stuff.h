//
// Created by User on 08/07/2023.
//

#pragma once
#include "QDebug"
#include "QGraphicsScene"
#include "QGraphicsRectItem"
#include "QFont"


/*class SudokuSquare :public QGraphicsRectItem {
public:
    SudokuSquare(qreal x, qreal y, qreal width, qreal height, QGraphicsItem* parent = nullptr)
            : QGraphicsRectItem(x, y, width, height, parent) {}

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override {
        QGraphicsRectItem::mousePressEvent(event);
    }
};*/


class Button :public QObject, public QGraphicsRectItem {
private:
    Q_OBJECT
    QGraphicsTextItem m_textItem;
    QGraphicsSceneMouseEvent* eventHandler = nullptr;
public:
    Button(qreal x, qreal y, qreal width, qreal height, QGraphicsItem* parent = nullptr)
            : QGraphicsRectItem(x, y, width, height, parent) {
        // Set the text item's parent to the button
        m_textItem.setParentItem(this);
        // Center the text within the button
        m_textItem.setPos(rect().center());
    }

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override{
        emit clicked();
        QGraphicsRectItem::mousePressEvent(event);
        qDebug() << m_textItem.toPlainText() << " was pressed";
    }

    void setText(const QString& text)
    {
        m_textItem.setPlainText(text);

        QFont font;
        font.setFamily("Times");
        font.setPointSize(16);
        m_textItem.setFont(font);

        // Center the text within the button
        QRectF rect = m_textItem.boundingRect();
        qreal dx = (boundingRect().width() - rect.width()) / 2.0;
        qreal dy = (boundingRect().height() - rect.height()) / 2.0;
        QPointF newPos = boundingRect().topLeft() + QPointF(dx, dy);
        m_textItem.setPos(newPos);
    }

    QString getText(){
        return m_textItem.toPlainText();
    }

    void setColor(const QColor& color) {
        setBrush(color);
    }

signals:
    void clicked();
};


class StartScene:public QGraphicsScene {
private:
public:
    StartScene() {
        setSceneRect(0, 0, 600, 800);
    }
};


class PlayScene:public QGraphicsScene {
private:
public:
    PlayScene() {
        setSceneRect(0, 0, 600, 800);
    }
};

class EndScene:public QGraphicsScene{
private:
public:
    EndScene() {
        setSceneRect(0, 0, 600, 800);
    }
};