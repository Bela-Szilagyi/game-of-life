#include <iostream>

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
    //n
    if (y > 0 && grid[(y-1)*sizeX+x].state == 1) ++result;
    //ne
    if (y > 0 && x < sizeX-1 && grid[(y-1)*sizeX+x+1].state == 1) ++result;
    //e
    if (x < sizeX-1 && grid[y*sizeX+x+1].state == 1) ++result;
    //se
    if (y < sizeY-1 && x < sizeX-1 && grid[(y+1)*sizeX+x+1].state == 1) ++result;
    //s
    if (y < sizeY-1 && grid[(y+1)*sizeX+x].state == 1) ++result;
    //sw
    if (y < sizeY-1 && x > 0 && grid[(y+1)*sizeX+x-1].state == 1) ++result;
    //w
    if (x > 0 && grid[y*sizeX+x-1].state == 1) ++result;
    //nw
    if (y > 0 && x > 0 && grid[(y-1)*sizeX+x-1].state == 1) ++result;

    return result;
}

void printGrid() {
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
    //toad 6x6
    grid[2*sizeX+2].state = 1;
    grid[2*sizeX+3].state = 1;
    grid[2*sizeX+4].state = 1;
    grid[3*sizeX+1].state = 1;
    grid[3*sizeX+2].state = 1;
    grid[3*sizeX+3].state = 1;
    printGrid();
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
    //step
    for (int count = 0; count < 10; ++count) {
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