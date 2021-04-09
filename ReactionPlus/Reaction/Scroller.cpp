#include "Scroller.hpp"

#include "Exec/OutOfMemoryException.hpp"

#include <proto/scroller.h>

#include <stdio.h>


namespace RAPlus {
  namespace Reaction {


    std::string Scroller::getAttrError = "Scroller GetAttrs() could not get the attribute.";


    Object *Scroller::newObject(struct TagItem *tagItem) {

      gadgetObject = (Object *)IIntuition->NewObjectA(IScroller->SCROLLER_GetClass(),NULL,tagItem);

      if (!gadgetObject) throw OutOfMemoryException("Could not create the Scroller Object.");

      return(gadgetObject);

    }


    bool Scroller::getArrows() {

      BOOL value = FALSE;

      if (Get(gadgetObject,SCROLLER_Arrows,&value) != 1) throw Exception(getAttrError);

      return(value == TRUE ? true : false);

    }


    int32 Scroller::getTop() {

      int32 value = 0;

      if (Get(gadgetObject,SCROLLER_Top,&value) != 1) throw Exception(getAttrError);

      return(value);

    }


    int32 Scroller::getTotal() {

      int32 value = 0;

      if (Get(gadgetObject,SCROLLER_Total,&value) != 1) throw Exception(getAttrError);

      return(value);

    }


    int32 Scroller::getVisible() {

      int32 value = 0;

      if (Get(gadgetObject,SCROLLER_Visible,&value) != 1) throw Exception(getAttrError);

      return(value);

    }


    uint32 Scroller::getOrientation() {

      uint32 value = 0;

      if (Get(gadgetObject,SCROLLER_Orientation,&value) != 1) throw Exception(getAttrError);

      return(value);

    }


    int16 Scroller::getArrowDelta() {

      int32 value = 0;

      if (Get(gadgetObject,SCROLLER_ArrowDelta,&value) != 1) throw Exception(getAttrError);

      return((int16)value);

    }


    void Scroller::setTop(int32 value) {

      Set(gadgetObject,SCROLLER_Top,value);

    }


    void Scroller::setTop(int32 value, struct Window *win) {

      SetRefresh(win,gadgetObject,SCROLLER_Top,value);

    }


    void Scroller::setTotal(int32 value) {

      Set(gadgetObject,SCROLLER_Total,value);

    }


    void Scroller::setTotal(int32 value, struct Window *win) {

      SetRefresh(win,gadgetObject,SCROLLER_Total,value);

    }


    void Scroller::setVisible(int32 value) {

      Set(gadgetObject,SCROLLER_Visible,value);

    }


    void Scroller::setVisible(int32 value, struct Window *win) {

      SetRefresh(win,gadgetObject,SCROLLER_Visible,value);

    }


    void Scroller::setArrowDelta(int32 value) {

      Set(gadgetObject,SCROLLER_ArrowDelta,value);

    }


    void Scroller::setSignalTask(struct Task *value) {

      Set(gadgetObject,SCROLLER_SignalTask,value);

    }


    void Scroller::setSignalTaskBit(uint32 value) {

      Set(gadgetObject,SCROLLER_SignalTaskBit,value);

    }


    bool Scroller::gadgetUpEvent() {

      if (gadgetUpClass != 0) return((gadgetUpClass->*gadgetUpMethod)(this));

      return(false);

    }


  }
}

