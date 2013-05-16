#include "ScriptRunner.hpp"
#include <angelscript.h>
#include <cstdio>
#include "ObjectBank.hpp"
#include <assert.h>

ScriptRunner::ScriptRunner():
	onLoadLevelFunc(NULL)
{
    //ctor
}

ScriptRunner::~ScriptRunner()
{
    //dtor
    ctx->Release();
}
void ScriptRunner::run(asIScriptEngine * engine)
{
    // Find the function that is to be called.
    int r = 0;
    asIScriptModule *mod = engine->GetModule("MyModule");
    asIScriptFunction *func = mod->GetFunctionByDecl("void main()");
	onLoadLevelFunc = mod->GetFunctionByDecl("void onLoadLevel(int levelNumber, string levelName)");
    if( func == 0 )
    {
        // The function couldn't be found. Instruct the script writer
        // to include the expected function in the script.
        printf("The script must have the function 'void main()'. Please add it and try again.\n");
        return;
    }



	ctx = engine->CreateContext();
	callFunction(func);

}
void ScriptRunner::callFunction(asIScriptFunction * func){
// Create our context, prepare it, and then execute
	assert(func != NULL);
	int r = 0;
    ctx->Prepare(func);
    r = ctx->Execute();
    if( r != asEXECUTION_FINISHED )
    {
        // The execution didn't complete as expected. Determine what happened.
        if( r == asEXECUTION_EXCEPTION )
        {
            // An exception occurred, let the script writer know what happened so it can be corrected.
            printf("An exception '%s' occurred. Please correct the code and try again.\n", ctx->GetExceptionString());
        }
    }
}
void ScriptRunner::loadLevelScriptFunction(int levelNumber, std::string levelName){
	ctx->Prepare(onLoadLevelFunc);
	ctx->SetArgDWord(0, levelNumber);
	ctx->SetArgObject(1, &levelName);
	int r = ctx->Execute();
	if( r != asEXECUTION_FINISHED )
    {
        // The execution didn't complete as expected. Determine what happened.
        if( r == asEXECUTION_EXCEPTION )
        {
            // An exception occurred, let the script writer know what happened so it can be corrected.
            printf("An exception '%s' occurred. Please correct the code and try again.\n", ctx->GetExceptionString());
        }
    }
}
