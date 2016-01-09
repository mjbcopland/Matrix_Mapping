#ifndef _MATRIX_MAPPING_H_
#define _MATRIX_MAPPING_H_

#include <stdint.h>

// Matrix layout information is passed in the 'matrixType' parameter
// for each constructor.

#define MATRIX_TOP         0x00 // Pixel 0 is at top of matrix
#define MATRIX_BOTTOM      0x01 // Pixel 0 is at bottom of matrix
#define MATRIX_LEFT        0x00 // Pixel 0 is at left of matrix
#define MATRIX_RIGHT       0x02 // Pixel 0 is at right of matrix
#define MATRIX_CORNER      0x03 // Bitmask for pixel 0 matrix corner
#define MATRIX_ROWS        0x00 // Matrix is row major (horizontal)
#define MATRIX_COLUMNS     0x04 // Matrix is column major (vertical)
#define MATRIX_AXIS        0x04 // Bitmask for row/column layout
#define MATRIX_PROGRESSIVE 0x00 // Same pixel order across each line
#define MATRIX_ZIGZAG      0x08 // Pixel order reverses between lines
#define MATRIX_SEQUENCE    0x08 // Bitmask for pixel line order


// These apply only to tiled displays (multiple matrices):

#define TILE_TOP           0x00 // First tile is at top of matrix
#define TILE_BOTTOM        0x10 // First tile is at bottom of matrix
#define TILE_LEFT          0x00 // First tile is at left of matrix
#define TILE_RIGHT         0x20 // First tile is at right of matrix
#define TILE_CORNER        0x30 // Bitmask for first tile corner
#define TILE_ROWS          0x00 // Tiles ordered in rows
#define TILE_COLUMNS       0x40 // Tiles ordered in columns
#define TILE_AXIS          0x40 // Bitmask for tile H/V orientation
#define TILE_PROGRESSIVE   0x00 // Same tile order across each line
#define TILE_ZIGZAG        0x80 // Tile order reverses between lines
#define TILE_SEQUENCE      0x80 // Bitmask for tile line order

class Matrix_Mapping {
  public:
    Matrix_Mapping(uint8_t w, uint8_t h, uint8_t matrixType = 0);
    Matrix_Mapping(uint8_t w, uint8_t h, uint8_t tX, uint8_t tY, uint8_t matrixType = 0);
    int16_t operator()(uint8_t, uint8_t);

  private:
    const uint8_t
      width,
      height,
      tilesX,
      tilesY,
      type;
};

#endif // _MATRIX_MAPPING_H_