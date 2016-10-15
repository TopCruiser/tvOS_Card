//
//  MyObject.m
//  tvapp
//
//  Created by Foni Rewenig on 10/9/16.
//
//

#import "MyObject.h"
@implementation MyObject

extern AVAudioPlayer* _audioPlayer = nil;

// C "trampoline" function to invoke Objective-C method
void MyObjectDoSomethingWith (void *self, std::string aParameter)
{
    
    if(aParameter == "") return;
    
    NSString *str = [NSString stringWithCString:aParameter.c_str()
                                                encoding:[NSString defaultCStringEncoding]];
    NSString *path = [NSString stringWithFormat:@"%@/%@", [[NSBundle mainBundle] resourcePath], str];
    NSURL *soundUrl = [NSURL fileURLWithPath:path];
    
    // Create audio player object and initialize with URL to sound
    _audioPlayer = [[AVAudioPlayer alloc] initWithContentsOfURL:soundUrl error:nil];
    
    [_audioPlayer play];
}

void stopBackgroundMusic()
{
    [_audioPlayer stop];
}
//- (int) doSomethingWith:(void *) aParameter
//{
//    
//}

@end
