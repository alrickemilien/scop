#include "object_loader.h"

// Kongs algorithm implementation for polygon triangulation
// // Precondition: R contains all non-convex points of polygon
// BOOL isEar(Vertice P-1, Vertice P, Vertice P1)
// begin
//     If R is empty
//         return False
//     else
//         if x is convex
//         then
//             if InsideAreaOfTriangle(P-1, P, P1) contains no point of R
//                 return true
//            else
//                 return false
//         else
//             return false
// end

// // Preconditions:
// // Q contains all points/vertices of the polygon
// void DoKong()
// begin
//     while |Q| > 3
//         if isEar(P-1, P, P1) then
//             addTriangle(P-1, P, P1)       // e.g. to a list
//             remove P from Q
//             P = P-1;
//     else
//         P = P1;
// end

/*
** Transform a given polygon into many polygon
*/
void kongs_triangulation() {

}