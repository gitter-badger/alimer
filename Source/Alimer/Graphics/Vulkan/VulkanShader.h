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

#include "../Shader.h"
#include "VulkanPrerequisites.h"
#include "../../Util/HashMap.h"
#include <vector>

namespace Alimer
{
    class VulkanGraphics;
    class VulkanPipelineLayout;

    /// D3D12 Shader implementation.
    class VulkanShader final : public Shader
    {
    public:
        /// Constructor.
        VulkanShader(VulkanGraphics* graphics, const void *pCode, size_t codeSize);
        /// Constructor.
        VulkanShader(VulkanGraphics* graphics,
            const void *pVertexCode, size_t vertexCodeSize,
            const void *pFragmentCode, size_t fragmentCodeSize);

        ~VulkanShader() override;

        VkShaderModule GetVkShaderModule(unsigned stage) const { return _shaderModules[stage]; }
        VkShaderModule GetVkShaderModule(ShaderStage stage) const;
        VulkanPipelineLayout* GetPipelineLayout() const { return _pipelineLayout; }
        VkPipeline GetGraphicsPipeline(Hash hash);
        void AddPipeline(Hash hash, VkPipeline pipeline);

    private:
        VkDevice _logicalDevice;
        VkShaderModule _shaderModules[static_cast<unsigned>(ShaderStage::Count)] = {};
        VulkanPipelineLayout* _pipelineLayout = nullptr;
        HashMap<VkPipeline> _graphicsPipelineCache;
    };
}
