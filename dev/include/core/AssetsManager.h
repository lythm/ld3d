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
		typedef boost::shared_ptr<T>			T_Ptr;
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
	class EXPORT_CLASS AssetManager
	{
		typedef boost::unordered_map<boost::filesystem::path, AssetPtr>					AssetMap;

	public:
		AssetManager(void);
		virtual ~AssetManager(void);

		bool								Initialize(Sys_GraphicsPtr pGraphics, Sys_SoundPtr pSound);
		void								Release();


		SoundAssetPtr						LoadSound(const boost::filesystem::path& file, bool sound3d = true);
		TextureAssetPtr						LoadTexture(const boost::filesystem::path& file);

		AssetPtr							LoadAsset();
		bool								PreloadAsset();

	private:
		AssetPtr							FindAsset(boost::filesystem::path file);
	private:
		Sys_GraphicsPtr						m_pGraphics;
		Sys_SoundPtr						m_pSound;
		

		AssetMap							m_assets;
	};
}
