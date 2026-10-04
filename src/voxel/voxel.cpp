#include "voxel.h"
#include <raylib.h>



    void voxel::draw_triang(Vector3 pos1,Vector3 pos2,Vector3 pos3, Color color){

        DrawTriangle3D(pos1,pos2,pos3,color);

    }


    void voxel::draw_rectangle(Vector3 pos1,Vector3 pos2,Vector3 pos3,Vector3 pos4, Color color)
    {


        voxel::draw_triang(
                pos1,  // A - левая нижняя
                pos2,  // B - верхняя левая
                pos3,  // C - правая нижняя
                color);

        voxel::draw_triang(
            pos2,// B
            pos4, // D - верхняя правая
            pos3, // B
            color);

    }


        void voxel::draw_cube(Vector3 position, float size, Color fill, Color wire) {
            DrawCube(position, size, size, size, fill);
            DrawCubeWires(position, size, size, size, wire);
    }






        //? багов - мало, фпс - много
        // voxel::draw_triang(
        //         Vector3{ 0, 0, 0 },  // A
        //         Vector3{ 1, 0, 0 },  // B
        //         Vector3{ 0, 1, 0 },  // C
        //     RAYWHITE);

        // voxel::draw_triang(
        //     Vector3{ 1, 0, 0 },
        //     Vector3{ 1, 1, 0 }, //D
        //     Vector3{ 0, 1, 0 },
        //     RAYWHITE);
