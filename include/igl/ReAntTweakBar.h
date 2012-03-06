#ifndef IGL_REANTTWEAKBAR_H
#define IGL_REANTTWEAKBAR_H
#include "igl_inline.h"
// ReAntTweakBar is a minimal wrapper for the AntTweakBar library that allows
// "bars" to be saved and load from disk. Changing your existing app that users
// AntTweakBar to use ReAntTweakBar is trivial.
// 
// Many (but not all) variable types are supported. I'll try to keep track them
// here:
//   TW_TYPE_BOOLCPP
//   TW_TYPE_QUAT4F
//   TW_TYPE_COLOR4F
//   TW_TYPE_COLOR3F
//   TW_TYPE_DIR3F
//   TW_TYPE_BOOL32
//   TW_TYPE_INT32
//   TW_TYPE_FLOAT
//   TW_TYPE_DOUBLE
//   and
//   custom TwTypes made with TwDefineEnum
// 
// I'm working on adding the rest on an as-needed basis. Adding a new type only
// requires changes in a few places...
// 
//
// Copyright Alec Jacobson, 2011
//

// This allows the user to have a non-global, static installation of
// AntTweakBar
#ifdef STATIC_ANTTWEAKBAR
#  include "AntTweakBar.h"
#else
#  include <AntTweakBar.h>
#endif

#include <vector>
#include <string>

namespace igl
{

  TwType ReTwDefineEnum(const char *name, const TwEnumVal *enumValues, unsigned int nbValues);
  
  struct ReTwRWItem
  {
    const char * name;
    TwType type;
    void * var;
    ReTwRWItem(
      const char * name,
      TwType type, 
      void *var)
    {
      this->name = name;
      this->type = type;
      this->var = var;
    }
  };
  
  struct ReTwCBItem
  {
    const char * name;
    TwSetVarCallback setCallback;
    TwGetVarCallback getCallback;
    void * clientData;
    TwType type;
    ReTwCBItem(
      const char * name,
      TwType type, 
      TwSetVarCallback setCallback,
      TwGetVarCallback getCallback,
      void * clientData)
    {
      this->name = name;
      this->type = type;
      this->setCallback = setCallback;
      this->getCallback = getCallback;
      this->clientData = clientData;
    }
  };
  
  class ReTwBar
  {
    // VARIABLES
    // Should be private, but seeing as I'm not going to implement all of the
    // AntTweakBar public functions right away, I'll expose this so that at
    // anytime AntTweakBar functions can be called directly on the bar
    public:
      TwBar * bar;
    private:
      std::vector<ReTwRWItem> rw_items;
      std::vector<ReTwCBItem> cb_items;
  
    // WRAPPERS FOR ANTTWEAKBAR FUNCTIONS 
    public:
      void TwNewBar(const char *barName);
      int TwAddVarRW(
        const char *name, 
        TwType type, 
        void *var, 
        const char *def,
        const bool record=true);
      int TwAddVarCB(
        const char *name, 
        TwType type, 
        TwSetVarCallback setCallback, 
        TwGetVarCallback getCallback, 
        void *clientData, 
        const char *def,
        const bool record=true);
      // Wrappers for convenience (not recorded, just passed on)
      int TwAddVarRO(const char *name, TwType type, void *var, const char *def);
      int TwAddButton(
        const char *name, 
        TwButtonCallback buttonCallback, 
        void *clientData, 
        const char *def);
      int TwSetParam(
        const char *varName, 
        const char *paramName, 
        TwParamValueType paramValueType, 
        unsigned int inValueCount, 
        const void *inValues);
      int TwGetParam(
        const char *varName, 
        const char *paramName, 
        TwParamValueType paramValueType, 
        unsigned int outValueMaxCount, 
        void *outValues);
      int TwRefreshBar();
  
  
    // IO FUNCTIONS
    public:
      // Save current items to file
      // Input:
      //   file_name  name of file to save data to, can be null which means print
      //   to stdout
      // Return:
      //   true only if there were no (fatal) errors
      bool save(const char *file_name);
      std::string get_value_as_string(
        void * var, 
        TwType type);
      // Load into current items from file
      // Input:
      //   file_name  name of input file to load
      // Return:
      //   true only if there were no (fatal) errors
      bool load(const char *file_name);
      // Get TwType from string
      // Input
      //   type_str  string of type 
      // Output
      //   type  TwType converted from string
      // Returns
      //   true only if string matched a valid type
      bool type_from_string(const char *type_str, TwType & type);
      // I realize that I mixing std::string and const char * all over the place.
      // What can you do...
      bool set_value_from_string(
        const char * name, 
        TwType type, 
        const char * value_str);
  };

};

// List of TwBar functions
//TW_API TwBar *      TW_CALL TwNewBar(const char *barName);
//TW_API int          TW_CALL TwDeleteBar(TwBar *bar);
//TW_API int          TW_CALL TwDeleteAllBars();
//TW_API int          TW_CALL TwSetTopBar(const TwBar *bar);
//TW_API TwBar *      TW_CALL TwGetTopBar();
//TW_API int          TW_CALL TwSetBottomBar(const TwBar *bar);
//TW_API TwBar *      TW_CALL TwGetBottomBar();
//TW_API const char * TW_CALL TwGetBarName(TwBar *bar);
//TW_API int          TW_CALL TwGetBarCount();
//TW_API TwBar *      TW_CALL TwGetBarByIndex(int barIndex);
//TW_API TwBar *      TW_CALL TwGetBarByName(const char *barName);
//TW_API int          TW_CALL TwRefreshBar(TwBar *bar);
//
//TW_API int      TW_CALL TwAddVarRW(TwBar *bar, const char *name, TwType type, void *var, const char *def);
//TW_API int      TW_CALL TwAddVarRO(TwBar *bar, const char *name, TwType type, const void *var, const char *def);
//TW_API int      TW_CALL TwAddVarCB(TwBar *bar, const char *name, TwType type, TwSetVarCallback setCallback, TwGetVarCallback getCallback, void *clientData, const char *def);
//TW_API int      TW_CALL TwAddButton(TwBar *bar, const char *name, TwButtonCallback callback, void *clientData, const char *def);
//TW_API int      TW_CALL TwAddSeparator(TwBar *bar, const char *name, const char *def);
//TW_API int      TW_CALL TwRemoveVar(TwBar *bar, const char *name);
//TW_API int      TW_CALL TwRemoveAllVars(TwBar *bar);

#ifdef IGL_HEADER_ONLY
#  include "ReAntTweakBar.cpp"
#endif

#endif