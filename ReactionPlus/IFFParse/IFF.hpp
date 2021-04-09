#ifndef REACTIONPLUS_IFF
#define REACTIONPLUS_IFF

#include "InvalidStateException.hpp"

#include <proto/iffparse.h>

#include <string>


namespace RAPlus {
  namespace IFFParse {

    class CollectionItem {

      public:

        CollectionItem(struct ::CollectionItem *ci) : item(ci) { if (ci == 0) throw InvalidStateException("Invalid Collection Item."); }
       ~CollectionItem() { }

        long getSize() { return(item->ci_Size); }
        APTR getData() { return(item->ci_Data); }

        bool nextItem() { return((item = item->ci_Next) != 0); }

      private:

        struct ::CollectionItem *item;

    };


    class ContextNode {

      public:

        ContextNode(struct ::ContextNode *cn) : node(cn) { if (cn == 0) throw InvalidStateException("Invalid Context Node."); }
       ~ContextNode() { }

        long getID()   { return(node->cn_ID); }
        long getType() { return(node->cn_Type); }
        long getSize() { return(node->cn_Size); }
        long getScan() { return(node->cn_Scan); }

        bool nextNode() { return((node = (struct ::ContextNode *)node->cn_Node.mln_Succ) != 0); }

      private:

        struct ::ContextNode *node;

    };


    class IFF {

      public:

        enum IFFOpenMode { MODE_Read, MODE_Write };

                 IFF();
        virtual ~IFF();

        virtual void openIFF(IFFOpenMode mode) = 0;

        virtual void collectionChunk(long type, long id);
        virtual void stopOnExit(long type, long id);
        virtual void stopChunk(long type, long id);

        virtual long parseIFF(long mode);

        virtual CollectionItem &findCollection(long type, long id);
        virtual ContextNode    &currentChunk();

        virtual void pushChunk(long type, long id, long size);
        virtual long writeChunkBytes(const APTR buf, long size);
        virtual long readChunkBytes(APTR buf, long size);
        virtual void popChunk();

        virtual void closeIFF() = 0;

        virtual const std::string iffErrorString(long error);

      protected:

        struct IFFHandle *iff;

        CollectionItem *ci;
        ContextNode    *cn;

    };

  }
}

#endif // REACTIONPLUS_IFF

