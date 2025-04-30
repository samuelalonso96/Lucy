#include "Window.hpp"
#include <AppKit/AppKit.h>
#include <QuartzCore/QuartzCore.h>

namespace Lucy::UI
{
    namespace Detail
    {
        bool WindowLoaded = false;
    }

    Window window;

    auto Window::Init() noexcept -> void
    {
        if(not Detail::WindowLoaded)
        {
            Detail::WindowLoaded = true;
            NSWindow* v_window = [[NSWindow alloc] initWithContentRect: [[NSScreen mainScreen] frame] styleMask:
            NSWindowStyleMaskResizable | NSWindowStyleMaskClosable | NSWindowStyleMaskTitled |
            NSWindowStyleMaskMiniaturizable backing: NSBackingStoreBuffered defer: NO];
            v_window.title = [NSString stringWithUTF8String: lucy_title];
            v_window.contentView = [[NSView alloc] init];
            v_window.contentView.wantsLayer = YES;
            v_window.contentView.layer = [CAMetalLayer layer];
            [v_window makeKeyAndOrderFront: nil];
            m_window = v_window;
        }
    }

    [[nodiscard]] auto Window::Layer() noexcept -> void*
    {
        return static_cast<NSWindow*>(m_window).contentView.layer;
    }

    auto Window::Title(const char* title) noexcept -> void
    {
        ((__bridge NSWindow*)m_window).title = [NSString stringWithUTF8String: title];
    }
}