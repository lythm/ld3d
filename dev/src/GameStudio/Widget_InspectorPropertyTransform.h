#pragma once

#include "widget_inspectorproperty.h"

class Widget_InspectorPropertyTransform : public Widget_InspectorProperty
{
	Q_OBJECT
public:
	Widget_InspectorPropertyTransform(QWidget *parent, const math::Matrix44& initValue = math::MatrixIdentity());
	virtual ~Widget_InspectorPropertyTransform(void);


	math::Matrix44									GetValue();
	void											SetValue(const math::Matrix44& value);

	void											resizeEvent(QResizeEvent* e);
private:
	math::Vector3									MatrixToEular(const math::Matrix44& mat);
	math::Matrix44									EularToMatrix(const math::Vector3& r);

	void											adjustLayout(const QSize& size);

private:

	QLineEdit*										m_rvx;
	QLineEdit*										m_rvy;
	QLineEdit*										m_rvz;

	QLineEdit*										m_tvx;
	QLineEdit*										m_tvy;
	QLineEdit*										m_tvz;

	QLineEdit*										m_svx;
	QLineEdit*										m_svy;
	QLineEdit*										m_svz;

	QLabel*											m_labelTranslation;
	QLabel*											m_labelRotation;
	QLabel*											m_labelScale;

	QLabel*											m_labelTvx;
	QLabel*											m_labelTvy;
	QLabel*											m_labelTvz;

	QLabel*											m_labelRvx;
	QLabel*											m_labelRvy;
	QLabel*											m_labelRvz;

	QLabel*											m_labelSvx;
	QLabel*											m_labelSvy;
	QLabel*											m_labelSvz;
};

