//
//  MyObjective-C-Interface.h
//  tvapp
//
//  Created by Foni Rewenig on 10/9/16.
//
//

#ifndef MyObjective_C_Interface_h
#define MyObjective_C_Interface_h

// This is the C "trampoline" function that will be used
// to invoke a specific Objective-C method FROM C++
void MyObjectDoSomethingWith (void *myObjectInstance, std::string parameter);
void stopBackgroundMusic();
#endif /* MyObjective_C_Interface_h */
