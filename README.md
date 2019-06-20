# CefSln
Cef

一步步CEF（1）之编译libcef_dll_wrapper.lib
https://blog.csdn.net/ftpleopard/article/details/84870054

工程--属性--C/C++  --预处理器定义：
WRAPPING_CEF_SHARED
NOMINMAX

>osr_d3d11_win.obj : error LNK2019: 无法解析的外部符号 _D3D11CreateDevice@40，
该符号在函数 "public: static class std::shared_ptr<class client::d3d11::Device> 
__cdecl client::d3d11::Device::create(void)" (?create@Device@d3d11@client@@SA?AV?$shared_ptr@VDevice@d3d11@client@@@std@@XZ) 中被引用
解决方法：
#pragma comment(lib, "D3D11.lib")


