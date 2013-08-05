#include "stdafx.h"
#include "leaf.h"
#include <QtWidgets/QApplication>

#ifdef __DEBUG__
#include <QtCore/qdebug.h>
#include <QtCore/QtGlobal>
#include <cassert>
QWidget  *DEBUG_MESSAGE_DISPLAY_WIDGET   = NULL;
QPlainTextEdit  *DEBUG_MESSAGE_DISPLAY_TEXTEDIT = NULL;
void setupDebugDisplay();
void debugMessageDisplayFunc(QtMsgType type, const QMessageLogContext& Context, const QString &Message);
#endif // __DEBUG__


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

#ifdef __DEBUG__
	a.setQuitOnLastWindowClosed( true );
	setupDebugDisplay();
#endif // __DEBUG__

	Leaf w;
	w.show();

#ifdef __DEBUG__
	int ret = a.exec();
	delete DEBUG_MESSAGE_DISPLAY_WIDGET;
	return ret;
#else
	return a.exec();
#endif // __DEBUG__
}

#ifdef __DEBUG__
void setupDebugDisplay()
{
    QWidget *widget = new QWidget();
    widget->setWindowTitle( "Debug Log" );
    widget->setAttribute( Qt::WA_QuitOnClose, false ); //quit only when mainwindow is closed
    QBoxLayout* layout = new QVBoxLayout();
    widget->setLayout( layout );
    QPlainTextEdit *textEdit = new QPlainTextEdit( widget );
    QFont font = QFont( "Monospace" );
    font.setStyleHint(QFont::TypeWriter);
    textEdit->setFont( font );
    textEdit->setReadOnly(true);
    layout->addWidget( textEdit );
    widget->show();
    DEBUG_MESSAGE_DISPLAY_WIDGET   = widget;
    DEBUG_MESSAGE_DISPLAY_TEXTEDIT = textEdit;
	
	qInstallMessageHandler(debugMessageDisplayFunc);

}

void debugMessageDisplayFunc(QtMsgType type, const QMessageLogContext& Context, const QString &msg)
{
  bool do_abort = false;
  const char* msgTypeStr = NULL;
  switch (type) {
    case QtDebugMsg:
      msgTypeStr = "Debug";
      break;
    case QtWarningMsg:
      msgTypeStr = "Warning";
      break;
    case QtCriticalMsg:
      msgTypeStr = "Critical";
      break;
    case QtFatalMsg:
      msgTypeStr = "Fatal";
      do_abort = true;
    default:
      assert(0);
      return;
  }
  QTime now = QTime::currentTime();
  QString formattedMessage = 
    QString::fromLatin1("%1 %2 %3")
    .arg(now.toString("hh:mm:ss:zzz"))
    .arg(msgTypeStr).arg(msg);
  // print on console:
  fprintf( stderr, "%s\n", formattedMessage.toLocal8Bit().constData() );
  // print in debug log window
  {

    bool isMainThread = QThread::currentThread() == QApplication::instance()->thread();
    if(DEBUG_MESSAGE_DISPLAY_TEXTEDIT)
    {
      if( isMainThread )
        DEBUG_MESSAGE_DISPLAY_TEXTEDIT->appendPlainText( formattedMessage );
      else // additional code, so that qDebug calls in threads will work aswell
        QMetaObject::invokeMethod( DEBUG_MESSAGE_DISPLAY_TEXTEDIT, "appendPlainText", Qt::QueuedConnection, Q_ARG( QString, formattedMessage ) );
    }
  }
}

#endif // __DEBUG__