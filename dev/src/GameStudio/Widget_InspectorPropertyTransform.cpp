#include "stdafx.h"
#include "Widget_InspectorPropertyTransform.h"


Widget_InspectorPropertyTransform::Widget_InspectorPropertyTransform(QWidget *parent, const math::Matrix44& initValue)
	: Widget_InspectorProperty(parent), 
	m_rvx(this), m_rvy(this), m_rvz(this),
	m_tvx(this), m_tvy(this), m_tvz(this),
	m_svx(this), m_svy(this), m_svz(this),

	m_labelRotation("Rotation", this), m_labelTranslation("Translation", this), m_labelScale("Scale", this),

	m_labelTvx("x", this), m_labelTvy("y", this), m_labelTvz("z", this), 
	m_labelRvx("x", this), m_labelRvy("y", this), m_labelRvz("z", this), 
	m_labelSvx("x", this), m_labelSvy("y", this), m_labelSvz("z", this)
{
	m_rvx.setValidator(&m_validator);
	m_rvy.setValidator(&m_validator);
	m_rvz.setValidator(&m_validator);

	m_tvx.setValidator(&m_validator);
	m_tvy.setValidator(&m_validator);
	m_tvz.setValidator(&m_validator);

	m_svx.setValidator(&m_validator);
	m_svy.setValidator(&m_validator);
	m_svz.setValidator(&m_validator);

	
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
	
	setMinimumHeight(6 * (WIDGET_ROW_HEIGHT + WIDGET_ROW_SPACING));
	setMinimumWidth(100);

	SetValue(initValue);


	connect(&m_tvx, SIGNAL(editingFinished()), this, SLOT(on_edit_changed()));
	connect(&m_tvy, SIGNAL(editingFinished()), this, SLOT(on_edit_changed()));
	connect(&m_tvz, SIGNAL(editingFinished()), this, SLOT(on_edit_changed()));
			
	connect(&m_rvx, SIGNAL(editingFinished()), this, SLOT(on_edit_changed()));
	connect(&m_rvy, SIGNAL(editingFinished()), this, SLOT(on_edit_changed()));
	connect(&m_rvz, SIGNAL(editingFinished()), this, SLOT(on_edit_changed()));
			
	connect(&m_svx, SIGNAL(editingFinished()), this, SLOT(on_edit_changed()));
	connect(&m_svy, SIGNAL(editingFinished()), this, SLOT(on_edit_changed()));
	connect(&m_svz, SIGNAL(editingFinished()), this, SLOT(on_edit_changed()));
}


Widget_InspectorPropertyTransform::~Widget_InspectorPropertyTransform(void)
{
}
void Widget_InspectorPropertyTransform::resizeEvent(QResizeEvent* e)
{
	
	adjustLayout(e->size());
	Widget_InspectorProperty::resizeEvent(e);
}

void Widget_InspectorPropertyTransform::adjustLayout(const QSize& size)
{
	int h_spacing = 1;
	int v_spacing = WIDGET_ROW_SPACING;
	int v_height = WIDGET_ROW_HEIGHT;
	int width = size.width();
	int label_width = 6;
	int label_padding = 10;
	int edit_width = (width - 2 * h_spacing - label_width * 3  - label_padding * 5) / 3;
	
	int offset = 0;

	// translation
	m_labelTranslation.setGeometry(0, offset, width, v_height);
	offset += v_height + v_spacing;

	// translation row
	// x label
	int row_offset = 0;
	
	m_labelTvx.setGeometry(row_offset, offset, label_width, v_height);
	row_offset +=  label_width + label_padding;

	// x value
	m_tvx.setGeometry(row_offset, offset, edit_width, v_height);
	row_offset += edit_width + label_padding;

	// y label
	m_labelTvy.setGeometry(row_offset, offset, label_width, v_height);
	row_offset += label_width + label_padding;

	// y value
	m_tvy.setGeometry(row_offset, offset, edit_width, v_height);
	row_offset += edit_width + label_padding;
	
	// z label
	m_labelTvz.setGeometry(row_offset, offset, label_width, v_height);
	row_offset += label_width + label_padding;

	// z value
	m_tvz.setGeometry(row_offset, offset, edit_width, v_height);
	offset += v_height + v_spacing;
	
		
	// rotation
	m_labelRotation.setGeometry(0, offset, width, v_height);
	offset += v_height + v_spacing;
	
	// rotation row
	row_offset = 0;
	
	// x label
	m_labelRvx.setGeometry(row_offset, offset, label_width, v_height);
	row_offset += label_width + label_padding;
	
	// x value
	m_rvx.setGeometry(row_offset, offset, edit_width, v_height);
	row_offset += edit_width + label_padding;
	
	// y label
	m_labelRvy.setGeometry(row_offset, offset, label_width, v_height);
	row_offset += label_width + label_padding;

	// y value
	m_rvy.setGeometry(row_offset, offset, edit_width, v_height);
	row_offset += edit_width + label_padding;

	// z label
	m_labelRvz.setGeometry(row_offset, offset, label_width, v_height);
	row_offset += label_width + label_padding;

	// z value
	m_rvz.setGeometry(row_offset, offset, edit_width, v_height);
	offset += v_height + v_spacing;
	
		
	// scale
	m_labelScale.setGeometry(0, offset, width, v_height);
	offset += v_height + v_spacing;

	// scale row
	// x label
	row_offset = 0;
	m_labelSvx.setGeometry(row_offset, offset, label_width, v_height);
	row_offset += label_width + label_padding;

	// x value
	m_svx.setGeometry(row_offset, offset, edit_width, v_height);
	row_offset += edit_width + label_padding;

	// y label
	m_labelSvy.setGeometry(row_offset, offset, label_width, v_height);
	row_offset += label_width + label_padding;

	// y value
	m_svy.setGeometry(row_offset, offset, edit_width, v_height);
	row_offset += edit_width + label_padding;

	// z label
	m_labelSvz.setGeometry(row_offset, offset, label_width, v_height);
	row_offset += label_width + label_padding;

	// z value
	m_svz.setGeometry(row_offset, offset, edit_width, v_height);

	setMinimumHeight(offset + v_height + v_spacing);
}

math::Matrix44 Widget_InspectorPropertyTransform::GetValue()
{
	math::Vector3 trans(m_tvx.text().toDouble(), m_tvy.text().toDouble(), m_tvz.text().toDouble());
	math::Vector3 rotation(m_rvx.text().toDouble(), m_rvy.text().toDouble(), m_rvz.text().toDouble());
	math::Vector3 scale(m_svx.text().toDouble(), m_svy.text().toDouble(), m_svz.text().toDouble());

	math::Matrix44 mat = EularToMatrix(rotation);
	mat.SetScale(scale);
	mat.SetTranslation(trans);

	return mat;
}
void Widget_InspectorPropertyTransform::SetValue(const math::Matrix44& value)
{
	math::Vector3 trans = value.GetRow3(3);
	math::Vector3 scale = value.GetScale();
	scale.x = abs(scale.x);
	scale.y = abs(scale.y);
	scale.z = abs(scale.z);
	math::Vector3 rotation = MatrixToEular(value);

	m_tvx.setText(QString::number(trans.x));
	m_tvy.setText(QString::number(trans.y));
	m_tvz.setText(QString::number(trans.z));
		 
	m_rvx.setText(QString::number(rotation.x));
	m_rvy.setText(QString::number(rotation.y));
	m_rvz.setText(QString::number(rotation.z));
		 
	m_svx.setText(QString::number(scale.x));
	m_svy.setText(QString::number(scale.y));
	m_svz.setText(QString::number(scale.z));
}
math::Vector3 Widget_InspectorPropertyTransform::MatrixToEular(const math::Matrix44& mat)
{
	math::Vector3 r;
	math::Matrix44 rm = mat;

	rm.SetScale(math::Vector3(1, 1, 1));
	//rm.Transpose();

	// Assuming the angles are in radians.
	if (rm(1, 0) > 0.998)
	{ // singularity at north pole
		r.x = 0;
		r.y = atan2(rm(0, 2), rm(2, 2));
		r.z = math::MATH_PI/2;
		return r;
	}
	if (rm(1, 0) < -0.998) { // singularity at south pole
		r.x = 0;

		r.y = atan2(rm(0, 2),rm(2, 2));
		r.z = -math::MATH_PI/2;
		return r;
	}

	r.x  = atan2(-rm(1, 2),rm(1, 1));
	r.y  = atan2(-rm(2, 0), rm(0, 0));
	r.z  = asin(rm(1, 0));

	return math::Vector3(-math::R2D(r.x), -math::R2D(r.y), -math::R2D(r.z));
}
math::Matrix44 Widget_InspectorPropertyTransform::EularToMatrix(const math::Vector3& r)
{
	using namespace math;

	return MatrixRotationAxisY(D2R(r.y)) * MatrixRotationAxisZ(D2R(r.z)) * MatrixRotationAxisX(D2R(r.x));
}
QSize Widget_InspectorPropertyTransform::sizeHint() const
{
	return QSize(100, 6 * (WIDGET_ROW_HEIGHT + WIDGET_ROW_SPACING));
}
void Widget_InspectorPropertyTransform::on_edit_changed()
{
	on_property_changed ? on_property_changed(this) : 0;
}
