//
// Copyright (c) 2018 Amer Koleci and contributors.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#pragma once

#include "Graphics/Shader.h"
#include "D3D12Helpers.h"

namespace Alimer
{
	class D3D12Graphics;

	/// D3D12 Shader implementation.
	class D3D12Shader final : public Shader
	{
	public:
		/// Constructor.
		D3D12Shader(D3D12Graphics* graphics, const ShaderStageDescription& desc);
		/// Constructor.
		D3D12Shader(D3D12Graphics* graphics, const ShaderStageDescription& vertex, const ShaderStageDescription& fragment);

		/// Destructor.
		~D3D12Shader() override;

		bool HasBytecode(ShaderStage stage);
		std::vector<uint8_t> AcquireBytecode(ShaderStage stage);

        ID3D12RootSignature* GetD3DRootSignature() const { return _rootSignature.Get(); }

	private:
        void InitializeRootSignature();

        D3D12Graphics* _graphics;
		std::vector<uint8_t> _shaders[static_cast<unsigned>(ShaderStage::Count)];
        ComPtr<ID3D12RootSignature> _rootSignature;
	};
}
