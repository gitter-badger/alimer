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

#include "../Graphics.h"
#include "../../Util/HashMap.h"
#include "VulkanPrerequisites.h"

namespace Alimer
{
	/// Vulkan graphics backend.
	class VulkanGraphics final : public Graphics
	{
	public:
		/// Is backend supported?
		static bool IsSupported();

		/// Construct. Set parent shader and defines but do not compile yet.
		VulkanGraphics(bool validation, const std::string& applicationName);
		/// Destruct.
		~VulkanGraphics() override;

		bool WaitIdle() override;
		bool Initialize(const SharedPtr<Window>& window) override;
		SharedPtr<Texture> AcquireNextImage() override;
		bool Present() override;

		SharedPtr<CommandBuffer> CreateCommandBuffer() override;

		GpuBufferPtr CreateBuffer(BufferUsage usage, uint32_t elementCount, uint32_t elementSize, const void* initialData) override;
		PipelineLayoutPtr CreatePipelineLayout() override;
		std::shared_ptr<Shader> CreateShader(const std::string& name) override;
		std::shared_ptr<Shader> CreateShader(const ShaderBytecode& vertex, const ShaderBytecode& fragment) override;
		PipelineStatePtr CreateRenderPipelineState(const RenderPipelineDescriptor& descriptor) override;

		VkInstance GetInstance() const { return _instance; }
		VkDevice GetLogicalDevice() const { return _logicalDevice; }

		/**
		* Get the index of a queue family that supports the requested queue flags
		*
		* @param queueFlags Queue flags to find a queue family index for
		*
		* @return Index of the queue family index that matches the flags
		*
		* @throw Throws an exception if no queue family index could be found that supports the requested flags
		*/
		uint32_t GetQueueFamilyIndex(VkQueueFlagBits queueFlags)
		{
			// Dedicated queue for compute
			// Try to find a queue family index that supports compute but not graphics
			const uint32_t queueFamilyPropsCount = static_cast<uint32_t>(_queueFamilyProperties.size());
			if (queueFlags & VK_QUEUE_COMPUTE_BIT)
			{
				for (uint32_t i = 0; i < queueFamilyPropsCount; i++)
				{
					if ((_queueFamilyProperties[i].queueFlags & queueFlags) && ((_queueFamilyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) == 0)) {
						return i;
						break;
					}
				}
			}

			// For other queue types or if no separate compute queue is present, return the first one to support the requested flags
			for (uint32_t i = 0; i < queueFamilyPropsCount; i++)
			{
				if (_queueFamilyProperties[i].queueFlags & queueFlags) {
					return i;
					break;
				}
			}

			throw std::runtime_error("Could not find a matching queue family index");
		}

	private:
		void Finalize() override;

		bool PrepareDraw(PrimitiveTopology topology);

		VkInstance _instance = VK_NULL_HANDLE;
		VkDebugReportCallbackEXT _debugCallback = VK_NULL_HANDLE;

		// PhysicalDevice
		VkPhysicalDevice _vkPhysicalDevice = VK_NULL_HANDLE;
		VkPhysicalDeviceProperties _deviceProperties;
		VkPhysicalDeviceFeatures _deviceFeatures;
		VkPhysicalDeviceMemoryProperties _deviceMemoryProperties;
		std::vector<VkQueueFamilyProperties> _queueFamilyProperties;

		// LogicalDevice
		struct {
			uint32_t graphics;
			uint32_t compute;
		} _queueFamilyIndices;

		VkDevice _logicalDevice = VK_NULL_HANDLE;

		// Queue's.
		VkQueue _graphicsQueue = VK_NULL_HANDLE;
		VkQueue _computeQueue = VK_NULL_HANDLE;

		VkSurfaceKHR _surface = VK_NULL_HANDLE;
		VkSurfaceFormatKHR _swapchainFormat{};
		VkSwapchainKHR _swapchain = VK_NULL_HANDLE;
		uint32_t _swapchainImageIndex = 0;

		// Sync semaphores
		VkSemaphore _imageAcquiredSemaphore = VK_NULL_HANDLE;
	};
}