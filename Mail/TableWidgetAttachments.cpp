#include "TableWidgetAttachments.hpp"
#include "fileattachmentwidget.hpp"

#include <QApplication>
#include <QClipboard>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QUrl>
#include <QFileInfo>

TableWidgetAttachments::TableWidgetAttachments(QWidget *parent) :
    QTableWidget(parent)
{
 setAcceptDrops(true);
}

void TableWidgetAttachments::dragEnterEvent(QDragEnterEvent *event)
{
  QStringList stringList = getFilesPathFromMimeData( event->mimeData() );
  if (stringList.size())
    event->acceptProposedAction();
}
 
void TableWidgetAttachments::dragMoveEvent(QDragMoveEvent *event)
{
    event->acceptProposedAction();
}
 
void TableWidgetAttachments::dragLeaveEvent(QDragLeaveEvent *event)
{
    event->accept();
}

void TableWidgetAttachments::dropEvent(QDropEvent *event)
{  
  QStringList stringList = getFilesPathFromMimeData(event->mimeData());
  if (stringList.size())
  {
    emit dropEvent(stringList);
    event->acceptProposedAction();
  }
}

QStringList TableWidgetAttachments::getFilesPathFromClipboard()
{
  const QMimeData *md = QApplication::clipboard()->mimeData();
  QStringList stringList = getFilesPathFromMimeData(md);
  return stringList;
}

QStringList TableWidgetAttachments::getFilesPathFromMimeData(const QMimeData *md)
{
  QStringList stringList = QStringList();

  if(md)
  {
    bool en = md->hasText();
    if (md->hasUrls())
    {
      for (int i = 0; i < md->urls().size(); i++)
      {
        QUrl url = md->urls().at(i);      
        if (url.isLocalFile ())
        {
          QString fileName = url.toLocalFile ();
          QFileInfo fileInfo(fileName);
          if (fileInfo.isFile())
            stringList.push_back( fileName );
        }
      }
    }
  }

  return stringList;
}