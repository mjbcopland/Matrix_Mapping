#include "Matrix_Mapping.h"

#ifndef swap
#define swap(a, b) { int8_t t = a; a = b; b = t; }
#endif

// Constructor for single matrix:
Matrix_Mapping::Matrix_Mapping(uint8_t w, uint8_t h, uint8_t matrixType)
: Matrix_Mapping(w, h, 1, 1, matrixType) {}

// Constructor for tiled matrices:
Matrix_Mapping::Matrix_Mapping(uint8_t w, uint8_t h,
  uint8_t tX, uint8_t tY, uint8_t matrixType)
: width(w), height(h), tilesX(tX), tilesY(tY), type(matrixType) {}

int16_t Matrix_Mapping::operator()(uint8_t x, uint8_t y) {
  if (x >= width * tilesX || y >= height * tilesY) return -1;

  uint16_t
    tileOffset = 0,
    pixelOffset;

  uint8_t
    corner = type & MATRIX_CORNER,
    minor,
    major,
    majorScale;

  if (tilesX > 1 || tilesY > 1) { // Tiled display, multiple matrices
    uint16_t tile;

    minor = x / width;            // Tile # X/Y; presume row major to
    major = y / height,           // start (will swap later if needed)
    x     = x - (minor * width);  // Pixel X/Y within tile
    y     = y - (major * height); // (-* is less math than modulo)

    // Determine corner of entry, flip axes if needed
    if (type & TILE_RIGHT)  minor = tilesX - 1 - minor;
    if (type & TILE_BOTTOM) major = tilesY - 1 - major;

    // Determine actual major axis of tiling
    if ((type & TILE_AXIS) == TILE_ROWS) {
      majorScale = tilesX;
    } else {
      swap(major, minor);
      majorScale = tilesY;
    }

    // Determine tile number
    if ((type & TILE_SEQUENCE) == TILE_PROGRESSIVE) {
      // All tiles in same order
      tile = major * majorScale + minor;
    } else {
      // Zigzag; alternate rows change direction.  On these rows,
      // this also flips the starting corner of the matrix for the
      // pixel math later.
      if (major & 1) {
        corner ^= MATRIX_CORNER;
        tile = (major + 1) * majorScale - 1 - minor;
      } else {
        tile =  major      * majorScale     + minor;
      }
    }

    // Index of first pixel in tile
    tileOffset = tile * width * height;

  } // else no tiling (handle as single tile)

  // Find pixel number within tile
  minor = x; // Presume row major to start (will swap later if needed)
  major = y;

  // Determine corner of entry, flip axes if needed
  if (corner & MATRIX_RIGHT)  minor = width  - 1 - minor;
  if (corner & MATRIX_BOTTOM) major = height - 1 - major;

  // Determine actual major axis of matrix
  if ((type & MATRIX_AXIS) == MATRIX_ROWS) {
    majorScale = width;
  } else {
    swap(major, minor);
    majorScale = height;
  }

  // Determine pixel number within tile/matrix
  if ((type & MATRIX_SEQUENCE) == MATRIX_PROGRESSIVE) {
    // All lines in same order
    pixelOffset = major * majorScale + minor;
  } else {
    // Zigzag; alternate rows change direction.
    if (major & 1) pixelOffset = (major + 1) * majorScale - 1 - minor;
    else           pixelOffset =  major      * majorScale     + minor;
  }


  return tileOffset + pixelOffset;
}