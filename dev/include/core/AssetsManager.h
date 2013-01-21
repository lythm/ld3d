#pragma once

namespace ld3d
{
	class Asset
	{
	public:
		Asset(){}
		virtual ~Asset(){}

		virtual void							Release();
	private:
		int										m_refCount;
	};

	template <typename T> class Asset_T : public Asset
	{
	public:
		Asset_T(){}
		virtual ~Asset_T(){}
	};
	class AssetManager
	{
	public:
		AssetManager(void);
		virtual ~AssetManager(void);

		AssetPtr							LoadAsset();
		bool								PreloadAsset();
	private:

	};
}
