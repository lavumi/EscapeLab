#include "Character.hpp"
#include "../Map/FloorMap.hpp"
#include "FieldOfView.hpp"

FieldOfView::FieldOfView(BaseCharacter* player){
    this->player = player;
}

FieldOfView::~FieldOfView(){

}


void FieldOfView::Compute(Vector2 origin, int rangeLimit){

    _setVisible(origin.x, origin.y);
    for(int octant = 0; octant < 8; octant++) {
            _compute(octant, origin, rangeLimit, 1, Slope(1, 1), Slope(0, 1));
    }
}
        


void FieldOfView::_compute(int octant, Vector2 origin, int rangeLimit, int x, Slope top, Slope bottom) {
    for (; x <= rangeLimit; x++) {
        int topY;
        if (top.X == 1) {
            topY = x;
        } else {
            topY = ((x * 2 - 1) * top.Y + top.X) / (top.X * 2);

            if (BlocksLight(x, topY, octant, origin)) {
                if (top.GreaterOrEqual(topY * 2 + 1, x * 2) && !BlocksLight(x, topY + 1, octant, origin))
                    topY++;
            } else {
                int ax = x * 2;
                if (BlocksLight(x + 1, topY + 1, octant, origin))
                    ax++;
                if (top.Greater(topY * 2 + 1, ax))
                    topY++;
            }
        }

        int bottomY;
        if (bottom.Y == 0) {
            bottomY = 0;
        } else {
            bottomY = ((x * 2 - 1) * bottom.Y + bottom.X) / (bottom.X * 2);
            if (bottom.GreaterOrEqual(bottomY * 2 + 1, x * 2) && BlocksLight(x, bottomY, octant, origin) &&
                !BlocksLight(x, bottomY + 1, octant, origin)) {
                bottomY++;
            }
        }

        int wasOpaque = -1;
        for (int y = topY; (int)y >= (int)bottomY; y--) {
            if (rangeLimit < 0  
               || GetDistance((int)x, (int)y) <= rangeLimit) {
                bool isOpaque = BlocksLight(x, y, octant, origin);
                bool isVisible =
                    isOpaque || ((y != topY || top.Greater(y * 4 - 1, x * 4 + 1)) && (y != bottomY || bottom.Less(y * 4 + 1, x * 4 - 1)));
                if (isVisible)
                    SetVisible(x, y, octant, origin);

                if (x != rangeLimit) {
                    if (isOpaque) {
                        if (wasOpaque == 0) {
                            int nx = x * 2, ny = y * 2 + 1;
                            if (BlocksLight(x, y + 1, octant, origin))
                                nx--;
                            if (top.Greater(ny, nx)) {
                                if (y == bottomY) {
                                    bottom = Slope(ny, nx);
                                    break;
                                } else
                                    _compute(octant, origin, rangeLimit, x + 1, top, Slope(ny, nx));
                            } else {
                                if (y == bottomY)
                                    return;
                            }
                        }
                        wasOpaque = 1;
                    } else {
                        if (wasOpaque > 0) {
                            int nx = x * 2, ny = y * 2 + 1;
                            if (BlocksLight(x + 1, y + 1, octant, origin))
                                nx++;
                            if (bottom.GreaterOrEqual(ny, nx))
                                return;
                            top = Slope(ny, nx);
                        }
                        wasOpaque = 0;
                    }
                }
            }
        }
        if (wasOpaque != 0)
            break;
    }
}

bool FieldOfView::BlocksLight(int x, int y, int octant, Vector2 origin) {
    int nx = origin.x, ny = origin.y;
    switch (octant) {
        case 0:
            nx += x;
            ny -= y;
            break;
        case 1:
            nx += y;
            ny -= x;
            break;
        case 2:
            nx -= y;
            ny -= x;
            break;
        case 3:
            nx -= x;
            ny -= y;
            break;
        case 4:
            nx -= x;
            ny += y;
            break;
        case 5:
            nx -= y;
            ny += x;
            break;
        case 6:
            nx += y;
            ny += x;
            break;
        case 7:
            nx += x;
            ny += y;
            break;
    }
    return _blocksLight((int)nx, (int)ny);
}

void FieldOfView::SetVisible(int x, int y, int octant, Vector2 origin) {
    int nx = origin.x, ny = origin.y;
    switch (octant) {
        case 0:
            nx += x;
            ny -= y;
            break;
        case 1:
            nx += y;
            ny -= x;
            break;
        case 2:
            nx -= y;
            ny -= x;
            break;
        case 3:
            nx -= x;
            ny -= y;
            break;
        case 4:
            nx -= x;
            ny += y;
            break;
        case 5:
            nx -= y;
            ny += x;
            break;
        case 6:
            nx += y;
            ny += x;
            break;
        case 7:
            nx += x;
            ny += y;
            break;
    }


    _setVisible((int)nx, (int)ny);
}

bool FieldOfView::_blocksLight(int x,int y){

    return player->GetCurrentMap()->isVisible(x, y);
}

int FieldOfView::GetDistance(int x, int y){


    return sqrt(x * x + y * y);     //Circle Sight
    //return x + y;                 //Diamond Sight
    //return x > y ? x : y;         //Square Sight
}

void FieldOfView::_setVisible(int x, int y){
    player->GetCurrentMap()->setVisible(x, y);
}