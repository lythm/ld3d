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
	/*QTextCursor cursor = textInfo->textCursor();
	cursor.movePosition(QTextCursor::End);
	cursor.insertText(str + "\n");
	cursor.movePosition(QTextCursor::End);
	textInfo->setTextCursor(cursor);*/

	textInfo->appendPlainText(str);
	//textInfo->moveCursor(QTextCursor::End);

	//textInfo->update();
}
void Form_Log::logBuild(const QString& str)
{
}
