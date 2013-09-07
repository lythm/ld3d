#include "stdafx.h"
#include "form_log.h"

Form_Log::Form_Log(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);
	textInfo->blockSignals(true);
}

Form_Log::~Form_Log()
{

}
void Form_Log::logInfo(const QString& str)
{
	QTextCursor text_cursor = textInfo->textCursor();
	text_cursor.movePosition(QTextCursor::End);
	text_cursor.insertText(str);
	
	textInfo->moveCursor(QTextCursor::End);

}
void Form_Log::logBuild(const QString& str)
{
}
