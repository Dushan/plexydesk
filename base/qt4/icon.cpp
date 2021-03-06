/*
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "icon.h"
#include <qplexymime.h>
#include <iconprovider.h>
#include <QPainter>

namespace PlexyDesk
{

class Icon::Private
{
    public:
      Private(){}
      ~Private(){}
      QPixmap icon;
      QPlexyMime mime;
      bool valid;
      IconProviderPtr iconprovider;
};

Icon::Icon(IconProviderPtr icon, const QRectF &rect, QWidget *embeddedWidget) : DesktopWidget(rect), d(new Private)
{
    d->valid = false;
    d->iconprovider = icon;
}

Icon::~Icon()
{
    qDebug()<<"Delete Icon"<<endl;
}

void Icon::setContent(const QString& path)
{
    qDebug()<<d->mime.fromFileName(path)<<endl;
    QString iconname;
    if(d->mime.mimeType() == "application/x-desktop")
    {
        QSettings setting(path,  QSettings::IniFormat);
        setting.beginGroup("Desktop Entry");
        iconname = setting.value("Icon","").toString();
        setting.endGroup();
        d->valid = true;
    } else {
        QString name = d->mime.genericIconName();
    }
   // d->icon = QPixmap(applicationDirPath()+"/share/app-install/icons/"+iconname+".png");
    d->iconprovider->requestIcon(iconname, "32x32");
    connect(d->iconprovider.data(),SIGNAL(iconPixmap(const QPixmap&)),this, SLOT(onIconPixmap(const QPixmap&)));
}

void Icon::onIconPixmap(const QPixmap& pixmap)
{
    if(!pixmap.isNull())  {
      d->icon = pixmap;
    }
}

bool Icon::isValid()
{
    return d->valid;
}

void Icon::paintBackSide(QPainter * painter,const QRectF& rect)
{
        if(!d->icon.isNull()) {
         int x = (this->boundingRect().width() - d->icon.width())/2;
         painter->drawPixmap(QRect(x, x , d->icon.width(), d->icon.height()) , d->icon);
        }
       // DesktopWidget::paintDockView(painter, rect);
}
void Icon::paintViewSide(QPainter * painter,const QRectF& rect)
{
       // DesktopWidget::paintDockView(painter, rect);
        if(!d->icon.isNull()) {
          int x = (this->boundingRect().width() - d->icon.width())/2;
          painter->drawPixmap(QRect(x, x , d->icon.width(), d->icon.height()) , d->icon);
        }
}
void Icon::paintDockView(QPainter * painter,const QRectF& rect)
{
    DesktopWidget::paintDockView(painter, rect);
   if(!d->icon.isNull()) {
         int x = (this->boundingRect().width() - d->icon.width())/2;
         painter->drawPixmap(QRect(x, x , d->icon.width(), d->icon.height()) , d->icon);
    }
}

}
