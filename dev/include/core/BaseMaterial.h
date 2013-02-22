#pragma once


namespace ld3d
{
	class BaseMaterial
	{
	public:

		//virtual const std::string&										GetName()							= 0;

		virtual void														Begin(){}
		virtual void														End(){}
		virtual void														ApplyPass(){}


	protected:
		BaseMaterial(void){}

		virtual ~BaseMaterial(void){}
	};


}
