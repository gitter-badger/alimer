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

#include "../Graphics/GpuResource.h"
#include <vector>

namespace Alimer
{
    struct VertexAttribute
    {
        static constexpr uint32_t POSITION = 0;
        static constexpr uint32_t NORMAL = 1;
        static constexpr uint32_t TANGENT = 2;
        static constexpr uint32_t COLOR = 3;
        static constexpr uint32_t UV0 = 4;
        static constexpr uint32_t UV1 = 5;
        static constexpr uint32_t BONE_INDICES = 6;
        static constexpr uint32_t ONE_WEIGHTS = 7;
    };

    struct VertexAttributeDescriptor
    {
        uint32_t        location;
        uint32_t        bufferIndex;
        VertexFormat    format;
        uint32_t        offset;
    };

    struct VertexBufferLayoutDescriptor
    {
        uint32_t        bufferIndex;
        uint32_t        stride;
        VertexInputRate inputRate;
    };

    struct VertexInputFormatDescriptor
    {
        uint32_t attributesCount;
        const VertexAttributeDescriptor* attributes;
        uint32_t layoutsCount;
        const VertexBufferLayoutDescriptor* layouts;
    };

    /// Defines a GPU VertexFormat.
    class VertexInputFormat : public RefCounted
    {
    protected:
        /// Constructor.
        VertexInputFormat(const VertexInputFormatDescriptor* descriptor);

    public:
        /// Destructor.
        virtual ~VertexInputFormat();

        /// Return number of vertex attributes.
        size_t GetAttributesCount() const { return _attributes.size(); }

        /// Return attribute at index.
        VertexAttributeDescriptor GetAttribute(size_t index) const { return _attributes[index]; }

        /// Return number of vertex layouts.
        size_t GetLayoutsCount() const { return _layouts.size(); }

        /// Return layout at index.
        VertexBufferLayoutDescriptor GetLayout(size_t index) const { return _layouts[index]; }

    protected:
        /// Vertex elements.
        std::vector<VertexAttributeDescriptor> _attributes;

        /// VertexFormat stride.
        std::vector<VertexBufferLayoutDescriptor> _layouts;
    };
}
