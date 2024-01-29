#pragma once

#include<vector>
#include<string>
#include<string>

#include<raylib.h>

#define TILE_SIZE 96
#define TOTAL_ANIM_FRAME (4)

class Tile{
    protected:
        Rectangle body;

        Texture2D texture;
        Texture2D debugbox;

        std::string name;
        std::string type;
        int id;

        int z_level;

        //animations
        bool hasAnimation;
        bool isRunningAnimation;

        bool hasCollision;

        //Debug var
        bool isTouchingMouse;
    public:

        //Getters
        std::string getName(){return name;}
        std::string getType(){return type;}

        float getX(){return body.x;}
        float getY(){return body.y;}

        int getZ(){return z_level;}
        int getID(){return id;}

        bool getHasAnimFrame(){return hasAnimation;}
        bool getHasCollision(){return hasCollision;}
        
        bool getIsRunningAnimation(){return isRunningAnimation;}

        Rectangle getBody(){return body;}
        Texture2D getTexture(){return texture;}
        
        //Seters
        void setBod(Rectangle bod){body=bod;}
        void setX(float x){body.x=x;}
        void setY(float y){body.y=y;}
        void runAnimation(){isRunningAnimation=true;}

        void Draw(bool is_debugging);

        //Constructors
        Tile(int id, Vector2 pos, int z_level);
        Tile();
};

std::vector<Tile> loadLevelFromFile(std::string file_path);
