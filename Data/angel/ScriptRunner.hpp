#ifndef SCRIPTRUNNER_H
#define SCRIPTRUNNER_H

#include <angelscript.h>
#include <string>

class ScriptRunner
{
	public:
		ScriptRunner();
		virtual ~ScriptRunner();

		void run(asIScriptEngine * engine);

		void callFunction(asIScriptFunction * func);
		void loadLevelScriptFunction(int levelNumber, std::string levelName);
	protected:
	private:
		asIScriptFunction * onLoadLevelFunc;
		asIScriptContext *ctx;
};

#endif // SCRIPTRUNNER_H
