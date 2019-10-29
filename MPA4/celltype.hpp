#ifndef MPA4_CELLTYPE
#define MPA4_CELLTYPE

enum class CellType { Wall, Open, Source, Destination, Visited };

extern CellType getCellTypeRepresentation(char x);
extern char getCharRepresentation(CellType c);

#endif
