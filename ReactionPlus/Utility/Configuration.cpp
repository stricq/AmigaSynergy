#include "Configuration.hpp"


namespace RAPlus {
  namespace Utility {


    Configuration *Configuration::config = NULL;


    Configuration &Configuration::instance(DOS::File &file) {

      if (config == NULL) config = new Configuration(file);

      if (config == NULL) throw OutOfMemoryException("Unable to create the Configuration class.");

      return(*config);

    }


    Configuration &Configuration::instance(std::string &file) {

      if (config == NULL) config = new Configuration(file);

      if (config == NULL) throw OutOfMemoryException("Unable to create the Configuration class.");

      return(*config);

    }


    void Configuration::load(std::string &file) {

      filename = file;

      load(filename);

    }


    void Configuration::load(DOS::File &file) {

      std::string line;

      DOS::FileReader iniFile(file);
      DOS::BufferedReader iniReader(iniFile);
      ParseLine parser;

      try {
        while(iniReader.readLine(line)) {
          parser.parse(line);
          if (parser.size() > 1) fields[parser[0]] = parser[1];
        }
      }
      catch(IOException &ioe) { }

    }


    bool Configuration::hasKey(std::string &key) {

      return(fields.find(key) != fields.end());

    }


    std::string Configuration::operator[](const std::string &key) {

      if (fields.find(key) == fields.end()) return("");

      return(fields[key]);

    }


  }
}

