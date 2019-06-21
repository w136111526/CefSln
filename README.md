# CefSln
Cef

libcef.lib
libcef_dll.lib
D3D11.lib
imm32.lib
OPENGL32.LIB

$(ProjectDir)\include 
$(SolutionDir)sdk\cef
$(SolutionDir)build\

cef下加载flash
https://blog.csdn.net/x356982611/article/details/52291122

一步步CEF（1）之编译libcef_dll_wrapper.lib
https://blog.csdn.net/ftpleopard/article/details/84870054

MFC对话框中调用CEF浏览器控件（使用2018年新版本的CEF SDK）
https://blog.csdn.net/toshiba689/article/details/86751028

工程--属性--C/C++  --预处理器定义：
WRAPPING_CEF_SHARED
NOMINMAX

语法错误: 未定义标识符“uint64_t”
添加头文件#include <stdint.h>

>osr_d3d11_win.obj : error LNK2019: 无法解析的外部符号 _D3D11CreateDevice@40，
该符号在函数 "public: static class std::shared_ptr<class client::d3d11::Device> 
__cdecl client::d3d11::Device::create(void)" (?create@Device@d3d11@client@@SA?AV?$shared_ptr@VDevice@d3d11@client@@@std@@XZ) 中被引用
解决方法：
#pragma comment(lib, "D3D11.lib")

osr_ime_handler_win.obj : error LNK2019: 无法解析的外部符号 _ImmGetContext@4，该符号在函数 "public: virtual void __thiscall client::OsrImeHandlerWin::CancelIME(void)" (?CancelIME@OsrImeHandlerWin@client@@UAEXXZ) 中被引用
1>osr_ime_handler_win.obj : error LNK2019: 无法解析的外部符号 _ImmReleaseContext@8，该符号在函数 "public: virtual void __thiscall client::OsrImeHandlerWin::CancelIME(void)" (?CancelIME@OsrImeHandlerWin@client@@UAEXXZ) 中被引用
1>osr_ime_handler_win.obj : error LNK2019: 无法解析的外部符号 _ImmAssociateContextEx@12，该符号在函数 "public: virtual void __thiscall client::OsrImeHandlerWin::DisableIME(void)" (?DisableIME@OsrImeHandlerWin@client@@UAEXXZ) 中被引用
1>osr_ime_handler_win.obj : error LNK2019: 无法解析的外部符号 _ImmGetCompositionStringW@16，该符号在函数 "private: void __thiscall client::OsrImeHandlerWin::GetCompositionInfo(struct HIMC__ *,long,class CefStringBase<struct CefStringTraitsUTF16> 
1>osr_ime_handler_win.obj : error LNK2019: 无法解析的外部符号 _ImmNotifyIME@16，该符号在函数 "public: virtual void __thiscall client::OsrImeHandlerWin::CancelIME(void)" (?CancelIME@OsrImeHandlerWin@client@@UAEXXZ) 中被引用
1>osr_ime_handler_win.obj : error LNK2019: 无法解析的外部符号 _ImmSetCandidateWindow@8，该符号在函数 "public: void __thiscall client::OsrImeHandlerWin::MoveImeWindow(void)" (?MoveImeWindow@OsrImeHandlerWin@client@@QAEXXZ) 中被引用
解决方法：
#pragma comment(lib, "imm32.lib")

1>osr_renderer.obj : error LNK2019: 无法解析的外部符号 __imp__glBegin@4，该符号在函数 "public: void __thiscall client::OsrRenderer::Render(void)" (?Render@OsrRenderer@client@@QAEXXZ) 中被引用
1>osr_renderer.obj : error LNK2019: 无法解析的外部符号 __imp__glBindTexture@8，该符号在函数 "public: void __thiscall client::OsrRenderer::Initialize(void)" (?Initialize@OsrRenderer@client@@QAEXXZ) 中被引用
1>osr_renderer.obj : error LNK2019: 无法解析的外部符号 __imp__glBlendFunc@8，该符号在函数 "public: void __thiscall client::OsrRenderer::Render(void)" (?Render@OsrRenderer@client@@QAEXXZ) 中被引用
1>osr_renderer.obj : error LNK2019: 无法解析的外部符号 __imp__glClear@4，该符号在函数 "public: void __thiscall client::OsrRenderer::Render(void)" (?Render@OsrRenderer@client@@QAEXXZ) 中被引用
1>osr_renderer.obj : error LNK2019: 无法解析的外部符号 __imp__glClearColor@16，该符号在函数 "public: void __thiscall client::OsrRenderer::Initialize(void)" (?Initialize@OsrRenderer@client@@QAEXXZ) 中被引用
1>osr_renderer.obj : error LNK2019: 无法解析的外部符号 __imp__glColor3f@12，该符号在函数 "public: void __thiscall client::OsrRenderer::Render(void)" (?Render@OsrRenderer@client@@QAEXXZ) 中被引用
1>osr_renderer.obj : error LNK2019: 无法解析的外部符号 __imp__glColor4f@16，该符号在函数 "public: void __thiscall client::OsrRendere
解决方法：
#pragma comment(lib, "OpenGL32.lib")
