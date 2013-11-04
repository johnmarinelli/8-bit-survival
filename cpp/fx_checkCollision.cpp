#include "fx_checkCollision.h"

bool check_collision( SDL_Rect &A, SDL_Rect &B )
{
	//The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;
        
    //Calculate the sides of rect B
    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;
            
    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }
    
    if( topA >= bottomB )
    {
        return false;
    }
    
    if( rightA <= leftB )
    {
        return false;
    }
    
    if( leftA >= rightB )
    {
        return false;
    }
    
    //If none of the sides from A are outside B
    return true;
}

bool check_player_Collision( SDL_Rect &A, SDL_Rect &B )
{
	//The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;
        
    //Calculate the sides of rect B
    leftB = B.x;
    rightB = /*(B.x - 5)*/B.x + B.w;
    topB = B.y;
    bottomB = /*(B.y - 10)*/B.y + B.h;
            
    //If any of the sides from A are outside of B
    if( bottomA <= topB + 7)
    {
        return false;
    }
    
    if( topA >= bottomB )
    {
        return false;
    }
    
    if( rightA <= leftB + 7)
    {
        return false;
    }
    
    if( leftA >= rightB )
    {
        return false;
    }
    
    //If none of the sides from A are outside B
    return true;
}

double distance(const int &x1, const int &y1, const int &x2, const int &y2)
{
	return sqrt(pow((double)x2-x1, 2) + pow((double)y2-y1, 2));
}

int inverted_sound_Distance( const int &pX, const int &pY, const int &rX, const int &rY )
{
	int d = (int)sqrt(pow((double)rX-pX, 2) + pow((double)rY-pY, 2));
	if (d > 255){
		d = 255;
	}
	else if (d <= 0){
		d = 1;
	}

	d = 256 - d;

	return d;
}

int sound_Distance( const int &pX, const int &pY, const int &rX, const int &rY )
{
	int d = (int)sqrt(pow((double)rX-pX, 2) + pow((double)rY-pY, 2));
	if (d > 255){
		d = 255;
	}
	else if (d <= 0){
		d = 1;
	}

	return d;
}


int getAngle( const int & pX, const int &pY, const int &rX, const int &rY )
{
	int dX = pX - rX;
	int dY = rY - pY;

	return (int)(atan2( (double)dY, (double)dX ) * 180/3.14);
}

bool check_collision( const circle &a, const SDL_Rect &b )
{
	/*closest points*/
	int cX, cY;

	if ( a.x < b.x ){
		cX = b.x;
	}
	else if ( a.x > b.x + b.w ){
		cX = b.x + b.w;
	}
	else{
		cX = a.x;
	}

	if ( a.y < b.y ){
		cY = b.y;
	}
	else if ( a.y > b.y + b.h ){
		cY = b.y + b.h;
	}
	else{
		cY = a.y;
	}

	if ( distance(a.x, a.y, cX, cY) < a.r ){
		return true;
	}
	else
		return false;
}