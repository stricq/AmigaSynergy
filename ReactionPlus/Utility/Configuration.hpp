#ifndef RAPLUS_UTILITY_CONFIGURATION
#define RAPLUS_UTILITY_CONFIGURATION

#include "ParseLine.hpp"

#include "DOS/BufferedReader.hpp"
#include "DOS/File.hpp"
#include "DOS/FileReader.hpp"
#include "DOS/IOException.hpp"

#include "Exec/OutOfMemoryException.hpp"

#include <string>
#include <map>


namespace RAPlus {
  namespace Utility {

    class Configuration {

      public:

       ~Configuration() { }

        static Configuration &instance(DOS::File &file);
        static Configuration &instance(std::string &file);

        void load() { load(filename); }
        void load(std::string &file);
        void load(DOS::File &file);

        void save() { save(filename); }
        void save(std::string &file);
        void save(DOS::File &file);

        bool hasKey(std::string &key);

        void  setFilename(DOS::File &file)        { filename = file; }
        void  setFilename(std::string &file) { filename = file; }
        DOS::File &getFilename() { return(filename); }

        std::string operator[](const std::string &key);

      private:

        Configuration(DOS::File &file) : filename(file) { }
        Configuration(std::string &file) : filename(file) { }

        DOS::File filename;

        std::map<std::string, std::string> fields;

        static Configuration *config;

    };

  }
}

#endif // RAPLUS_UTILITY_CONFIGURATION

