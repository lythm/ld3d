#pragma once

namespace ld3d
{
	class Asset
	{
	public:
		Asset()
		{
			m_refCount = 1;
		}
		virtual ~Asset(){}

		virtual void							Release()												= 0;
		int										IncRef()
		{
			++m_refCount;
			return m_refCount;
		}
		int										DecRef()
		{
			--m_refCount;
			return m_refCount;
		}
		int										Ref()
		{
			return m_refCount;
		}

		virtual bool							Ready()
		{
			return false;
		}
	private:
		int										m_refCount;
	};

	template <typename T> class Asset_T : public Asset
	{
		typedef std::shared_ptr<T>			T_Ptr;
	public:

		Asset_T(T_Ptr pAsset)
		{
			m_pAsset = pAsset;
		}
		Asset_T()
		{
			
		}
		virtual ~Asset_T(){}
		void									Release()
		{
			if(DecRef() == 0)
			{
				m_pAsset->Release();
				m_pAsset.reset();
			}
		}

		T_Ptr									GetAsset()
		{
			return m_pAsset;
		}

		bool									Ready()
		{
			return m_pAsset != nullptr;
		}

	private:
		T_Ptr									m_pAsset;
		
	};
	class _DLL_CLASS AssetManager
	{
		typedef std::unordered_map<std::string, AssetPtr>								AssetMap;
		typedef std::function<AssetPtr (const boost::filesystem::path& file)>			AssetLoader;
		typedef std::unordered_map<std::string, AssetLoader>							AssetLoaderMap;

	public:
		AssetManager(void);
		virtual ~AssetManager(void);

		bool								Initialize(Sys_GraphicsPtr pGraphics, Sys_SoundPtr pSound);
		void								Release();

		AssetPtr							LoadAsset(const boost::filesystem::path& file);
		bool								RegisterAssetLoader(const boost::filesystem::path& ext, AssetLoader loader);


	private:
		void								RegisterAssetLoaders();
		AssetPtr							FindAsset(const boost::filesystem::path& file);
		AssetLoader							FindLoader(const boost::filesystem::path& file);

		AssetPtr							LoadSound(const boost::filesystem::path& file, bool sound3d = true);
		AssetPtr							LoadTexture(const boost::filesystem::path& file);
	private:
		Sys_GraphicsPtr					m_pGraphics;
		Sys_SoundPtr						m_pSound;
		

		AssetMap							m_assets;

		AssetLoaderMap						m_loaders;
	};
}
