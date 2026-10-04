#ifndef VOXEL_H
#define VOXEL_H

#pragma once


#define BLUE_DARK CLITERAL(Color){50,50,150,250}


#include <raylib.h>

class voxel
{
public:

        static void draw_triang(Vector3 pos1,Vector3 pos2,Vector3 pos3, Color color);
        static void draw_rectangle(Vector3 pos1,Vector3 pos2,Vector3 pos3,Vector3 pos4, Color color);
        static void draw_cube(Vector3 position, float size, Color fill, Color wire);




private:

};

#endif