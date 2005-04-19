#include "global.h"

// Manually finds the number of walls in a sector
long FindWalls(const unsigned short SectorNumber)
{
 int  j;
 long wallpointer, walls = 1;

 wallpointer = sector[SectorNumber].wallptr;
 j = wall[wallpointer].point2;

 do 
 {
     j = wall[j].point2;
     walls++;

 } while (j != wallpointer);

 
 return walls; // sector[SectorNumber].wallnum;
}


// Alternate sector drawing function - why?
short Draw_Sector_II(FILE *f, const unsigned short i)
{

 int  j;
 long Dn = -15, Up = 1, wallpointer, SectorFloor, SectorCeiling, count = 0;

 SectorFloor  = sector[i].floorz;
 SectorCeiling  = sector[i].ceilingz;
 wallpointer = sector[i].wallptr;
 j   = sector[i].wallptr;
 
 do 
 {
     if (wall[j].nextsector != -1) // Doesn't touch any other sectors
         {
         if (sector[wall[j].nextsector].floorz - SectorFloor < Dn)
             {
                 Dn = sector[wall[j].nextsector].floorz - SectorFloor;
             } 
         if (sector[wall[j].nextsector].ceilingz - SectorCeiling > Up)
             {
                 Up = sector[wall[j].nextsector].ceilingz - SectorCeiling;
             }
         M_Wall[j] = M_Wall[wall[j].nextwall] = 1;
         }
    
     j = wall[j].point2;
    count++;

 } while ((j != wallpointer) && (count < 1000));

 if (count < 1000)
 {
  WriteFloor  (f, i, Dn);
  WriteCeiling(f, i, Up);
 } 
 else printf("Error in Draw_Sector_II\n");

 return count;
}


void DrawBrush(FILE *f, const unsigned short WallNumber, long SectorFloor, long SectorCeiling)
{
 TPoint point1, point2;
 char   Texture[256]="";
 long   j = WallNumber;
 
 // Sanity check? Why would this be bad if this was connected to another sector?
 if (wall[WallNumber].nextwall != -1) // No connecting sector
     return;

 point1.x = point2.x = wall[j].x;
 point1.y = point2.y = wall[j].y;
 point1.zt = point2.zt = SectorFloor;
 point2.zb = SectorCeiling;

/* TWEAKME: Put more dummy textures here and a switch*/
// skip = not drawn because it's never seen by the player
#ifdef QUAKE2
 sprintf(Texture, "e1u1/skip"); // Good for quake 2, but not 1
#elif defined QUAKE1
 sprintf(Texture, "tile0000"); // The good old blood dummy texture
#endif

 fprintf(f, "{\n");
 fprintf(f, "  (%d %d %d) (%d %d %d) (%d %d %d) %s 0 0 0 1 1 1 0 0\n", 
     point1.x, point1.y, SectorFloor, point1.x, point1.y+100, SectorFloor, point2.x+100, point2.y, SectorFloor, Texture); 

 do 
 {
  point1.x = wall[j].x;
  point1.y = wall[j].y;
  point2.x = wall[wall[j].point2].x;
  point2.y = wall[wall[j].point2].y;
  
  sprintf(Texture, "tile%.4d", wall[j].picnum);
  fprintf(f, "  (%d %d %d) (%d %d %d) (%d %d %d) %s 0 0 0 1 1 1 0 0\n", 
      point1.x, point1.y, 500, point2.x, point2.y, 500, point2.x, point2.y, 0, Texture); // 500?

/* Alternate
  fprintf(f, "  (%d %d %d) (%d %d %d) (%d %d %d) %s 0 0 0 1 1 1 0 0\n", 
      point2.x, point2.y, 500, point1.x, point1.y, 500, point1.x, point1.y, 0, Texture); 
*/


  j = wall[j].point2;
 } while (j != WallNumber);


/* TWEAKME: Put more dummy textures here and a switch*/
// skip = not drawn because it's never seen by the player
#ifdef QUAKE2
 strcpy(Texture, "e1u1/skip"); // Good for quake 2, but not 1
#elif defined QUAKE1
 strcpy(Texture, "tile0000"); // The good old blood dummy texture
#endif 

 fprintf(f, "(%d %d %d) (%d %d %d) (%d %d %d) %s 0 0 0 1 1 1 0 0\n",
     0, 0, SectorCeiling, 500, 0, SectorCeiling, 0, 500, SectorCeiling, Texture);

/* Alternate
  fprintf(f, "(%d %d %d) (%d %d %d) (%d %d %d) %s 0 0 0 1 1 1 0 0\n", // 0 and 500 again
              0, 0, SectorCeiling, 500, 0, point2.zb, 0, 500, SectorCeiling, Texture); 
*/

 fprintf(f, "}\n"); 

}

// Writes sectors whose number of walls don't match the listed number of walls
void WriteSector(FILE *f, const unsigned short SectorNumber, const long Up, const long Down)
{
 long Sn = FindWall(SectorNumber); // Finds a specific wall within a sector
 sector[numsectors] = sector[SectorNumber]; // Storing to the temp sector

 if (Sn != -1) 
 {
  sector[numsectors].wallptr = Sn; //wall[sector[i].wallptr].nextwall;
  if (Draw_Sector_II(f, numsectors) < 1000) // Storing to the temp sector
  {
   DrawSectorWalls(f, numsectors);
   DrawBrush(f, sector[SectorNumber].wallptr, sector[SectorNumber].ceilingz+16, sector[SectorNumber].floorz-16); 
  }
 }
 
// else printf("Wall not found in WriteSector\n");
 
     WriteFloor  (f, SectorNumber, Down); // Write the temp sector
     WriteCeiling(f, SectorNumber, Up);
     DrawSectorWalls(f, SectorNumber);
 
}

