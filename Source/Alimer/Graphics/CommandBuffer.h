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

#include "../Core/Flags.h"
#include "../Graphics/Commands.h"
#include "../Graphics/VertexBuffer.h"
#include "../Graphics/IndexBuffer.h"
#include "../Graphics/RenderPass.h"
#include "../Graphics/Shader.h"
#include "../Graphics/PipelineState.h"
#include "../Math/Math.h"
#include "../Math/Color.h"

namespace Alimer
{
    class Graphics;

    /// Defines a command context for recording gpu commands.
    class ALIMER_API CommandContext 
    {
    public:
        CommandContext();

        /// Destructor.
        virtual ~CommandContext();

        /// Flush the command context and optionally wait for execution.
        virtual void Flush(bool wait = false) = 0;

        void BeginRenderPass(RenderPass* renderPass, const Color& clearColor, float clearDepth = 1.0f, uint8_t clearStencil = 0);

        void BeginRenderPass(RenderPass* renderPass,
            const Color* clearColors, uint32_t numClearColors,
            float clearDepth = 1.0f, uint8_t clearStencil = 0);

        void EndRenderPass();

        virtual void SetViewport(const Viewport& viewport) = 0;
        virtual void SetScissor(const Rectangle& scissor) = 0;

        void SetShader(Shader* shader);

        void SetVertexBuffer(uint32_t binding, VertexBuffer* buffer, uint64_t offset = 0, VertexInputRate inputRate = VertexInputRate::Vertex);
        void SetIndexBuffer(GpuBuffer* buffer, uint32_t offset = 0);
        
        void SetUniformBuffer(uint32_t set, uint32_t binding, GpuBuffer* buffer);
        void SetTexture(uint32_t binding, Texture* texture, ShaderStageFlags stage = ShaderStage::AllGraphics);

        // Draw methods
        void Draw(PrimitiveTopology topology, uint32_t vertexCount, uint32_t instanceCount = 1u, uint32_t vertexStart = 0u, uint32_t baseInstance = 0u);
        void DrawIndexed(PrimitiveTopology topology, uint32_t indexCount, uint32_t instanceCount = 1u, uint32_t startIndex = 0u);

        //void ExecuteCommands(uint32_t commandBufferCount, CommandBuffer* const* commandBuffers);

    protected:
        virtual void BeginRenderPassCore(RenderPass* renderPass, const Color* clearColors, uint32_t numClearColors, float clearDepth, uint8_t clearStencil) = 0;
        virtual void EndRenderPassCore() = 0;
        //virtual void ExecuteCommandsCore(uint32_t commandBufferCount, CommandBuffer* const* commandBuffers);

        virtual void SetUniformBufferCore(uint32_t set, uint32_t binding, GpuBuffer* buffer, uint64_t offset, uint64_t range) = 0;
        virtual void SetTextureCore(uint32_t binding, Texture* texture, ShaderStageFlags stage) = 0;

        virtual void SetShaderCore(Shader* shader) = 0;
        virtual void DrawCore(PrimitiveTopology topology, uint32_t vertexCount, uint32_t instanceCount, uint32_t vertexStart, uint32_t baseInstance) = 0;
        virtual void DrawIndexedCore(PrimitiveTopology topology, uint32_t indexCount, uint32_t instanceCount, uint32_t startIndex) = 0;
        virtual void SetVertexBufferCore(uint32_t binding, VertexBuffer* buffer, uint64_t offset, uint64_t stride, VertexInputRate inputRate) = 0;
        virtual void SetIndexBufferCore(GpuBuffer* buffer, uint32_t offset, IndexType indexType) = 0;

        inline bool IsInsideRenderPass() const
        {
            return _state == CommandBufferState::InRenderPass;
        }

        inline bool IsOutsideRenderPass() const
        {
            return _state == CommandBufferState::Ready;
        }

        enum class CommandBufferState
        {
            Ready,
            InRenderPass,
            Committed
        };

        CommandBufferState _state = CommandBufferState::Ready;

    private:
        DISALLOW_COPY_MOVE_AND_ASSIGN(CommandContext);
    };
}
