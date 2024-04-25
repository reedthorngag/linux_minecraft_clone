
#include "../game_loop/game_loop.hpp"
#include "./startup/window.hpp"
#include "./startup/opengl.hpp"
#include "globals.hpp"


int main() {
    
    createWindow();
    setupOpenGL();

    GameLoop gameLoop(program);
    gameLoop.start();


    // WorldLoader worldLoader;
    // Generator gen;
    // double count = 0;
    // double total = RENDER_DISTANCE*2;

    // printf(" %d %d \n\n",RENDER_DISTANCE,RENDER_DISTANCE/2);

    // setbuf(stdout, NULL);
    // printf("\n\nGenerating chunks... 0%%");

    // for (int x=-(RENDER_DISTANCE/2); x<(RENDER_DISTANCE/2); x++) {
    //     for (int y=-(RENDER_DISTANCE/2);y<(RENDER_DISTANCE/2);y++) {
    //         int pos[2]{x,y};
    //         Chunk* chunk = new Chunk(program, new int[2]{x,y});
    //         chunks.setChunk(pos,chunk);
    //         gen.generateChunk(chunk);
    //         printf("\rGenerating chunks... %f",(count++/total));
    //     }
    // }

    // printf("\nMeshing chunks... 0%%");
    // count = 0;

    // for (int x=-(RENDER_DISTANCE/2); x<(RENDER_DISTANCE/2); x++) {
    //     for (int y=-(RENDER_DISTANCE/2);y<(RENDER_DISTANCE/2);y++) {
    //         int pos[2]{x,y};
    //         worldLoader.pushChunk(chunks.getChunk(pos));
    //         //printf("\rMeshing chunks... %f",(count++/total));
    //     }
    // }

    
    //printf("damnit: %d\n", XGrabPointer(dpy,win,true,0,GrabModeAsync,GrabModeAsync, win, None, CurrentTime));

    return 0;
}
