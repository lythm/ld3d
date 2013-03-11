#pragma once


namespace ld3d
{
	class MaterialTech
	{
	public:
		MaterialTech(const std::string& name);
		virtual ~MaterialTech(void);

		bool												Parse();
		void												Release();
		uint32												GetPassCount();
		MaterialPassPtr										GetPassByIndex(uint32 index);

		void												AddPass(MaterialPassPtr pPass);
		const std::string&									GetName();

		bool												Validate();
		bool												IsValid();
	private:
		std::vector<MaterialPassPtr>						m_passes;
		std::string											m_name;
		bool												m_valid;
	};


}