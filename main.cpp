#include <iostream>
#include <zconf.h>

class cell {
public:
    cell() {}
    virtual ~cell() {}
    bool state; // 0-dead, 1-live
    bool nextState;
};

const int sizeX = 6;
const int sizeY = 6;
cell grid[sizeX*sizeY];

int getNrOfLiveNeighbours(int x, int y) {
    int result = 0;
    int nX, nY;
    //n
    nX = x;
    nY = y-1;
    if (nY < 0) nY = sizeY-1;
    if (grid[(nY)*sizeX+nX].state == 1) ++result;
    //ne
    nX = x+1;
    nY = y-1;
    if (nY < 0) nY = sizeY-1;
    if (nX>sizeX-1) nX = 0;
    if (grid[(nY)*sizeX+nX].state == 1) ++result;
    //e
    nX = x+1;
    nY = y;
    if (nX>sizeX-1) nX = 0;
    if (grid[(nY)*sizeX+nX].state == 1) ++result;
    //se
    nX = x+1;
    nY = y+1;
    if (nX>sizeX-1) nX = 0;
    if (nY>sizeY-1) nY = 0;
    if (grid[(nY)*sizeX+nX].state == 1) ++result;
    //s
    nX = x;
    nY = y+1;
    if (nY>sizeY-1) nY = 0;
    if (grid[(nY)*sizeX+nX].state == 1) ++result;
    //sw
    nX = x-1;
    nY = y+1;
    if (nX < 0) nX = sizeX-1;
    if (nY>sizeY-1) nY = 0;
    if (grid[(nY)*sizeX+nX].state == 1) ++result;
    //w
    nX = x-1;
    nY = y;
    if (nX < 0) nX = sizeX-1;
    if (grid[(nY)*sizeX+nX].state == 1) ++result;
    //nw
    nX = x-1;
    nY = y-1;
    if (nX < 0) nX = sizeX-1;
    if (nY<0) nY = sizeY-1;
    if (grid[(nY)*sizeX+nX].state == 1) ++result;

    return result;
}

void printGrid() {
    unsigned int microseconds = 500000;
    usleep(microseconds);
    std::cout<<"\033[2J\033[1;1H";
    for (int y = 0; y < sizeY; ++y) {
        for (int x = 0; x < sizeX; ++x) {
            if (grid[y*sizeX+x].state == 0) {
                std::cout<<'-';
            } else {
                std::cout<<'+';
            }
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
}
int main() {
    //initGrid
    for (int y = 0; y < sizeY; ++y) {
        for (int x = 0; x < sizeX; ++x) {
            grid[y*sizeX+x].state = 0;
            grid[y*sizeX+x].nextState = 0;
        }
    }
    /*//blinker 5x5
    grid[2*sizeX+1].state = 1;
    grid[2*sizeX+2].state = 1;
    grid[2*sizeX+3].state = 1;
    printGrid();*/
    /*//toad 6x6
    grid[2*sizeX+2].state = 1;
    grid[2*sizeX+3].state = 1;
    grid[2*sizeX+4].state = 1;
    grid[3*sizeX+1].state = 1;
    grid[3*sizeX+2].state = 1;
    grid[3*sizeX+3].state = 1;
    printGrid();*/
    /*//beacon 6x6
    grid[1*sizeX+1].state = 1;
    grid[1*sizeX+2].state = 1;
    grid[2*sizeX+1].state = 1;
    grid[2*sizeX+2].state = 1;
    grid[3*sizeX+3].state = 1;
    grid[3*sizeX+4].state = 1;
    grid[4*sizeX+3].state = 1;
    grid[4*sizeX+4].state = 1;
    printGrid();*/
    //glider 6x6
    grid[0*sizeX+2].state = 1;
    grid[1*sizeX+2].state = 1;
    grid[2*sizeX+2].state = 1;
    grid[2*sizeX+1].state = 1;
    grid[1*sizeX+0].state = 1;
    printGrid();
    //step
    for (int count = 0; count < 100; ++count) {
        for (int y = 0; y < sizeY; ++y) {
            for (int x = 0;x < sizeX; ++x) {
                int nrOfLiveNeighbours = getNrOfLiveNeighbours(x, y);
                if ( grid[y*sizeX+x].state == 1 && ( nrOfLiveNeighbours < 2 || nrOfLiveNeighbours > 3 ) ) {
                    grid[y*sizeX+x].nextState = 0;
                } else if ( grid[y*sizeX+x].state == 1 && ( nrOfLiveNeighbours == 2 || nrOfLiveNeighbours == 3 ) ) {
                    grid[y*sizeX+x].nextState = 1;
                } else if ( grid[y*sizeX+x].state == 0 &&  nrOfLiveNeighbours == 3) {
                    grid[y * sizeX + x].nextState = 1;
                }
            }
        }
        for (int nextY = 0; nextY < sizeY; ++nextY) {
            for (int nextX = 0; nextX < sizeX; ++nextX) {
                grid[nextY * sizeX + nextX].state = grid[nextY * sizeX + nextX].nextState;
            }
        }
        printGrid();
    }
    return 0;
}