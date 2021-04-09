#ifndef RAPLUS_UTILITY_PARSELINE
#define RAPLUS_UTILITY_PARSELINE

#include <string>
#include <vector>


namespace RAPlus {

  class ParseLine {

    public:

               ParseLine()         : seperator('=') { }
               ParseLine(char sep) : seperator(sep) { }
      virtual ~ParseLine() { }

      virtual void parse(std::string &line);
      virtual void parse(std::string &line, char sep);

      virtual int size() { return(fields.size()); }

      virtual void setSeperator(char sep) { seperator = sep; }
      virtual char getSeperator() { return(seperator); }

      virtual std::string operator[](int index) const;

    private:

      char seperator;

      std::vector<std::string> fields;

  };

}

#endif // RAPLUS_UTILITY_PARSELINE

