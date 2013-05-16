#include "CompileScript.hpp"
#include <cstdio>
#include "Script.h"
#include "ConfigLoader.hpp"
#include <iostream>
#include "ObjectBank.hpp"
#include <assert.h>

CompileScript::CompileScript():config(ConfigLoader::instance())
{
    //ctor

}

CompileScript::~CompileScript()
{
    //dtor
}
void CompileScript::build(asIScriptEngine * engine)
{
    // The CScriptBuilder helper is an add-on that loads the file,
// performs a pre-processing pass if necessary, and then tells
// the engine to build a script module.

//r = engine->RegisterObjectMethod("object", "void createObject(string name, string texture, string model)", asMETHOD(ObjectBank,getObject),asCALL_THISCALL); assert (r>= 0);
    //register the function to create an object using script
    ObjectBank & b = ObjectBank::instance();
    int r = engine->RegisterGlobalFunction("void createObject(const string name, const string texture, const string model)", asMETHOD(ObjectBank, getObject), asCALL_THISCALL_ASGLOBAL, &b); assert(r >= 0);
    CScriptBuilder builder;

    //regestring a function to create an object
    //r = engine->RegisterObjectType("Object", 0, asOBJ_REF); assert (r >= 0);
   // r = engine->RegisterObjectBehaviour("Object", asBEHAVE_FACTORY, "ref @ Object()", asFUNCTION(Ref_Factory), asCALL_CDECL); assert (r >= 0);
    r = builder.StartNewModule(engine, "MyModule");
    if( r < 0 )
    {
        // If the code fails here it is usually because there
        // is no more memory to allocate the module
        printf("Unrecoverable error while starting a new module.\n");
        return;
    }
    std::cout << "about to load scripts" << std::endl;
    std::string scriptDir("scripts\\");
    std::vector<std::string> scriptsToCompile = config.getStringArray("scripts");
    std::cout << "got script from config file " << std::endl;
    for(unsigned int i = 0; i < scriptsToCompile.size(); ++i){
        r = builder.AddSectionFromFile((scriptDir + scriptsToCompile[i]).c_str());
        if( r < 0 )
        {
            // The builder wasn't able to load the file. Maybe the file
            // has been removed, or the wrong name was given, or some
            // preprocessing commands are incorrectly written.
            printf("Please correct the errors in the script and try again.\n");
            return;
        }

    }

    r = builder.BuildModule();
    if( r < 0 )
    {
        // An error occurred. Instruct the script writer to fix the
        // compilation errors that were listed in the output stream.
        printf("Please correct the errors in the script and try again.\n");
        return;
    }
}
