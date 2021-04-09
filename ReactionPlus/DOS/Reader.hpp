#ifndef REACTION_DOS_READER_HPP
#define REACTION_DOS_READER_HPP


namespace RAPlus {
  namespace DOS {

    class Reader {

      public:

        virtual void close() = 0;

        virtual char read();
        virtual long read(char *buffer, long bufLen);
        virtual long read(char *buffer, long bufLen, long offset, long size) = 0;

        virtual bool ready();

      protected:

                 Reader() { }
        virtual ~Reader() { }

    };

  }
}


#endif // REACTION_DOS_READER_HPP

