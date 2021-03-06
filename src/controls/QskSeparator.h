/******************************************************************************
 * QSkinny - Copyright (C) 2016 Uwe Rathmann
 * This file may be used under the terms of the QSkinny License, Version 1.0
 *****************************************************************************/

#ifndef QSK_SEPARATOR_H
#define QSK_SEPARATOR_H

#include "QskGlobal.h"
#include "QskControl.h"

class QSK_EXPORT QskSeparator : public QskControl
{
    Q_OBJECT

    Q_PROPERTY( Qt::Orientation orientation READ orientation
        WRITE setOrientation NOTIFY orientationChanged )

    Q_PROPERTY( qreal thickness READ thickness
        WRITE setThickness NOTIFY thicknessChanged )

    using Inherited = QskControl;

public:
    QSK_SUBCONTROLS( Panel )

    QskSeparator( QQuickItem* parent = nullptr );
    QskSeparator( Qt::Orientation, QQuickItem* parent = nullptr );

    virtual ~QskSeparator();

    void setOrientation( Qt::Orientation );
    Qt::Orientation orientation() const;

    void setThickness( qreal thickness );
    qreal thickness() const;

    virtual QSizeF contentsSizeHint() const override;

Q_SIGNALS:
    void orientationChanged( Qt::Orientation );
    void thicknessChanged() const;

private:
    Qt::Orientation m_orientation;
};

#endif
