#include "core_pch.h"
#include "..\..\include\core\AssetsManager.h"
#include "core\Texture.h"
#include "core\Sys_Graphics.h"
#include "core_utils.h"

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

		return true;
	}
	void AssetManager::Release()
	{
		AssetMap::iterator it = m_assets.begin();
		for(;it != m_assets.end(); ++it)
		{
			it->second->Release();
		}

		m_assets.clear();
	}
	AssetPtr AssetManager::LoadAsset()
	{
		return AssetPtr();
	}
	bool AssetManager::PreloadAsset()
	{
		return true;
	}
	TextureAssetPtr AssetManager::LoadTexture(boost::filesystem::path file)
	{
		AssetPtr pAsset = FindAsset(file);
		if(pAsset)
		{
			return boost::shared_dynamic_cast<Asset_T<Texture> >(pAsset);
		}

		TexturePtr pTex = m_pGraphics->CreateTextureFromFile(file.string().c_str());
		if(pTex == nullptr)
		{
			return TextureAssetPtr();
		}

		pAsset = alloc_object<TextureAsset, TexturePtr>(pTex);

		m_assets[file] = pAsset;
		return boost::shared_dynamic_cast<Asset_T<Texture> >(pAsset);

	}
	AssetPtr AssetManager::FindAsset(boost::filesystem::path file)
	{
		AssetMap::iterator it = m_assets.find(file);
		if(it != m_assets.end())
		{
			if(it->second->Ready())
			{
				return it->second;
			}
		}

		return AssetPtr();
	}
}
