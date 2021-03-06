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

#include "../Graphics/Texture.h"
#include <array>

namespace Alimer
{
    enum class LoadAction
    {
        DontCare,
        Load,
        Clear
    };

    enum class StoreAction
    {
        DontCare,
        Store
    };

    struct RenderPassAttachment
    {
        Texture* texture = nullptr;
        uint32_t mipLevel = 0;
        uint32_t slice = 0;
        uint32_t depthPlane = 0;
        LoadAction loadAction = LoadAction::Clear;
        StoreAction storeAction = StoreAction::Store;
    };

    struct RenderPassDescription
    {
        RenderPassAttachment colorAttachments[MaxColorAttachments];
        RenderPassAttachment depthStencilAttachment;
        /// The width, in pixels, to constain the render target to.
        uint32_t width = 0;
        /// The height, in pixels, to constain the render target to.
        uint32_t height = 0;
        /// The number of active layers that all attachments must have for layered rendering.
        uint32_t layers = 1;
    };

    /// Defines a RenderPass class.
    class ALIMER_API RenderPass : public GpuResource, public RefCounted
    {
    protected:
        /// Constructor.
        RenderPass(Graphics* graphics, const RenderPassDescription* descriptor);

    public:
        /// Destructor.
        virtual ~RenderPass() = default;

        uint32_t GetWidth() const { return _width; }
        uint32_t GetHeight() const { return _height; }
        uint32_t GetLayers() const { return _layers; }
        uint32_t GetColorAttachmentsCount() const { return _colorAttachmentsCount; }
        const RenderPassAttachment& GetColorAttachment(uint32_t index) const { return _colorAttachments[index]; }

    protected:
        uint32_t _width;
        uint32_t _height;
        uint32_t _layers;
        uint32_t _colorAttachmentsCount;
        std::array<RenderPassAttachment, MaxColorAttachments> _colorAttachments;
        RenderPassAttachment _depthStencilAttachment;
    };
}
