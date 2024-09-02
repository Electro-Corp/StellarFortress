#ifndef ZOOMGRAPHICSVIEW_H
#define ZOOMGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QGraphicsScene>
#include <QDebug>

class ZoomGraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    explicit ZoomGraphicsView(QWidget *parent = nullptr)
        : QGraphicsView(parent), isPanning(false) {}

    ZoomGraphicsView(QGraphicsScene *scene, QWidget *parent = nullptr)
        : QGraphicsView(scene, parent), isPanning(false) {}

protected:
    void wheelEvent(QWheelEvent *event) override
    {
        qreal zoomFactor = 1.2;
        if (event->delta() < 0)
            zoomFactor = 1.0 / zoomFactor;

        
        QPointF mouseScenePos = mapToScene(event->pos());

        scale(zoomFactor, zoomFactor);

        QPointF newMouseScenePos = mapToScene(event->pos());

        QPointF offset = mouseScenePos - newMouseScenePos;

        translate(offset.x(), offset.y());

        QGraphicsView::wheelEvent(event);
    }

    void mousePressEvent(QMouseEvent *event) override
    {
        if (event->button() == Qt::LeftButton)
        {
            isPanning = true;
            lastMousePos = event->pos();
            setCursor(Qt::ClosedHandCursor);
        }
        QGraphicsView::mousePressEvent(event);
    }

    void mouseMoveEvent(QMouseEvent *event) override
    {
        if (isPanning)
        {
            QPointF delta = mapToScene(lastMousePos) - mapToScene(event->pos());

            QTransform transform = this->transform();

            transform.translate(delta.x(), delta.y());

            this->setTransform(transform);

            lastMousePos = event->pos();
        }
        QGraphicsView::mouseMoveEvent(event);
    }

    void mouseReleaseEvent(QMouseEvent *event) override
    {
        if (event->button() == Qt::LeftButton)
        {
            isPanning = false;
            unsetCursor();
        }
        QGraphicsView::mouseReleaseEvent(event);
    }

private:
    bool isPanning;
    QPoint lastMousePos;
};

#endif
