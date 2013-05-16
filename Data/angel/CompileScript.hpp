#ifndef COMPILESCRIPT_H
#define COMPILESCRIPT_H

#include <angelscript.h>
#include <scriptbuilder/scriptbuilder.h>
class ConfigLoader;

class CompileScript
{
	public:
		CompileScript();
		virtual ~CompileScript();

		void build(asIScriptEngine *engine);
	protected:
	private:
		CScriptBuilder builder;
		ConfigLoader & config;
};

#endif // COMPILESCRIPT_H
