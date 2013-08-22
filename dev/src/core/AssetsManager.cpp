#include "core_pch.h"
#include "core/AssetsManager.h"
#include "core/Texture.h"
#include "core/Sys_Graphics.h"
#include "core_utils.h"
#include "core/Sys_Sound.h"
#include "core/Sound.h"

namespace ld3d
{
	AssetManager::AssetManager(void)
	{
	}


	AssetManager::~AssetManager(void)
	{
	}
	bool AssetManager::Initialize(Sys_GraphicsPtr pGraphics, Sys_SoundPtr pSound)
	{
		m_pGraphics				= pGraphics;
		m_pSound				= pSound;

		

		RegisterAssetLoaders();

		return true;
	}
	void AssetManager::Release()
	{
		AssetMap::iterator it = m_assets.begin();
		for(;it != m_assets.end(); ++it)
		{
			if(it->second->Ready())
			{
				char buffer[100];
				sprintf(buffer, "%d", it->second->Ref());
				log("asset leak: " + it->first + " ref: " + buffer);
				it->second->Release();
			}
		}

		m_assets.clear();

		m_loaders.clear();

	}
	AssetPtr AssetManager::LoadAsset(const boost::filesystem::path& file)
	{
		AssetPtr pAsset = FindAsset(file);
		if(pAsset)
		{
			pAsset->IncRef();
			return pAsset;
		}

		AssetLoader loader = FindLoader(file);
		if(loader)
		{
			return AssetPtr();
		}
		pAsset = loader(file);

		m_assets[file.string()] = pAsset;
		return pAsset;
	}

	AssetPtr AssetManager::LoadSound(const boost::filesystem::path& file, bool sound3d)
	{
		SoundPtr pSound;
		
		if(sound3d)
		{
			pSound = m_pSound->Create3DSound(file.string().c_str());
		}
		else
		{
			pSound = m_pSound->CreateSound(file.string().c_str());
		}
		if(pSound == nullptr)
		{
			return AssetPtr();
		}

		AssetPtr pAsset = alloc_object<SoundAsset, SoundPtr>(pSound);

		return pAsset;
	}
	AssetPtr AssetManager::LoadTexture(const boost::filesystem::path& file)
	{
		TexturePtr pTex = m_pGraphics->CreateTextureFromFile(file.string().c_str(), false);
		if(pTex == nullptr)
		{
			return TextureAssetPtr();
		}

		AssetPtr pAsset = alloc_object<TextureAsset, TexturePtr>(pTex);

		return pAsset;

	}
	AssetPtr AssetManager::FindAsset(const boost::filesystem::path& file)
	{
		AssetMap::iterator it = m_assets.find(file.string());
		if(it != m_assets.end())
		{
			if(it->second->Ready())
			{
				return it->second;
			}
		}

		return AssetPtr();
	}
	AssetManager::AssetLoader AssetManager::FindLoader(const boost::filesystem::path& path)
	{
		if(path.has_extension() == false)
		{
			return AssetLoader();
		}
		AssetLoaderMap::iterator it = m_loaders.find(path.extension().string());

		if(it != m_loaders.end())
		{
			return it->second;
		}
		return AssetLoader();
	}
	bool AssetManager::RegisterAssetLoader(const boost::filesystem::path& ext, AssetLoader loader)
	{
		AssetLoaderMap::iterator it = m_loaders.find(ext.string());

		if(it != m_loaders.end())
		{
			log("Asset loader already exists: " + it->first);
			return false;
		}

		m_loaders[ext.string()] = loader;

		return true;
	}
	void AssetManager::RegisterAssetLoaders()
	{
		AssetLoader loader = boost::bind(&AssetManager::LoadSound, this, _1, true);
		RegisterAssetLoader(boost::filesystem::path(".mp3"), loader);
		RegisterAssetLoader(boost::filesystem::path(".ogg"), loader);
		RegisterAssetLoader(boost::filesystem::path(".wav"), loader);

		loader = boost::bind(&AssetManager::LoadTexture, this, _1);
		RegisterAssetLoader(boost::filesystem::path(".dds"), loader);
		RegisterAssetLoader(boost::filesystem::path(".jpg"), loader);
		RegisterAssetLoader(boost::filesystem::path(".tga"), loader);
		RegisterAssetLoader(boost::filesystem::path(".bmp"), loader);

	}
}
