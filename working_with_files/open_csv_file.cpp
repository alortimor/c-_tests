#include <fstream>

// format of csv file is:
// "string",number,"string","string",... etc

std::string get_csv_column(ifstream & in) {
    std::string col;
    unsigned quotes = 0;
    char prev = 0;
    bool finis = false;
    for (int ch; !finis && (ch = in.get()) != EOF; ) {
        switch(ch) {
        case '"':
            ++quotes;
            break;
        case ',':
            if (quotes == 0 || (prev == '"' && (quotes & 1) == 0)) {
                finis = true;
            }
            break;
        default:;
        }
        col += prev = ch;
    }
    return col;
}

int main() {
  int a, b;
  while (infile >> a >> b)
  {
      // process pair (a,b)
  }

  return 0;
}
