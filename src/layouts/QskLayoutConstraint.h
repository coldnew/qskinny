/******************************************************************************
 * QSkinny - Copyright (C) 2016 Uwe Rathmann
 * This file may be used under the terms of the QSkinny License, Version 1.0
 *****************************************************************************/

#ifndef QSK_LAYOUT_CONSTRAINT_H
#define QSK_LAYOUT_CONSTRAINT_H

#include "QskGlobal.h"
#include <Qt>
#include <limits>

class QskSizePolicy;
class QQuickItem;
class QSizeF;

namespace QskLayoutConstraint
{
    QSK_EXPORT bool hasDynamicConstraint( const QQuickItem* );
    QSK_EXPORT qreal heightForWidth( const QQuickItem*, qreal width );
    QSK_EXPORT qreal widthForHeight( const QQuickItem*, qreal height );

    QSK_EXPORT QSizeF effectiveConstraint( const QQuickItem*, Qt::SizeHint );
    QSK_EXPORT QskSizePolicy sizePolicy( const QQuickItem* );

    // QGridLayoutEngine internally uses FLT_MAX
    const qreal unlimited = std::numeric_limits< float >::max();
}

#endif
