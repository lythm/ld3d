#pragma once

#include "core\g_format.h"

namespace ld3d
{
	class VertexLayout
	{
	public:
		struct VertexAttr
		{
			//int							slot;
			G_FORMAT					type;
			std::string					semantics;
		};

		VertexLayout()
		{
		}
		~VertexLayout(){}

		void							AddAttribute(G_FORMAT type, const std::string& semantics = "")
		{
			VertexAttr	attr;

			attr.semantics		= semantics == "" ? "undefined" : semantics;
//			attr.slot			= slot;
			attr.type			= type;

			m_layout.push_back(attr);
		}

		unsigned int					AttrCount() const
		{
			return (unsigned int)m_layout.size();
		}
		/*unsigned int					AttrSlot(unsigned int index) const
		{
			return m_layout[index].slot;
		}*/
		G_FORMAT						AttrType(unsigned int index) const
		{
			return m_layout[index].type;
		}
		
		const std::string&				AttrSemantics(unsigned int index) const
		{
			return m_layout[index].semantics;
		}
		unsigned int					VertexStride() const
		{
			unsigned int stride = 0;
			for(int i = 0; i < m_layout.size(); ++i)
			{
				const VertexAttr& attr = m_layout[i];

				stride += TypeBytes(attr.type);
			}
			return stride;
		}

		/*unsigned int					VertexStride(unsigned int slot) const
		{
			unsigned int stride = 0;
			for(int i = 0; i < m_layout.size(); ++i)
			{
				const VertexAttr& attr = m_layout[i];
				if(attr.slot == slot)
				{
					stride += TypeBytes(attr.type);
				}
			}
			return stride;
		}*/

		unsigned int					TypeBytes(G_FORMAT type) const
		{
			switch(type)
			{
			case G_FORMAT_R32G32B32A32_FLOAT:
			case G_FORMAT_R32G32B32A32_UINT:
			case G_FORMAT_R32G32B32A32_SINT:
				return 4 * 4;

			case G_FORMAT_R32G32B32_FLOAT:
			case G_FORMAT_R32G32B32_UINT:
			case G_FORMAT_R32G32B32_SINT:
				return 4 * 3;

			case G_FORMAT_R16G16B16A16_FLOAT:
			case G_FORMAT_R16G16B16A16_UINT:
			case G_FORMAT_R16G16B16A16_SINT:
				return 2 * 4;
			
			case G_FORMAT_R32G32_FLOAT:
			case G_FORMAT_R32G32_UINT:
			case G_FORMAT_R32G32_SINT:
				return 4 * 2;

			case G_FORMAT_R16G16_FLOAT:
			case G_FORMAT_R16G16_UINT:
			case G_FORMAT_R16G16_SINT:
				return 2 * 2;
			case G_FORMAT_R32_FLOAT:
			case G_FORMAT_R32_UINT:
			case G_FORMAT_R32_SINT:
				return 4;

			case G_FORMAT_R16_FLOAT:
			case G_FORMAT_R16_UINT:
			case G_FORMAT_R16_SINT:
				return 2;
			case G_FORMAT_R8_UINT:
			case G_FORMAT_R8_SINT:
				return 1;
			default:
				assert(0);
				break;
			}
			return 0;
		}
	private:
		std::vector<VertexAttr>		m_layout;
	};
}
