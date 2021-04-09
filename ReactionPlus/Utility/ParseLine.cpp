#include "ParseLine.hpp"

#include "IndexRangeException.hpp"
#include "ParseException.hpp"


namespace RAPlus {


  void ParseLine::parse(std::string &line) {

    bool quoted = false;
    bool quotes = false;

    std::string tmpStr;

    fields.clear();

    for(int i = 0; i < (int)line.length(); i++) {
      char c = line[i];
      if (c == '\"') {
        quoted = (quoted ? false : true);
        if (quoted) quotes = true;
      }
      else {
        if (c == seperator) {
          if (quoted) tmpStr += c;
          else {
            quotes = false;
            fields.push_back(tmpStr);
            tmpStr.clear();
          }
        }
        else {
          if (quotes) {
            if (quoted) tmpStr += c;
            else if (c != ' ') throw ParseException("Character found outside quotes.",line,i);
          }
          else tmpStr += c;
        }
      }
    }

    if (quoted) throw ParseException("Premature end of line, trailing quote not found.",line,0);

    if (tmpStr.length() > 0) fields.push_back(tmpStr);

  }


  void ParseLine::parse(std::string &line, char sep) {

    seperator = sep;

    parse(line);

  }


  std::string ParseLine::operator[](int index) const {

    if (index < 0) throw IndexRangeException("Index below lower bounds.",0,index);

    if (index >= (int)fields.size()) throw IndexRangeException("Index above upper bounds.",fields.size() - 1,index);

    return(fields[index]);

  }


}

