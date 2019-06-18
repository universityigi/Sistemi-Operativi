#pragma once

//! select
#define BIT(n)                  ( 1<<(n) )

//! set to true all bits in y responding to mask
#define BIT_SET(y, mask)        ( y |=  (mask) )

//! set to fase all bits in y in mask
#define BIT_CLEAR(y, mask)      ( y &= ~(mask) )

//! invert all bits in y in mask

#define BIT_FLIP(y, mask)       ( y ^=  (mask) )

//! Create a bitmask of length \a len.
#define BIT_MASK(len)           ( BIT(len)-1 )

//! Create a bitfield mask of length \a starting at bit \a start.
#define BF_MASK(start, len)     ( BIT_MASK(len)<<(start) )

//! Prepare a bitmask for insertion or combining.
#define BF_PREP(x, start, len)  ( ((x)&BIT_MASK(len)) << (start) )

//! Extract a bitfield of length \a len starting at bit \a start from \a y.
#define BF_GET(y, start, len)   ( ((y)>>(start)) & BIT_MASK(len) )

//! Insert a new bitfield value \a x into \a y.
#define BF_SET(y, x, start, len)    \
    ( y= ((y) &~ BF_MASK(start, len)) | BF_PREP(x, start, len) )
