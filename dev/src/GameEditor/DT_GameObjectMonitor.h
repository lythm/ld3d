#pragma once

#include <boost\function.hpp>
#include <boost\signal.hpp>
namespace dt
{
	class DT_GameObjectMonitor : public ld3d::GameObjectComponent
	{
	public:

		typedef boost::function<void (ld3d::GameObjectPtr)>				Monitor;

		DT_GameObjectMonitor(ld3d::GameObjectManagerPtr pManager);
		virtual ~DT_GameObjectMonitor(void);

		void															AddMonitor(const Monitor& m);
		void															Alert();

		static ld3d::GameObjectComponentPtr								Create(ld3d::GameObjectManagerPtr pManager);
		static ld3d::ExtPackage::ComponentClass*						GetClass();

		
	private:

		static ld3d::ExtPackage::ComponentClass							s_class;

		boost::signal<void (ld3d::GameObjectPtr)>						m_monitors;
	};
}
