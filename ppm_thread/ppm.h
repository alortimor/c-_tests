#ifndef PPM_H
#define PPM_H

class ppm {
  private:
    bool flag_alloc;
    void init();

    unsigned int nr_lines;
    unsigned int nr_columns;

  public:
    unsigned char *r;  
    unsigned char *g; 
    unsigned char *b;

    unsigned int height;
    unsigned int width;
    unsigned int max_col_val;

    unsigned int size;

#endif


