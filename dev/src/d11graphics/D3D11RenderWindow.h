#pragma once

#include "core\RenderWindow.h"

namespace ld3d
{
	class D3D11RenderWindow : public RenderWindow
	{
	public:
		D3D11RenderWindow(ID3D11DeviceContext* pContext);
		virtual ~D3D11RenderWindow(void);


		bool											Create(void* handle, int w, int h, G_FORMAT color_format, G_FORMAT ds_format, int backbufferCount, int multiSampleCount, int multiSampleQuality, bool windowed);
		void											Release();

		void											Present();
		void											Resize(int cx, int cy);

		ID3D11DepthStencilView*							GetD3D11DepthStencilView();
		ID3D11RenderTargetView*							GetD3D11RenderTargetView();

		int												GetWidth();
		int												GetHeight();

	private:
		bool											CreateFrameBuffer();
	private:

		IDXGISwapChain*									m_pSwapChain;


		G_FORMAT										m_frameBufferFormat;
		G_FORMAT										m_dsFormat;
		int												m_backbufferCount;
		int												m_multiSampleCount;
		int												m_multiSampleQuality;


		ID3D11RenderTargetView*							m_pRTView;
		ID3D11Device*									m_pDevice;
		ID3D11DeviceContext*							m_pContext;
		DepthStencilBufferPtr							m_pDepthBuffer;

		int												m_width;
		int												m_height;

	};
}
