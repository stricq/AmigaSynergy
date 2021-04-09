#include "ScrollerEvents.hpp"

#include <stdio.h>


std::vector<ScrollerEvents *> ScrollerEvents::visibleObservers;
std::vector<ScrollerEvents *> ScrollerEvents::topObservers;
std::vector<ScrollerEvents *> ScrollerEvents::totalObservers;


void ScrollerEvents::onVisibleChange(ScrollerEvents *se) { visibleObservers.push_back(se); }

void ScrollerEvents::onTopChange(ScrollerEvents *se) { topObservers.push_back(se); }

void ScrollerEvents::onTotalChange(ScrollerEvents *se) { totalObservers.push_back(se); }


void ScrollerEvents::stopVisibleEvents(ScrollerEvents *se) { removeObserver(visibleObservers,se); }

void ScrollerEvents::stopTopEvents(ScrollerEvents *se) { removeObserver(topObservers,se); }

void ScrollerEvents::stopTotalEvents(ScrollerEvents *se) { removeObserver(totalObservers,se); }


void ScrollerEvents::removeObserver(std::vector<ScrollerEvents *> &observers, ScrollerEvents *se) {

  if (observers.size() > 0) {
    std::vector<ScrollerEvents *>::iterator obsIter;
    for(obsIter = observers.begin(); obsIter < observers.end(); obsIter++) {
      if ((*obsIter) == se) {
        observers.erase(obsIter);
        break;
      }
    }
  }

}


void ScrollerEvents::setVisible(LONG visible) {

  if (visibleObservers.size() > 0) {
    std::vector<ScrollerEvents *>::iterator obsIter;
    for(obsIter = visibleObservers.begin(); obsIter < visibleObservers.end(); obsIter++) if ((*obsIter) != this) (*obsIter)->scroller_VisibleChanged(visible);
  }

}

void ScrollerEvents::setTop(LONG top) {

  if (topObservers.size() > 0) {
    std::vector<ScrollerEvents *>::iterator obsIter;
    for(obsIter = topObservers.begin(); obsIter < topObservers.end(); obsIter++) if ((*obsIter) != this) (*obsIter)->scroller_TopChanged(top);
  }

}

void ScrollerEvents::setTotal(LONG total) {

  if (totalObservers.size() > 0) {
    std::vector<ScrollerEvents *>::iterator obsIter;
    for(obsIter = totalObservers.begin(); obsIter < totalObservers.end(); obsIter++) if ((*obsIter) != this) (*obsIter)->scroller_TotalChanged(total);
  }

}

