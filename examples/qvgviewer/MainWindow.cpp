/******************************************************************************
 * QSkinny - Copyright (C) 2016 Uwe Rathmann
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#include "MainWindow.h"

#include <QskGraphic.h>
#include <QskGraphicLabel.h>
#include <QskGraphicIO.h>
#include <QskPushButton.h>
#include <QskLinearBox.h>
#include <QskColorFilter.h>
#include <QskAspect.h>
#include <QskTabView.h>
#include <QskSetup.h>
#include <QskSkin.h>
#include <QskAnimationHint.h>

#include <QDir>
#include <QVariant>

class GraphicLabel : public QskGraphicLabel
{
public:
    enum Role
    {
        Normal,
        Inverted
    };

    GraphicLabel( const QskGraphic& graphic, QQuickItem* parent = nullptr ):
        QskGraphicLabel( graphic, parent )
    {
        setAlignment( Qt::AlignCenter );
        setAutoFillBackground( true );

        setDarknessMode( false );
    }

    void setDarknessMode( bool on )
    {
        using namespace QskAspect;

        const int oldRole = graphicRole();

        QColor color;
        if ( on )
        {
            color.setRgb( 40, 40, 40 );
            setGraphicRole( Inverted );
        }
        else
        {
            color.setRgb( 255, 228, 181 );
            setGraphicRole( Normal );
        }

        const int duration = 500;

        for ( auto edge : { TopEdge, BottomEdge } )
        {
            const Aspect aspectColor = Control | Color | Background | edge;

            const auto oldColor = effectiveHint( aspectColor );
            setColor( aspectColor, color );
            startTransition( aspectColor, duration, oldColor, color );
        }

        const QskAspect::Aspect aspectRole = QskGraphicLabel::Graphic | GraphicRole;
        startTransition( aspectRole, duration, oldRole, graphicRole() );
    }
};

MainWindow::MainWindow()
{
    m_tabView = new QskTabView( Qt::Horizontal );

    const QString resourceDir( ":/qvg" );
    const QStringList icons = QDir( resourceDir ).entryList();

    for ( auto icon : icons )
    {
        m_tabView->addTab( icon.replace( ".qvg", "" ),
            new GraphicLabel( QskGraphicIO::read( resourceDir + "/" + icon ) ) );
    }

    auto invertButton = new QskPushButton( "Inverted" );
    invertButton->setSizePolicy( Qt::Horizontal, QskSizePolicy::Fixed );
    invertButton->setCheckable( true );

    auto box = new QskLinearBox( Qt::Vertical );
    box->setMargins( 5 );
    box->addItem( invertButton, Qt::AlignRight );
    box->addItem( m_tabView );

    addItem( box );

    connect( invertButton, &QskPushButton::toggled,
        this, &MainWindow::setDarknessMode );

    connect( qskSetup, &QskSetup::skinChanged,
        this, &MainWindow::setGraphicRoles );

    setGraphicRoles( qskSetup->skin() );
}

void MainWindow::setDarknessMode( bool on )
{
    for ( int i = 0; i < m_tabView->count(); i++ )
    {
        auto label = static_cast< GraphicLabel* >( m_tabView->itemAt( i ) );
        label->setDarknessMode( on );
    }
}

void MainWindow::setGraphicRoles( QskSkin* skin )
{
    // substituting black and white
    QskColorFilter colorFilter;
    colorFilter.addColorSubstitution( qRgb( 0, 0, 0 ), qRgb( 189, 183, 107 ) );
    colorFilter.addColorSubstitution( qRgb( 255, 255, 255 ), qRgb( 50, 50, 50 ) );

    skin->setGraphicFilter( GraphicLabel::Inverted, colorFilter );
}

#include "moc_MainWindow.cpp"
