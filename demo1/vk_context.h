#pragma once

#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_win32.h>

#include <string>
#include <vector>

struct device_props
{
	device_props(VkPhysicalDevice gpu);
	//设备属性
	VkPhysicalDeviceProperties _properties{};
	//物理设备特性
	VkPhysicalDeviceFeatures _features{};
	//队列族信息
	std::vector<VkQueueFamilyProperties> _que_family_props;
};

struct ld_props
{
	ld_props(VkLayerProperties props, VkInstance instance, VkPhysicalDevice gpu);

	VkLayerProperties _props;
	std::vector<VkExtensionProperties> _instance_extension;
	std::vector<VkExtensionProperties> _device_extension;
};

class vk_context
{

public:
	vk_context();

private:
	//创建临时实例
	VkInstance create_temp_instance();
	//获取临时物理设备
	std::vector<VkPhysicalDevice> create_temp_physical_devices(VkInstance instance);
	//获取所有的层
	void available_layers();
	//获取所有实例支持的扩展
	void all_instance_extension();

public:
	//所有实例属性
	std::vector<device_props> _device_props;
	//所有验证层和扩展属性
	std::vector<ld_props> _ld_props;

	//设备属性
	VkPhysicalDeviceProperties _device_properties{};
	//物理设备特性
	VkPhysicalDeviceFeatures _device_features{};
	//队列族信息
	std::vector<VkQueueFamilyProperties> _device_que_family_props;
	//物理设备内存信息
	VkPhysicalDeviceMemoryProperties _memory_props;
	//选择物理设备
	int _chooes_device = 0;

	//可用的验证层
	std::vector<VkLayerProperties> _available_layers;
	//启用的验证层
	std::vector<const char*> _validation_layers{
		"VK_LAYER_KHRONOS_validation",
		"VK_LAYER_LUNARG_api_dump"
	};
	std::vector<const char*> _instance_extension_names{
		VK_KHR_SURFACE_EXTENSION_NAME,
		VK_KHR_WIN32_SURFACE_EXTENSION_NAME,
		VK_EXT_DEBUG_REPORT_EXTENSION_NAME
	};
	std::vector<const char*> _device_extension_names{
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};
	//是否启用验证层
	bool enable_validation_layers{ false };


	//应用名称
	std::string _app_name{ "vulkan" };
	//宽度
	int _width{ 0 };
	//长度
	int _height{ 0 };
};

