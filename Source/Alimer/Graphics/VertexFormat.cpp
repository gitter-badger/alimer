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

#include "../Graphics/VertexFormat.h"

namespace Alimer
{
    VertexInputFormat::VertexInputFormat(const VertexInputFormatDescriptor* descriptor)
    {
        // Check if we need to auto offset.
        bool useAutoOffset = true;
        for (size_t i = 0; i < descriptor->attributesCount; ++i)
        {
            if (descriptor->attributes[i].offset != 0)
            {
                useAutoOffset = false;
                break;
            }
        }

        uint32_t stride = 0;

        _attributes.resize(descriptor->attributesCount);
        for (size_t i = 0; i < descriptor->attributesCount; ++i)
        {
            _attributes[i] = descriptor->attributes[i];
            _attributes[i].offset = useAutoOffset ? stride : descriptor->attributes[i].offset;
            stride += GetVertexFormatSize(descriptor->attributes[i].format);
        }

        // Compute default single buffer layout if none specified.
        if (!descriptor->layoutsCount)
        {
            _layouts.push_back({ 0, stride, VertexInputRate::Vertex });
        }
    }

    VertexInputFormat::~VertexInputFormat()
    {
    }
}
