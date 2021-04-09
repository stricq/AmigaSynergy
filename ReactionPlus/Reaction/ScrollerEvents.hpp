#ifndef REACTIONPLUS_SCROLLEREVENTS_HPP
#define REACTIONPLUS_SCROLLEREVENTS_HPP

#include <exec/types.h>

#include <vector>


class ScrollerEvents {

  public:

    virtual ~ScrollerEvents() { }

    static void onVisibleChange(ScrollerEvents *se);
    static void onTopChange(ScrollerEvents *se);
    static void onTotalChange(ScrollerEvents *se);

    static void stopVisibleEvents(ScrollerEvents *se);
    static void stopTopEvents(ScrollerEvents *se);
    static void stopTotalEvents(ScrollerEvents *se);

    virtual void setVisible(LONG visible);
    virtual void setTop(LONG top);
    virtual void setTotal(LONG total);

    virtual void scroller_VisibleChanged(LONG) { }
    virtual void scroller_TopChanged(LONG) { }
    virtual void scroller_TotalChanged(LONG) { }

  protected:

    ScrollerEvents() { }

  private:

    static void removeObserver(std::vector<ScrollerEvents *> &observers, ScrollerEvents *se);

    static std::vector<ScrollerEvents *> visibleObservers;
    static std::vector<ScrollerEvents *> topObservers;
    static std::vector<ScrollerEvents *> totalObservers;

};

#endif // REACTIONPLUS_SCROLLEREVENTS_HPP

