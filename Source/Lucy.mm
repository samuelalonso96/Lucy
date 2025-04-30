#ifdef lucy_mac
#include <AppKit/AppKit.h>
#include <QuartzCore/QuartzCore.h>
#include "Experimental/Game.hpp"
#include "Experimental/Window.hpp"
#include "Experimental/Camera.hpp"
#include "Experimental/Renderer.hpp"

@interface LucyAppRenderer : NSObject<CAMetalDisplayLinkDelegate>
@end
@implementation LucyAppRenderer
- (void)metalDisplayLink:(nonnull CAMetalDisplayLink*) link needsUpdate:(nonnull
CAMetalDisplayLinkUpdate*) update
{
    Lucy::Graphics::Detail::RendererUpdating = true;
    Lucy::Graphics::renderer.Update(update.drawable);
    Lucy::Engine::main.Render();
    Lucy::Graphics::Detail::RendererUpdating = false;
    ::lucy_game::Update();
    Lucy::Graphics::Detail::RendererUpdating = true;
    Lucy::Graphics::renderer.Dispatch(update.drawable);
    Lucy::Graphics::Detail::RendererUpdating = false;
}
@end

@interface LucyAppDel : NSObject<NSApplicationDelegate, NSWindowDelegate>{}
@end
@implementation LucyAppDel
-(id)init
{
    if (self = [super init])
    {
        Lucy::UI::window.Init();
        Lucy::Graphics::renderer.Init([[LucyAppRenderer alloc] init]);
        Lucy::Engine::main = Lucy::Engine::Camera::Create();
        ::lucy_game::Start();
        [static_cast<CAMetalDisplayLink*>(Lucy::Graphics::renderer.Display()) addToRunLoop: [
        NSRunLoop currentRunLoop] forMode: NSRunLoopCommonModes];
    }
    return self;
}

-(BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication*) sender
{
    return YES;
}

-(void)applicationWillTerminate:(NSNotification*)notification
{
    ::lucy_game::Finish();
}
@end

int main()
{
    NSApplication* nsapp = [NSApplication sharedApplication];
    [nsapp setDelegate: [[LucyAppDel alloc] init]];
    [nsapp run];
    [nsapp release];
}

#endif