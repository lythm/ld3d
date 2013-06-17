#include "stdafx.h"
#include "form_log.h"

Form_Log::Form_Log(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);
}

Form_Log::~Form_Log()
{

}
void Form_Log::logInfo(QString str)
{
	QTextCursor cursor = textInfo->textCursor();
	cursor.movePosition(QTextCursor::End);
	cursor.insertText(str + "\n");
	cursor.movePosition(QTextCursor::End);
	textInfo->setTextCursor(cursor);
	
}
void Form_Log::logBuild(QString str)
{
}
