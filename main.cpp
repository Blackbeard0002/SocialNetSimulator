/*
 COL106 - SocialNet Simulator
 */

#include <iostream>
#include "SocialNet.h" 

int main() {
    SocialNet sim;
    
    std::cout << "SocialNet Simulator started. Enter commands (or EXIT to quit)." << std::endl << std::endl;
    sim.run();
    
    return 0;
}

